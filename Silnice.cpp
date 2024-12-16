#include "Silnice.h"
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

bool Silnice::find() {
    // Priority queue 
    std::priority_queue<std::pair<int, Point>, std::vector<std::pair<int, Point>>, std::greater<std::pair<int, Point>>> queue;

    // Maps to store scores and the path
    std::unordered_map<Point, Point> pastPoint;
    std::unordered_map<Point, int> score;

    // Initialize the start point with score = 0
    queue.push({0, start});
    score[start] = 0;

    // Explore neighbours 
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
            Point neighbour = current + dir;
            if (!map.validCoords(neighbour)) continue;

            // Skip neighbours that have altitude <= 0)
            if (map.alt(neighbour) <= 0) continue;

            // Check slope (altitude difference / distance should not exceed 6%)
            double altitude_diff = map.alt(neighbour) - map.alt(current);
            double slope = (altitude_diff / 1000) * 100;
            //std::cout << "Slope is " << slope << " %" << std::endl;
            if (slope > 6) continue;

            // Calculate score (current score + cost to neighbour, which is always 1)
            int temp_score = score[current] + 1;

            // If a better path was found
            if (score.find(neighbour) == score.end() || temp_score < score[neighbour]) {
                // Update score and add the neighbour to the queue
                score[neighbour] = temp_score;
                queue.push({temp_score, neighbour});
                pastPoint[neighbour] = current;
            }
        }
    }

    return false;  // Path not found
}
