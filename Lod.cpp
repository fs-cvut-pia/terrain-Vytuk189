#include "Lod.h"
#include <queue>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <algorithm>

//Hash function so that it is possible to use an unordered_map of points
namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
        }
    };
}

bool Lod::find() {
    // Priority queue 
    std::priority_queue<std::pair<int, Point>, std::vector<std::pair<int, Point>>, std::greater<std::pair<int, Point>>> queue;

    // Maps to store scores and the path
    std::unordered_map<Point, Point> pastPoint;
    std::unordered_map<Point, int> score;

    // Initialize the start point with score = 0
    queue.push({0, start});
    score[start] = 0;

    // Explore neighbors
    while (!queue.empty()) {
        // Find the point with the lowest score
        Point current = queue.top().second;
        queue.pop();

        // If in  finish, reconstruct the path
        if (current == finish) {
            Point temp = finish;
            while (temp != start) {
                path.push_back(temp);
                temp = pastPoint[temp];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());  // Reverse to get path from start to finish
            return true;
        }

        // Explore neighbours
        for (const Point& dir : {Point(1, 0), Point(-1, 0), Point(0, 1), Point(0, -1), Point(1, 1), Point(1, -1), Point(-1, 1), Point(-1, -1)}) {
            Point neighbor = current + dir;
            if (!map.validCoords(neighbor)) continue;

            // Skip neighbors that have altitude < 0, except for start/finish
            if (map.alt(neighbor) >= 0 && neighbor != start && neighbor != finish) continue;

            // Calculate score (current score + cost to neighbour, which is always 1)
            int temp_score = score[current] + 1;

            // If a better path was found
            if (score.find(neighbor) == score.end() || temp_score < score[neighbor]) {
                // Update score and add the neighbor to the queue
                score[neighbor] = temp_score;
                queue.push({temp_score, neighbor});
                pastPoint[neighbor] = current;
            }
        }
    }

    return false;  // Path not found
}
