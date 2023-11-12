#include <iostream>
#include <vector>
#include <random>

struct Point {
    int id;
    std::vector<int> dimensions;
};

// Check if point A dominates point B in all dimensions
bool dominates(const Point& A, const Point& B) {
    for (size_t i = 0; i < A.dimensions.size(); ++i) {
        if (A.dimensions[i] <= B.dimensions[i]) {
            return false;
        }
    }
    return true;
}

// Scalar Skyline computation
void skylineScalar(const std::vector<Point>& points) {
    for (size_t i = 0; i < points.size(); ++i) {
        bool isDominatedByOthers = false;

        for (size_t j = 0; j < points.size(); ++j) {
            if (i != j && dominates(points[j], points[i])) {
                isDominatedByOthers = true;
                break;
            }
        }

        if (!isDominatedByOthers) {
            // The point at index 'i' is in the Skyline
            // You can take appropriate action here
            std::cout << "Point " << points[i].id << " is in the Skyline." << std::endl;
        }
    }
}

int main() {
    // Generate 100 random 4-dimensional points
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    std::vector<Point> points;
    for (int i = 0; i < 100; ++i) {
        Point p;
        p.id = i;
        p.dimensions.resize(4);
        for (int j = 0; j < 4; ++j) {
            p.dimensions[j] = dist(gen);
        }
        points.push_back(p);
    }

    skylineScalar(points);

    return 0;
}
