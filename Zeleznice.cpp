#include "Zeleznice.h"
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

bool Zeleznice::find() {
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
        // Find the point with the lowest score (cost)
        Point current = queue.top().second;
        queue.pop();

        // If in finish, reconstruct the path
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

        // Explore neighbors
        for (const Point& dir : {Point(1, 0), Point(-1, 0), Point(0, 1), Point(0, -1), Point(1, 1), Point(1, -1), Point(-1, 1), Point(-1, -1)}) {
            Point neighbor = current + dir;
            if (!map.validCoords(neighbor)) continue;

            // Skip neighbors with altitude <= 0
            if (map.alt(neighbor) <= 0) continue;

            // Skip neighbors that have slope > 4%
            double altitude_diff = std::abs(map.alt(neighbor) - map.alt(current));
            double slope = (altitude_diff / 1000) * 100;
            if (slope > 4) continue;

            // The cost is absolute altitude difference between current and neighbor
            int cost = altitude_diff;

            // Calculate score (current score + cost to neighbor)
            int temp_score = score[current] + cost;

            // If a better path was found
            if (score.find(neighbor) == score.end() || temp_score < score[neighbor]) {
                // Update score and add the neighbor to the open set
                score[neighbor] = temp_score;
                queue.push({temp_score, neighbor});
                pastPoint[neighbor] = current;
            }
        }
    }

    return false;  // Path not found
}
