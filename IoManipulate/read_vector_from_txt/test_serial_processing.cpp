

/*
1.Run with default arguments(Fendt):
./test_serial_processing

2.Set arguments by gflags :
./test_serial_processing --filename_prefix="../scans/gassel/single_scan_" --max_iteration = 702

*/
#include "read_vector_from_txt.hpp"
#include "icp2d.h"
#include <vector>
#include <iomanip>
#include <glog/logging.h>
#include <gflags/gflags.h>

// Define gflags
DEFINE_string(filename_prefix, "../scans/Fendt/single_scan_", "Prefix of the filename");
DEFINE_int32(max_iteration, 253, "Max iteration number");

std::vector<MovementData> odometry;

int main(int argc, char* argv[]) {
    google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    FLAGS_log_dir = "../logs";
    FLAGS_logtostderr = false; // set to true to flush info to console

    Icp2d icp_2d;
    Mat3d R_accumulated = Mat3d::Identity();
    Vec3d t_accumulated = Vec3d::Zero();

    for(int i = 0; i <= FLAGS_max_iteration; i++) {
        std::string filename = FLAGS_filename_prefix + std::to_string(i) + ".txt";
        std::vector<Eigen::Vector3d> fileData = readXYFromFile_double(filename);

        LOG(INFO) << "***Read data from:*** " << filename;

        if(!icp_2d.isSourceSet()) {
            icp_2d.SetSource(fileData);  
            continue;
        }

        icp_2d.SetTarget(fileData);

        if (!icp_2d.pose_estimation_3d3d()) {
            //icp_2d.SetSource(fileData);
            // not update source instead
            // still try to match the last scan , but this would require a 
            // larger threshold for min_distance of pair, which was increased to 5 in pose_esimation()
            continue;
        }

        Mat3d R = icp_2d.Get_Odometry().R_;
        Vec3d t = icp_2d.Get_Odometry().p_;

        LOG(INFO) << "R:\n" << R;
        LOG(INFO) << "t:\n" << t;

        if(!t.hasNaN()) {
            t_accumulated += t;
            R_accumulated *= R;
            odometry.push_back(MovementData(0.0, R_accumulated, Vec3d::Zero(), t_accumulated));
            LOG(INFO) << "*R_accumulated:\n" << R_accumulated;
            LOG(INFO) << "*t_accumulated:******************\n" << t_accumulated;
        } else {
            LOG(ERROR) << "********************************  t is NAN  In current iteration \n********************************";
        }

        icp_2d.SetSource(fileData);
    }

    LOG(INFO) << "final displacement is believed to be\n:" << t_accumulated.transpose();
    LOG(INFO) << "final ROTATION is believed to be:\n" << R_accumulated;

    const char* homeDir = getenv("HOME");
    if (!homeDir) {
        LOG(ERROR) << "Error: HOME environment variable not set.";
        return 1;
    }

    std::string fullPath = std::string(homeDir) + "/slam_in_autonomous_driving/data/ch3/velodyne_bag_txt/state_cloud_2d.txt";

    std::ofstream fout(fullPath);
    if (!fout) {
        LOG(ERROR) << "Error: Unable to open file for writing.";
        return 1;
    }

    for (const auto& reading : odometry) {
        auto save_vec3 = [](std::ofstream& fout, const Eigen::Vector3d& v) {
            fout << v[0] << " " << v[1] << " " << v[2] << " ";
        };
        auto save_quat = [](std::ofstream& fout, const Mat3d& R) {
            Eigen::Quaterniond q(R);
            fout << q.w() << " " << q.x() << " " << q.y() << " " << q.z() << " ";
        };

        fout << std::setprecision(18) << reading.timestamp_ << " " << std::setprecision(9);
        save_vec3(fout, reading.p_);
        save_quat(fout, reading.R_);
        save_vec3(fout, reading.v_);
        fout << std::endl;
    }

    LOG(INFO) << "done";
    google::FlushLogFiles(google::INFO);

    return 0;
}
