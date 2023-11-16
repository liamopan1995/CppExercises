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
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include <mlpack/methods/dbscan/dbscan.hpp>
#include <armadillo>
#include <limits>
#include <g2o/types/slam2d/types_slam2d.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/solvers/dense/linear_solver_dense.h>

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

// state cloud 2d( converted from odometry): 
//  time stamp    x,     y,     quaternion.w    quaternion.x  quaternion.y quaternion.z   0, 0, 0 , yaw, pitch, roll
// 1674207936.16734028 -0.00246779501 0.000972316053 1.1386308e-313 0.999999952 0 0 0.000311146919 0 0 0 0.0356548112 -0 0
// 1674207936.26819897 -0.00857342122 -0.00717347218 2.2772616e-313 0.999999914 0 0 0.000413781293 0 0 0 0.0474158448 -0 0
// 1674207936.46993303 -0.00808547143 -0.00219018683 3.49180112e-313 0.999999961 0 0 0.00027987178 0 0 0 0.032070944 -0 0


// Robot's translation between consective frames is saved in: 

// translation_consective_poses:
// formated same as state cloud 2d
// .




int main(int argc, char* argv[]) {
    // Set the information (or covariance) matrix
    Mat3d information_edge_se2;
    information_edge_se2 << 100.0, 0., 0.,
                            0., 100.0, 0.,
                            0., 0., 1000.0;
    Mat2d information_edge_xy;
    information_edge_xy<< 100.0, 0.,
                          0., 100.0;
    information_edge_se2 = Mat3d::Identity();
    information_edge_xy = Mat2d::Identity();

    google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    FLAGS_log_dir = "../logs";
    FLAGS_logtostderr = false; // set to true to flush info to console

    Icp2d icp_2d;
    Mat3d R_accumulated = Mat3d::Identity();
    Vec3d t_accumulated = Vec3d::Zero();
    Vec3d path_accumulated =Vec3d::Zero();
    Mat3d Rotation_accumulated = Mat3d::Identity();




    // Setting up the g2o optimizer

    typedef g2o::BlockSolver<g2o::BlockSolverTraits<-1, -1>> Block;
    Block::LinearSolverType* linearSolver = new g2o::LinearSolverDense<Block::PoseMatrixType>();
    Block* solver_ptr = new Block(std::unique_ptr<Block::LinearSolverType>(linearSolver));

    g2o::OptimizationAlgorithmGaussNewton* solver = new g2o::OptimizationAlgorithmGaussNewton(std::unique_ptr<Block>(solver_ptr));
    
    g2o::SparseOptimizer optimizer;
    optimizer.setAlgorithm(solver);


    for(int i = 0; i <= FLAGS_max_iteration; i++) {
        std::string filename = FLAGS_filename_prefix + std::to_string(i) + ".txt";
        double timestamp = readTimeFromFile(filename);
        std::vector<Eigen::Vector3d> fileData = readXYFromFile_double(filename);
        std::vector<Eigen::Vector3d> fileDataRadius = readXYRFromFile_double(filename);

        LOG(INFO) << "***Read data from:*** " << filename;
        // if it is first scan, set it ot source ,add it directly to global map and skip the rest
        // part of the code.
        if(!icp_2d.isSourceSet()) {
            icp_2d.SetSource(fileData);
            // try  abandon first reading for pose graph

            // int idx = 0;  
            // for(Eigen::Vector3d  point: fileDataRadius) {
            //     Vec6d frame_in_global_time_idx_clusteridx;
            //     frame_in_global_time_idx_clusteridx<<point(0),
            //     point(1),
            //     point(2),
            //     timestamp,
            //     idx++,
            //     0.;
            //     global_map.push_back(frame_in_global_time_idx_clusteridx);
            //     // following line leads to error in comipling , look into it when time is sufficient.
            //     // global_map.emplace_back(point(0), point(1), point(2), timestamp, static_cast<double>(idx++), 0.);

            // }
            // // origin in the odometry
            // odometry.push_back(MovementData(timestamp));            
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


    /*
    *   Clustering , Pose graph construction and solving..
    *
    */

    // Assuming global_map is a std::vector<Vec6d>
    arma::mat data;
    for (const auto& point : global_map) {
        // Include only x, y, r
        data.insert_cols(data.n_cols, arma::vec({point(0,0), point(1,0), point(2,0)}));
    }

    DBSCAN<> dbscan(0.5, 5); // Example values for eps and min_samples
    arma::Row<size_t> assignments;
    dbscan.Cluster(data, assignments);

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
    // update global_map so it now has global cluster idex
    global_map = clusteredData;
    std::vector<Vec6d> global_map_test = global_map;

//  Averaging the features in global_map(clusteredData) by clusters  ( find centriod of each cluster, 
//  which will be used as initial guess for stem centers in the global map)

    // First, calculate the centroids of each cluster
    std::unordered_map<size_t, std::pair<Vec6d, size_t>> clusterSums;
    for (const auto& point : clusteredData) {
        size_t clusterId = static_cast<size_t>(point(5, 0));
        if (clusterId != std::numeric_limits<size_t>::max()) {
            clusterSums[clusterId].first(0, 0) += point(0, 0); // Sum x
            clusterSums[clusterId].first(1, 0) += point(1, 0); // Sum y
            clusterSums[clusterId].second += 1; // Count
        }
    }
    std::unordered_map<size_t, Vec6d> centroids;
    for (const auto& pair : clusterSums) {
        size_t clusterId = pair.first;
        Vec6d sum = pair.second.first;
        size_t count = pair.second.second;
        centroids[clusterId](0, 0) = sum(0, 0) / count; // Average x
        centroids[clusterId](1, 0) = sum(1, 0) / count; // Average y
    }

    // Now replace x and y of each point with the centroid of its cluster
    for (auto& point : clusteredData) {
        size_t clusterId = static_cast<size_t>(point(5, 0));
        if (clusterId != std::numeric_limits<size_t>::max()) {
            point(0, 0) = centroids[clusterId](0, 0); // Centroid x
            point(1, 0) = centroids[clusterId](1, 0); // Centroid y
        }
    }
    //************************************************************************************************                                                   ****/
    // clusteredData is that version of global_map where each stem's cneter is replaced
    // by the centroid of its cluster.
    //************************************************************************************************ 

    //  Pose graph construction 

    //  0. construct vertexXY from clusteredData:
    //  {x, y, r, time stamp ,  idx_in_local_scan [from 0 to n], cluster_index [-1 outlier]}
    //  use a set to check wheter the current clusterId already has been processed.)
    std::unordered_set<size_t> processedClusters;
    int vertex_cnt = 0;
    for (size_t i = 0; i < clusteredData.size(); ++i) {
        size_t clusterId = assignments[i];

        if (clusterId == std::numeric_limits<size_t>::max() || processedClusters.count(clusterId) > 0) {
            // Skip if it's noise or already processed
            continue;
        } else {
            // Process this cluster
            g2o::VertexPointXY* vertex = new g2o::VertexPointXY();
            vertex->setId(clusterId);
            vertex->setEstimate(Eigen::Vector2d(clusteredData[i](0), clusteredData[i](1))); // Set the x, y position
            optimizer.addVertex(vertex);
            vertex_cnt++;
            processedClusters.insert(clusterId); // Mark this clusterId as processed
        }
    }
    cout<< "vertex_cnt in the end :"<< vertex_cnt<<endl;// Notice: Vertex idx is started from 0 !


    //  1. construct vertexSE2 from odometry { a vec<MovementData} 
    // struct MovementData {
    //     double timestamp_;
    //     Mat3d R_= Mat3d::Identity();
    //     Eigen::Vector3d v_;
    //     Eigen::Vector3d p_;
    // usefull : timestamp_ , p_, R_ () 

    //Eigen::Vector3d euler_angles = R.eulerAngles(2, 1, 0); // ZYX order
        // double yaw = euler_angles[0] ; 
        // double pitch = euler_angles[1] ; 
        // double roll = euler_angles[2] ; 




    // g2o::VertexSE2* v = new g2o::VertexSE2();
    // v->setId(pose_id);
    // v->setEstimate(g2o::SE2(pose.x, pose.y, pose.orientation));
    // optimizer.addVertex(v);
    int iter_global_map = 0;
    int test_use = 0;
    // in order to differ from the idices occupied by VertexXY in above.
    for ( size_t i = 0; i < odometry.size() ; ++i) {
        // int vertex_se2_id = i + vertex_cnt + 1; // this is the vertex ID we going to start with
        int vertex_se2_id = i + vertex_cnt + 1      +49; //   let it be the same as the result in python
        auto pose = odometry[i];
        double timestamp = pose.timestamp_;
        Eigen::Vector3d euler_angles = pose.R_.eulerAngles(2, 1, 0);
        double x = pose.p_(0);
        double y = pose.p_(1);
        double yaw = euler_angles[0] ;

        // added a vertex , 
        //cout<< i + vertex_cnt + 1 <<"  !"<<endl;  // this is the vertex ID we going to use here
        
        g2o::VertexSE2* v = new g2o::VertexSE2();
        v->setId(vertex_se2_id);
        v->setEstimate(g2o::SE2(x, y, yaw));
        cout<< "new vertex ,  id: "<< vertex_se2_id <<"added\n";
        // Fix the first vertex
        if(vertex_se2_id == vertex_cnt + 1) {
            v->setFixed(true);
            optimizer.addVertex(v); 
            cout<< "first node is set fix, first node id: "<< vertex_se2_id <<"\n";
            
        } else {
            optimizer.addVertex(v);
            // set a edege EDGE_SE2 to the previous  node : i.e : vertex_se2_id-1
            int to_idx = vertex_se2_id;
            int from_idx = to_idx-1; 
            cout<< " from_idx and to_idx : "<<from_idx<<"   " << to_idx <<endl;
            // since first tranlation in the vec: translation_pose2pose is the move from id:0 to id:1
            auto translation = translation_pose2pose[i-1];
            Eigen::Vector3d euler_angles = translation.R_.eulerAngles(2, 1, 0);
            double x = translation.p_(0);
            double y = translation.p_(1);
            double yaw = euler_angles[0];
   
            cout<< "x ,y ,yaw : "<< x<<" "<< y<< " "<<yaw<<endl;
            g2o::EdgeSE2* e = new g2o::EdgeSE2();
            // Set the connecting vertices (nodes)
            e->setVertex(0, dynamic_cast<g2o::OptimizableGraph::Vertex*>(optimizer.vertex(from_idx)));
            e->setVertex(1, dynamic_cast<g2o::OptimizableGraph::Vertex*>(optimizer.vertex(to_idx)));

            // Set the measurement (relative pose)
            g2o::SE2 relative_pose(x, y, yaw);
            e->setMeasurement(relative_pose);
            e->setInformation(information_edge_se2);// defined at the beginning of main()

            // Add the edge to the optimizer
            optimizer.addEdge(e);
            cout<< "edge se2 has been added in between from: "<<from_idx<<" to " << to_idx <<endl;
            // return 0;
        }
        
        test_use = vertex_se2_id;
        // add the egeXY between current pose and landmarks:

        // timestamp
        // iterate over global_map  ! ! !
        // global_map : x, y, r, time stamp ,  idx_in_local_scan [from 0 to n], cluster_index [0 by default]
        // find cluster_index
        // pose.timestamp_;

        //  having timestamp  and vertex_se2_id

        double specific_value = timestamp;
        //cout<< "specific val: "<< specific_value<<endl;

        // for (size_t j=0;j<global_map_test.size();++j){
        //     cout<< "global_map_test[j]: "<< j <<" " << global_map_test[j]<<endl;
        //     if(j>=10) break;
        // }
        // for (size_t j=0;j<global_map.size();++j){
        //     cout<< "global_map[j]: " << global_map[j]<<endl;
        // }
        // Iterate over the data and print the 6th element where the 4th element matches the specific value
        while(true){
            // cout<< "global_map_test[iter_global_map]: " << global_map_test[iter_global_map]<<endl;
            // cout<< "global_map_test[iter_global_map](3) : " << global_map_test[iter_global_map](3)<<endl;
            if (specific_value == global_map_test[iter_global_map](3)) {
                int vertex_xy_id = global_map_test[iter_global_map](5);
    
                if (vertex_xy_id == -1){
                    //cout<<" 6th Element equal -1: skipping it" << endl;
                    // Do nothing since it is a outlier
                } else {
                    double x =global_map_test[iter_global_map](0);
                    double y =global_map_test[iter_global_map](1);
                    // std::cout << "time stamp  " <<std::setprecision(18)<< global_map_test[iter_global_map](3)<<
                    // " 6th Element (global idx,i.e vertexXY's ID): " << vertex_xy_id << "  x "<<
                    // x<<"  y "<< y << std::endl;

                    // BUILD THE EDGESE2PointXY :
                    g2o::EdgeSE2PointXY* e = new g2o::EdgeSE2PointXY();
                    // Set the connecting vertices (nodes)
                    e->setVertex(0, dynamic_cast<g2o::OptimizableGraph::Vertex*>(optimizer.vertex(vertex_se2_id)));
                    e->setVertex(1, dynamic_cast<g2o::OptimizableGraph::Vertex*>(optimizer.vertex(vertex_xy_id)));
                    //Eigen::Vector2d position(x, y); // Assuming x and y are defined earlier as the positions
                    e->setMeasurement(Eigen::Vector2d(x, y));
                    e->setInformation(information_edge_xy); // Define information_edge_xy appropriately
                    optimizer.addEdge(e);
                    //cout << "Edge XY has been added in between from: " << vertex_se2_id << " to " << vertex_xy_id << endl;

                }
                ++iter_global_map;
            } else {break;}
            
        }
        // if(iter_global_map>49) return 0;
    }

    cout<< "final vertex id of se2vertex (started from  vertex_cnt +1 ) : "<<test_use<<endl;
    cout<< "final vertexXY count: " <<vertex_cnt<<endl;
    cout<< "final iter_global_map final val: "<<iter_global_map<<endl;

    // cout << "Preparing optimization..." << endl;
    // optimizer.setVerbose(true);
    // optimizer.initializeOptimization();
    // cout << "Starting optimization..." << endl;
    // optimizer.optimize(30);

    cout << "Saving optimization results..." << endl;
    optimizer.save("../result_g2o/result_2d.g2o");




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
