#ifndef  READ_VECTOR_FROM_TXT
#define  READ_VECTOR_FROM_TXT

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <Eigen/Dense>

using namespace std;
// Return a vec of float including x  y 0
vector<Eigen::Vector3f> readXYFromFile(const string &filename) {
    vector<Eigen::Vector3f> data;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        double time, x, y, radius,stemIdx;
        if (!(iss >> time >> x >> y >> radius >> stemIdx)) {
            break;  // Error in reading
        }
        Eigen::Vector3f vec(x, y, 0.0f);
        data.push_back(vec);
    }

    file.close();
    return data;
}
// Return a vec of double  including x y r
vector<Eigen::Vector3d> readXYRFromFile_double(const string &filename) {
    vector<Eigen::Vector3d> data;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        double time, x, y, radius, stemIdx;
        if (!(iss >> time >> x >> y >> radius >> stemIdx)) {
            break;  // Error in reading
        }
        Eigen::Vector3d vec(x, y,radius);
        data.push_back(vec);
    }

    file.close();
    return data;
}

// Return a vec of double  including x y 0
vector<Eigen::Vector3d> readXYFromFile_double(const string &filename) {
    vector<Eigen::Vector3d> data;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        double time, x, y, radius,stemIdx;
        if (!(iss >> time >> x >> y >> radius >> stemIdx)) {
            break;  // Error in reading
        }
        Eigen::Vector3d vec(x, y, 0.0f);
        data.push_back(vec);
    }

    file.close();
    return data;
}
// Return a double representing timestamp
double readTimeFromFile(const std::string &filename) {
    double time = -1;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return time;
    }
    
    std::string line;
    if (getline(file, line)) { 
        std::istringstream iss(line);
        if (!(iss >> time)) { 
            std::cerr << "Error in reading time from file: " << filename << std::endl;
        }
    }
    
    file.close();
    return time;
}

#endif