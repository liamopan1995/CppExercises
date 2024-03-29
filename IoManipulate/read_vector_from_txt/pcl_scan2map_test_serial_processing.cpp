// This version takes the scan to map matching approach in finding correspondence 

/*
1.Run with default arguments(Fendt):
./test_serial_processing

2.Set arguments by gflags :
./test_serial_processing --filename_prefix="../scans/gassel/single_scan_" --max_iteration=702
./test_serial_processing --filename_prefix="../scans/Fendt_new/single_scan_" --max_iteration=474
*/



#include "read_vector_from_txt.hpp"
#include "icp2d.h"
#include <vector>
#include <iomanip>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include <pcl/registration/icp.h>
#include <pcl/filters/voxel_grid.h>

// Define gflags
DEFINE_string(filename_prefix, "../scans/Fendt/single_scan_", "Prefix of the filename");
DEFINE_int32(max_iteration, 253, "Max iteration number");


pcl::PointCloud<pcl::PointXYZ>::Ptr voxelFilterPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, float leafSize) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr filteredCloud(new pcl::PointCloud<pcl::PointXYZ>());
    
    pcl::VoxelGrid<pcl::PointXYZ> voxelFilter;
    voxelFilter.setInputCloud(cloud);
    voxelFilter.setLeafSize(leafSize, leafSize, leafSize);
    voxelFilter.filter(*filteredCloud);
    
    return filteredCloud;
}



float leafSize = 2;
std::vector<MovementData> odometry;
std::vector<Eigen::Vector3d> global_map;

int main(int argc, char* argv[]) {
    google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    FLAGS_log_dir = "../logs";
    FLAGS_logtostderr = false; // set to true to flush info to console

    pcl_icp icp_processor;
    Mat3d R_accumulated = Mat3d::Identity();
    Vec3d t_accumulated = Vec3d::Zero();
    Vec3d path_accumulated =Vec3d::Zero();
    Mat3d Rotation_accumulated = Mat3d::Identity();
    pcl::PointCloud<pcl::PointXYZ>::Ptr globalMap(new pcl::PointCloud<pcl::PointXYZ>); 

    for(int i = 0; i <= FLAGS_max_iteration; i++) {
        std::string filename = FLAGS_filename_prefix + std::to_string(i) + ".txt";

        std::vector<Eigen::Vector3d> fileData = readXYFromFile_double(filename);
        std::vector<Eigen::Vector3d> fileDataRadius = readXYRFromFile_double(filename);

        //  before align it is necessary to map/ align the currentCloud into the global frame first
        // for(Eigen::Vector3d&  point: fileData) {
        //         point= Rotation_accumulated *  point + path_accumulated;
        //     }
        
        /// cast to pcl::point cloud and apply the alignment
        pcl::PointCloud<pcl::PointXYZ>::Ptr currentCloud = vectorToPointCloud_2D<pcl::PointXYZ>(fileData);

        if (i == 0) {
            *globalMap = *currentCloud;
            continue;
        }

        icp_processor.align(currentCloud, globalMap); 

        Mat3d R;
        Vec3d t;
        if(icp_processor.hasConverged()) {
            Eigen::Matrix4f R_t = icp_processor.getFinalTransformation();
            std::cout << "ICP has converged. Transformation Matrix: \n";
            std::cout << R_t << std::endl;
            R =  R_t.block<3,3>(0,0).cast<double>();
            t =  R_t.block<3,1>(0,3).cast<double>();
            pcl::PointCloud<pcl::PointXYZ> transformedCloud;
            pcl::transformPointCloud(*currentCloud, transformedCloud, R_t);
            *globalMap += transformedCloud;
            //Downsampling
            globalMap = voxelFilterPointCloud(globalMap, leafSize);
            //Other option :
            // tranform globalMap and transformedCloud into vectors
            // iterate over POINTS in transformedCloud 
            // if no " point" in globalMap has a distance to it that is smaller than the threshol
            // add this POINT into globalMap
            // otherwise update the point by taking a average of the pair.
            

        } else {
            std::cout << "ICP did not converge for point cloud " << i << std::endl;
        }

        LOG(INFO) << "R:\n" << R;
        LOG(INFO) << "t:\n" << t;

        if(!t.hasNaN()&& !R.hasNaN()) {
            path_accumulated += t;
            Rotation_accumulated = R *  Rotation_accumulated;
            odometry.push_back(MovementData(0.0, Rotation_accumulated, Vec3d::Zero(), path_accumulated));
            LOG(INFO) << "*R_accumulated:\n" << Rotation_accumulated;
            LOG(INFO) << "*t_accumulated:******************\n" << path_accumulated;

            for(Eigen::Vector3d  point: fileDataRadius) {
                Eigen::Vector3d frame_in_global= Rotation_accumulated *  point + path_accumulated;
                //Eigen::Vector3d frame_in_global= R_accumulated *  point + t_accumulated;
                global_map.push_back(frame_in_global);


                // "Downsampling" the gloabal map for removal of duplicated points.
                pcl::PointCloud<pcl::PointXYZ>::Ptr place_holder_global_map = vectorToPointCloud<pcl::PointXYZ>(global_map);
                place_holder_global_map = voxelFilterPointCloud(place_holder_global_map, leafSize);//Downsampling
                global_map = pointCloudToVector(*place_holder_global_map);
            }

            





        } else {
            LOG(ERROR) << "********************************  t is NAN  In current iteration \n********************************";
        }
    }


    LOG(INFO) << "final displacement is believed to be\n:" << t_accumulated.transpose();
    LOG(INFO) << "final ROTATION is believed to be:\n" << R_accumulated;

    auto save_vec3 = [](std::ofstream& fout, const Eigen::Vector3d& v) {
        fout << v[0] << " " << v[1] << " " << v[2] << " ";
    };
    auto save_quat = [](std::ofstream& fout, const Mat3d& R) {
        Eigen::Quaterniond q(R);
        fout << q.w() << " " << q.x() << " " << q.y() << " " << q.z() << " ";
    };

    const char* homeDir = getenv("HOME");
    if (!homeDir) {
        LOG(ERROR) << "Error: HOME environment variable not set.";
        return 1;
    }

    std::string fullPath = std::string(homeDir) + "/git/CppExercises/IoManipulate/read_vector_from_txt/scans/state_cloud_2d.txt";

    std::ofstream fout(fullPath);
    if (!fout) {
        LOG(ERROR) << "Error: Unable to open file for writing.";
        return 1;
    }

    for (const auto& reading : odometry) {


        fout << std::setprecision(18) << reading.timestamp_ << " " << std::setprecision(9);
        save_vec3(fout, reading.p_);
        save_quat(fout, reading.R_);
        save_vec3(fout, reading.v_);
        fout << std::endl;
    }

    std::string fullPath_2 = std::string(homeDir) + "/git/CppExercises/IoManipulate/read_vector_from_txt/scans/global_map.txt";
    std::ofstream fout2(fullPath_2);
    if (!fout2) {
        LOG(ERROR) << "Error: Unable to open file for writing.";
        return 1;
    }

    for (const auto& reading : global_map) {

        fout2 << std::setprecision(9);
        save_vec3(fout2, reading);
        fout2 << std::endl;
    }
    LOG(INFO) << "done";
    google::FlushLogFiles(google::INFO);

    return 0;
}
