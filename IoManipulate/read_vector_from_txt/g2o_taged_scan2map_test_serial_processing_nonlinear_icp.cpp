// This version takes the scan to scan matching approach in finding correspondence 

// A wrong usage/convention has been conducted in here : 
//     R()* source + t = target , where target is the newst scan and source the older.

//  it arranges the data in a format that is ready for clustering and buildin the pose graph
/*
1.Run with default arguments(Fendt):
./test_serial_processing

2.Set arguments by gflags :
./test_serial_processing --filename_prefix="../scans/gassel/single_scan_" --max_iteration=702
./test_serial_processing --filename_prefix="../scans/Fendt_new/single_scan_" --max_iteration=474
--filename_prefix="../scans/Fendt_with_time_stamp_246/single_scan_" --max_iteration=246
--filename_prefix="../scans/gassel_with_time_stamp/single_scan_" --max_iteration=695
--filename_prefix="../scans/Fendt_with_time_stamp/single_scan_" --max_iteration=407

*/

#include "read_vector_from_txt.hpp"
#include "common/utilities.h"
//#include "icp2d.h"
#include <vector>
#include <iomanip>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include "icp_2d_gauss_newton.h"
#include <g2o/types/slam2d/types_slam2d.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/solvers/dense/linear_solver_dense.h>

#include <mlpack/methods/dbscan/dbscan.hpp>
#include <armadillo>

using namespace mlpack;
using namespace mlpack::dbscan;

// Define gflags
DEFINE_string(filename_prefix, "../scans/Fendt/single_scan_", "Prefix of the filename");
DEFINE_int32(max_iteration, 253, "Max iteration number");

std::vector<MovementData> odometry;
std::vector<MovementData> translation_pose2pose;
std::vector<Vec6d> global_map;
// Data file's name, layout, description, and format example

// landmarks' x y and radius  under the global frame at timestamp t and idx for assosiation and a cluster_index
// for storing the cluster idx is saved in:

// global_map : x, y, r, time stamp ,  idx_in_local_scan [from 0 to n], cluster_index [0 by default]
                // 1.42116996 -5.99914523 0.250949532 1674207936.16734028 0 0 
                // 12.4400949 -6.7267802 0.339668691 1674207936.16734028 1 0 
                // 2.80325263 8.00486085 0.196213201 1674207936.16734028 2 0 


// landmarks' x y and radius  under the robot's local frame at timestamp t 
// and a idx which is used for assosiation of landmarks from local to 
// to glbal frame after clustering is saved in:

// single_scans :       time stamp        x          y           r   idx_in_local_scan [from 0 to n]
                // 1674207988.61443281 7.83363914 3.97701097 0.308205336       0
                // 1674207988.61443281 -2.41814137 -7.88516998 0.316813171     1  


// Robot's poses in global frame is saved in:

// state cloud 2d: 
//  time stamp    x,     y,     quaternion.w    quaternion.x  quaternion.y quaternion.z   0, 0, 0 , yaw, pitch, roll
// 1674207936.16734028 -0.00246779501 0.000972316053 1.1386308e-313 0.999999952 0 0 0.000311146919 0 0 0 0.0356548112 -0 0
// 1674207936.26819897 -0.00857342122 -0.00717347218 2.2772616e-313 0.999999914 0 0 0.000413781293 0 0 0 0.0474158448 -0 0
// 1674207936.46993303 -0.00808547143 -0.00219018683 3.49180112e-313 0.999999961 0 0 0.00027987178 0 0 0 0.032070944 -0 0


// Robot's translation between consective frames is saved in: 

// translation_consective_poses:
// formated same as state cloud 2d
// .




int main(int argc, char* argv[]) {
    google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    FLAGS_log_dir = "../logs";
    FLAGS_logtostderr = false; // set to true to flush info to console

    sad::Icp2d icp_2d;
    Mat2d R_accumulated = Mat2d::Identity();
    Vec2d t_accumulated = Vec2d::Zero();
    Vec2d path_accumulated =Vec2d::Zero();
    Mat2d Rotation_accumulated = Mat2d::Identity();

    for(int i = 0; i <= FLAGS_max_iteration; i++) {
        std::string filename = FLAGS_filename_prefix + std::to_string(i) + ".txt";
        double timestamp = readTimeFromFile(filename);
        std::vector<Eigen::Vector2d> fileData = readXYFromFile_double_vec2d(filename);
        std::vector<Eigen::Vector3d> fileDataRadius = readXYRFromFile_double(filename);

        LOG(INFO) << "***Read data from:*** " << filename;

        if(!icp_2d.isTargetSet()) {
            icp_2d.SetTarget(fileData);  

            continue;
        }

        icp_2d.SetSource(fileData);
        SE2 pose ; 
        icp_2d.AlignGaussNewton(pose);
        Mat2d R = pose.so2().matrix();
        Vec2d t = pose.translation();
        icp_2d.SetTarget(fileData);




        // path_accumulated -= t;
        // Rotation_accumulated = R.inverser()*  Rotation_accumulated;
        path_accumulated += t;
        Rotation_accumulated = R*  Rotation_accumulated;
        // Save the translation between consective poses
        translation_pose2pose.push_back(MovementData(timestamp, R, 
        Vec3d::Zero(), t));
        // Save the translation from the current pose to the origin
        odometry.push_back(MovementData(timestamp, Rotation_accumulated, 
        Vec3d::Zero(), path_accumulated));

        LOG(INFO) << "R:\n" << R;
        LOG(INFO) << "t:\n" << t;
        LOG(INFO) << "*R_accumulated:\n" << R_accumulated.inverse();
        LOG(INFO) << "*t_accumulated:******************\n" << path_accumulated;


        int idx = 0;
        for(Eigen::Vector3d  point: fileDataRadius) {
            //Eigen::Vector3d frame_in_global= R_accumulated.inverse() *  point - t_accumulated;
            //Eigen::Vector3d frame_in_global= R_accumulated.inverse() *  (point - t_accumulated);
            

            double radius = point(2);
            Vec2d point_xy = Vec2d(point(0),point(1));
            Eigen::Vector2d frame_in_global = Rotation_accumulated * point_xy + path_accumulated;

            Vec6d frame_in_global_time_idx_clusteridx;
            frame_in_global_time_idx_clusteridx<<frame_in_global(0),
            frame_in_global(1),
            radius,
            timestamp,
            idx++,
            0.;

            //timestamp
            global_map.push_back(frame_in_global_time_idx_clusteridx);
        }



        
    }
    
    // when time is sufficient also try : keeping a global map and updating by adding new features which 
    // failed to find a nearest neighbour and to those whom  found one, update their value by averaging.
    // keep a global idx there.



    // create the first vertexSE2 and its edges here ( fixed starting point with ID 0)
    // create the initial guess of the global landmark maps via clustering, keeping track of tree idx 
    // after clustering.  from this initial guess create/(update per idx) the VertexPointXY 
    
    // 1. finsh the clustering ? or how to maintain the gloabl map and its indexing ? 

    // global_map 
    // stems in global_map( non duplicate ) should have the same idx as in vec edgeSE2PointXY
    // hashmap ? 


        // create the vertexSE2 and its edgeSE2(from last to cur) here 
        // create the edgeSE2PointXY here 


    // run optimizer and save the result as .g2o to local for verification.
    
    // get the clustering done





    // Lambdas
    auto save_vec3 = [](std::ofstream& fout, const Eigen::Vector3d& v) {
        fout << v[0] << " " << v[1] << " " << v[2] << " ";
    };

    auto save_vec6 = [](std::ofstream& fout, const Vec6d& v) {
        fout << v(0,0) << " " << v(1,0) << " " << v(2,0) << " "<<std::setprecision(18) <<v(3,0) << " " <<std::setprecision(9)<< v(4,0) << " " << v(5,0)<< " ";
    };

    auto save_quat = [](std::ofstream& fout, const Mat3d& R) {
        Eigen::Quaterniond q(R);
        fout << q.w() << " " << q.x() << " " << q.y() << " " << q.z() << " ";
    };

    auto save_yaw_pitch_roll = [](std::ofstream& fout, const Eigen::Matrix3d& R) {
        Eigen::Vector3d euler_angles = R.eulerAngles(2, 1, 0); // ZYX order
        double yaw = euler_angles[0] ; 
        double pitch = euler_angles[1] ; 
        double roll = euler_angles[2] ; 
        fout << yaw << " " << pitch << " " << roll;
    };




    // Assuming global_map is a std::vector<Vec6d>
    arma::mat data;
    for (const auto& point : global_map) {
        // Include only x, y, r
        data.insert_cols(data.n_cols, arma::vec({point(0,0), point(1,0), point(2,0)}));
    }

    DBSCAN<> dbscan(0.5, 5); // Example values for eps and min_samples
    arma::Row<size_t> assignments;
    dbscan.Cluster(data, assignments);

    // // Assuming 'assignments' is your arma::Row<size_t> from DBSCAN
    // for (size_t i = 0; i < assignments.n_elem; ++i) {
    //     if
    //     std::cout << "Point " << i << " is in cluster " << assignments[i] << std::endl;
    // }

    std::vector<Vec6d> clusteredData;
    for (size_t i = 0; i < global_map.size(); ++i) {
        Vec6d objectWithCluster = global_map[i];
        size_t clusterId = assignments[i];

        // Append the cluster ID to the object's existing data
        // Assuming the 5th index of Vec6d is free to store the cluster ID
        if (clusterId == std::numeric_limits<size_t>::max()) {
        // If the point is considered noise, set the cluster ID to -1
            objectWithCluster(5, 0) = -1;
        } else {
        // Otherwise, use the actual cluster ID
            objectWithCluster(5, 0) = static_cast<double>(clusterId);
        }

        clusteredData.push_back(objectWithCluster);
    }
    global_map = clusteredData;



    // IO
    const char* homeDir = getenv("HOME");
    if (!homeDir) {
        LOG(ERROR) << "Error: HOME environment variable not set.";
        return 1;
    }

    // Save Results
    // save every single poses in the global map(frame)
    std::string fullPath = std::string(homeDir) + "/git/CppExercises/IoManipulate/read_vector_from_txt/scans/Gauss_Newton_ICPSCAN2SCAN/state_cloud_2d.txt";
    std::ofstream fout(fullPath);
    if (!fout) {
        LOG(ERROR) << "Error: Unable to open file for writing.";
        return 1;
    }
    for (const auto& reading : odometry) {
        fout << std::setprecision(18) << reading.timestamp_ << " " << std::setprecision(9);
        save_vec3(fout, reading.p_);
        //Replace the next line with save_row_pitch_yaw in order to save rotation in angleform
        //Or append yaw pitch roll to the end of v_, we choose the second way
        save_quat(fout, reading.R_); 
        save_vec3(fout, reading.v_);
        save_yaw_pitch_roll(fout, reading.R_);//Appeding
        fout << std::endl;
    }

    // save landmarks in the global map 
    std::string fullPath_2 = std::string(homeDir) + "/git/CppExercises/IoManipulate/read_vector_from_txt/scans/Gauss_Newton_ICPSCAN2SCAN/global_map.txt";
    std::ofstream fout2(fullPath_2);
    if (!fout2) {
        LOG(ERROR) << "Error: Unable to open file for writing.";
        return 1;
    }
    for (const auto& reading : global_map) {
        fout2 << std::setprecision(9);
        save_vec6(fout2, reading);
        fout2 << std::endl;
    }

    // save translations of consective poses 
    std::string fullPath_3 = std::string(homeDir) + "/git/CppExercises/IoManipulate/read_vector_from_txt/scans/Gauss_Newton_ICPSCAN2SCAN/translation_consective_poses.txt";
    std::ofstream fout3(fullPath_3);
    if (!fout3) {
        LOG(ERROR) << "Error: Unable to open file for writing.";
        return 1;
    }
    for (const auto& reading : translation_pose2pose) {
        fout3 << std::setprecision(18) << reading.timestamp_ << " " << std::setprecision(9);
        save_vec3(fout3, reading.p_);
        save_quat(fout3, reading.R_); 
        save_vec3(fout3, reading.v_);
        save_yaw_pitch_roll(fout3, reading.R_);//Appeding
        fout3 << std::endl;
    }
    
    LOG(INFO) << "done";
    google::FlushLogFiles(google::INFO);

    return 0;
}

