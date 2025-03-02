#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>

struct Point3D {
    double x, y, z;
};

int main() {
    const int numPoints = 100;  // Number of points to generate
    const double circleRadius = 5.0;  // Radius of the circle

    std::vector<Point3D> points;

    // Set up random number generator for noise
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> noise(0.0, 0.2); // Mean 0, Standard deviation 0.2

    for (int i = 0; i < numPoints; ++i) {
        double angle = 1 * M_PI * i / numPoints; // Angle between points
        double radius = circleRadius + noise(gen); // Add noise to radius

        Point3D point;
        point.x = radius * cos(angle);
        point.y = radius * sin(angle);
        point.z = noise(gen); // Z coordinate also has noise

        points.push_back(point);
    }

    std::ofstream outfile("circlepoints.csv");
    if (outfile.is_open()) {
        for (const Point3D& point : points) {
            outfile << point.x << "," << point.y << "," << point.z << "\n";
        }
        outfile.close();
        std::cout << "Points saved to circlepoints.csv" << std::endl;
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }

    return 0;
}
