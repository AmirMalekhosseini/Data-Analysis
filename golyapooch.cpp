#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

struct Coordinate {
    int x, y;
    Coordinate(int x, int y) : x(x), y(y) {}
};

struct ClosestPair {
    double distance;
    Coordinate coord1, coord2;
    ClosestPair(double dist, Coordinate c1, Coordinate c2) : distance(dist), coord1(c1), coord2(c2) {}
    
    void print() const {
        std::cout << coord1.x << " " << coord1.y << " " << coord2.x << " " << coord2.y << std::endl;
    }

    void printRev() const {
        std::cout << coord2.x << " " << coord2.y << " " << coord1.x << " " << coord1.y << std::endl;
    }
};

void mergeSort(std::vector<Coordinate>& points, bool sortByX) {
    if (points.size() <= 1) return;

    int mid = points.size() / 2;
    std::vector<Coordinate> left(points.begin(), points.begin() + mid);
    std::vector<Coordinate> right(points.begin() + mid, points.end());

    mergeSort(left, sortByX);
    mergeSort(right, sortByX);

    int i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {
        if ((sortByX && left[i].x < right[j].x) || (!sortByX && left[i].y < right[j].y)) {
            points[k++] = left[i++];
        } else {
            points[k++] = right[j++];
        }
    }
    while (i < left.size()) points[k++] = left[i++];
    while (j < right.size()) points[k++] = right[j++];
}

double getDistance(const Coordinate& p1, const Coordinate& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

ClosestPair mergeBoundary(std::vector<Coordinate>& boundaryPoints, ClosestPair minResult) {
    mergeSort(boundaryPoints, false);  // Sort by y-coordinate
    for (size_t i = 0; i < boundaryPoints.size(); ++i) {
        for (size_t j = i + 1; j < boundaryPoints.size() && (boundaryPoints[j].y - boundaryPoints[i].y) < minResult.distance; ++j) {
            double distance = getDistance(boundaryPoints[i], boundaryPoints[j]);
            if (distance < minResult.distance) {
                minResult = ClosestPair(distance, boundaryPoints[i], boundaryPoints[j]);
            }
        }
    }
    return minResult;
}

ClosestPair findClosestPair(std::vector<Coordinate>& points, int start, int end) {
    if (end - start <= 3) {
        ClosestPair minPair(std::numeric_limits<double>::infinity(), {0, 0}, {0, 0});
        for (int i = start; i < end; ++i) {
            for (int j = i + 1; j < end; ++j) {
                double dist = getDistance(points[i], points[j]);
                if (dist < minPair.distance) {
                    minPair = ClosestPair(dist, points[i], points[j]);
                }
            }
        }
        return minPair;
    }

    int mid = (start + end) / 2;
    ClosestPair leftResult = findClosestPair(points, start, mid);
    ClosestPair rightResult = findClosestPair(points, mid, end);
    ClosestPair minResult = (leftResult.distance < rightResult.distance) ? leftResult : rightResult;

    std::vector<Coordinate> boundaryPoints;
    for (int i = start; i < end; ++i) {
        if (std::abs(points[i].x - points[mid].x) < minResult.distance) {
            boundaryPoints.push_back(points[i]);
        }
    }
    return mergeBoundary(boundaryPoints, minResult);
}

int main() {
    int numberOfPoints;
    std::cin >> numberOfPoints;
    std::vector<Coordinate> coordinates;
    
    for (int i = 0; i < numberOfPoints; ++i) {
        int x, y;
        std::cin >> x >> y;
        coordinates.emplace_back(x, y);
    }

    mergeSort(coordinates, true);  // Sort by x-coordinate initially
    ClosestPair result = findClosestPair(coordinates, 0, numberOfPoints);
    
    if ((result.coord1.x < result.coord2.x) || 
       (result.coord1.x == result.coord2.x && result.coord1.y < result.coord2.y)) {
        result.print();
    } else {
        result.printRev();
    }
    return 0;
}
