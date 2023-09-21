// main.cpp
#include "read_vector_from_txt.hpp" // Assuming the given header is named 'read_vector_from_txt.h'
#include <vector>
#include "icp2d.h"

int main() {
    Icp2d icp_2d;
    Mat3d R = Mat3d::Zero();
    Mat3d R_accumulated = Mat3d::Identity();
    Vec3d t = Vec3d::Zero();
    Vec3d t_accumulated = Vec3d::Zero();
    for(int i = 0; i <= 253; i++) {
        std::string filename = "../scans/single_scan_" + std::to_string(i) + ".txt";
        std::vector<Eigen::Vector3d> fileData = readXYFromFile_double(filename);



        // Optionally print out status
        std::cout << "Read data from: " << filename << std::endl;
        if(!icp_2d.isSourceSet()) {
            icp_2d.SetSource(fileData);
            continue;
        };
        icp_2d.SetTarget(fileData);
        icp_2d.pose_estimation_3d3d(R,t);

        cout<<"R:\n"<<R<<endl;
        cout<<"t:\n"<<t<<endl;
        if(!t.hasNaN()) {
            t_accumulated += t;
            R_accumulated *= R;
        } else {
            cout<< "********************************  t is NAN  In current iteration \n********************************";
        }

        icp_2d.SetSource(fileData);
    }
    cout<<"final displacement is believed to be\n:"<<t_accumulated<<t_accumulated.transpose()<<"\n";
    cout<<"final ROTATION is believed to be:\n"<<R_accumulated<<t_accumulated;

    return 0;
}
