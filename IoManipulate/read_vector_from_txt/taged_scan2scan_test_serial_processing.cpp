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
#include "icp2d.h"
#include <vector>
#include <iomanip>
#include <glog/logging.h>
#include <gflags/gflags.h>

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

    Icp2d icp_2d;
    Mat3d R_accumulated = Mat3d::Identity();
    Vec3d t_accumulated = Vec3d::Zero();
    Vec3d path_accumulated =Vec3d::Zero();
    Mat3d Rotation_accumulated = Mat3d::Identity();

    for(int i = 0; i <= FLAGS_max_iteration; i++) {
        std::string filename = FLAGS_filename_prefix + std::to_string(i) + ".txt";
        double timestamp = readTimeFromFile(filename);
        std::vector<Eigen::Vector3d> fileData = readXYFromFile_double(filename);
        std::vector<Eigen::Vector3d> fileDataRadius = readXYRFromFile_double(filename);

        LOG(INFO) << "***Read data from:*** " << filename;

        if(!icp_2d.isSourceSet()) {
            icp_2d.SetSource(fileData);  
            continue;
        }

        icp_2d.SetTarget(fileData);

        if (!icp_2d.pose_estimation_3d3d()) {
            // icp_2d.SetSource(fileData);
            // not update source instead
            // still try to match the last scan , but this would require a 
            // larger threshold for min_distance of pair, which was increased to 5 in pose_esimation()
            continue;
        }

        Mat3d R = icp_2d.Get_Odometry().R_;
        Vec3d t = icp_2d.Get_Odometry().p_;

        if(!t.hasNaN()&& !R.hasNaN()) {
            // because the swaped use of target and source in the code : bfnn
            // the t and R is the transformation for aligning the older scan to the newst scan.
            path_accumulated -= t;
            Rotation_accumulated = R.inverse() *  Rotation_accumulated;
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
                Eigen::Vector3d frame_in_global = Rotation_accumulated * point + path_accumulated;

                Vec6d frame_in_global_time_idx_clusteridx;
                frame_in_global_time_idx_clusteridx<<frame_in_global(0),
                frame_in_global(1),
                frame_in_global(2),
                timestamp,
                idx++,
                0.;

                //timestamp
                global_map.push_back(frame_in_global_time_idx_clusteridx);
            }
            icp_2d.SetSource(fileData);//oct 18
        } else {
            LOG(ERROR) << "********************************  t is NAN  In current iteration \n********************************";
        }

        //icp_2d.SetSource(fileData); //oct 18, update source only after valid R and t have been aquired
    }




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


    // IO
    const char* homeDir = getenv("HOME");
    if (!homeDir) {
        LOG(ERROR) << "Error: HOME environment variable not set.";
        return 1;
    }

    // Save Results
    // save every single poses in the global map(frame)
    std::string fullPath = std::string(homeDir) + "/git/CppExercises/IoManipulate/read_vector_from_txt/scans/state_cloud_2d.txt";
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
    std::string fullPath_2 = std::string(homeDir) + "/git/CppExercises/IoManipulate/read_vector_from_txt/scans/global_map.txt";
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
    std::string fullPath_3 = std::string(homeDir) + "/git/CppExercises/IoManipulate/read_vector_from_txt/scans/translation_consective_poses.txt";
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
