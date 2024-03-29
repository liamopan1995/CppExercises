
#ifndef POSE_GRAPH_BUILDER_H
#define POSE_GRAPH_BUILDER_H

#include <string>
#include <vector>
#include <unordered_set>
#include <Eigen/Dense>
#include <g2o/core/sparse_optimizer.h>
#include "common/utilities.h" // Custom header for utility structures like Vec6d
#include <mlpack/methods/dbscan/dbscan.hpp>
#include <armadillo>
#include <limits>
class PoseGraphBuilder {
public:
    std::vector<Vec6d> clusteredData_;
    PoseGraphBuilder();

    void build_optimize_Graph(const std::vector<Vec6d>& globalMap, 
                    std::vector<Vec6d> localMap, 
                    const std::vector<MovementData>& odometry,
                    const std::vector<MovementData>& translationPose2Pose);
    void saveGraph();
    void saveGraph(std::string location);
    void clear_edges_vertices();

private:
    g2o::SparseOptimizer optimizer_;
    void initializeOptimizer();
    void clusterData(const std::vector<Vec6d>& globalMap);
    void addVerticesAndEdges(   
                             std::vector<Vec6d> localMap, 
                             const std::vector<MovementData>& odometry,
                             const std::vector<MovementData>& translationPose2Pose);
    Mat3d information_edge_se2_ = Mat3d::Identity();
    Mat2d information_edge_xy_ = Mat2d::Identity();
    // Additional private members and methods...
    // Todo  iterate over vertices and publish them in ros message types.
};

#endif // POSE_GRAPH_BUILDER_H
