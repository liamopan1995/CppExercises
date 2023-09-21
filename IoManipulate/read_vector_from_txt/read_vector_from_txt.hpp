#ifndef  READ_VECTOR_FROM_TXT
#define  READ_VECTOR_FROM_TXT

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <Eigen/Dense>

using namespace std;

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
        double time, x, y, radius;
        if (!(iss >> time >> x >> y >> radius)) {
            break;  // Error in reading
        }
        Eigen::Vector3f vec(x, y, 0.0f);
        data.push_back(vec);
    }

    file.close();
    return data;
}
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
        double time, x, y, radius;
        if (!(iss >> time >> x >> y >> radius)) {
            break;  // Error in reading
        }
        Eigen::Vector3d vec(x, y, 0.0f);
        data.push_back(vec);
    }

    file.close();
    return data;
}


#endif