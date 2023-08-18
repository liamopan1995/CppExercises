#include <iostream>
#include <fstream>
#include <vector>

struct Point3D {
    double x, y, z;
};

int main() {
    std::vector<Point3D> points = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };

    std::ofstream outfile("points.csv");
    if (outfile.is_open()) {
        for (const Point3D& point : points) {
            outfile << point.x << "," << point.y << "," << point.z << "\n";
        }
        outfile.close();
        std::cout << "Points saved to points.csv" << std::endl;
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }

    return 0;
}
