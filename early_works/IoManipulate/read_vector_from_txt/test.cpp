#include "read_vector_from_txt.hpp"
#include "bfnn.h"
#include "icp3d.h"
#include "icp2d.h"
#include "icp_2d_gauss_newton.h"
int main(int argc, char* argv[]) {
    // vector<Eigen::Vector3f> cloud1 = readXYFromFile("../scans/single_scan_0.txt");
    // vector<Eigen::Vector3f> cloud2 = readXYFromFile("../scans/single_scan_1.txt");
    // vector<Eigen::Vector3f> source = cloud1;
    // vector<Eigen::Vector3f> target = cloud2;

    vector<Eigen::Vector3d> cloud1 = readXYFromFile_double("../scans/single_scan_24.txt");
    vector<Eigen::Vector3d> cloud2 = readXYFromFile_double("../scans/single_scan_25.txt");
    vector<Eigen::Vector3d> source = cloud1;
    vector<Eigen::Vector3d> target = cloud2;

    // Example: Print the data from the first file
    cout<<"cloud1\n";
    for (const auto &vec : cloud1) {
        cout << vec[0] << ", " << vec[1] << ", " << vec[2] << endl;
    }
    cout<<"cloud2\n";
    for (const auto &vec : cloud2) {
        cout << vec[0] << ", " << vec[1] << ", " << vec[2] << endl;
    }

    

    cout<<cloud1.size()<<"  "<<cloud2.size()<<endl;
    for (int i=0; i<cloud1.size();i++) {
        int idx = -1;
        cout<<"idx is initlized to: "<<idx<<"\n"<<endl;
        // See matching result    
        idx =bfnn_point(cloud1,cloud2[i]);
        if(idx != -1) {
            cout<<"idx is : "<<idx<<"\n"<<"i is : "<<i<<"\n"<<endl;
            cout<<cloud1[idx]<<"\n"<<cloud2[i];
        }
    }


    std::vector<std::pair<size_t, size_t>> matches_1_2;

    // bfnn_cloud_mt(cloud1,cloud2, matches_1_2);

    // for(int i=0; i< matches_1_2.size(); i++){
    //     cout<<matches_1_2[i].first<<matches_1_2[i].second<<"      distance: " <<(cloud1[matches_1_2[i].first] - cloud2[matches_1_2[i].second]).squaredNorm()<<endl;
    // }
    // matches_1_2.clear();

    bfnn_cloud_mt(target,source, matches_1_2);
    /// this represent the right order
    for(int i=0; i< matches_1_2.size(); i++){
        cout<<matches_1_2[i].first<<matches_1_2[i].second<<"      distance: " <<(target[matches_1_2[i].first] - source[matches_1_2[i].second]).squaredNorm()<<endl;
    }

    Icp3d icp;
    Icp2d icp_2d;
    icp_2d.SetSource(source);
    icp_2d.SetTarget(target);
    // Mat3f R = Mat3f::Zero();
    // Vec3f t = Vec3f::Zero();
    // icp_2d.pose_estimation_3d3d(R,t);
    // Mat3d R = Mat3d::Zero();
    // Vec3d t = Vec3d::Zero();
    icp_2d.pose_estimation_3d3d();
    cout<<"R:\n"<<icp_2d.Get_Odometry().R_<<endl;
    cout<<"t:\n"<<icp_2d.Get_Odometry().p_<<endl;

    return 0;
}