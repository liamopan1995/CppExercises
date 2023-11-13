//
// Created by xiang on 2022/3/15.
//

#include "icp_2d_gauss_newton.h"
#include "common/math_utils.h"

#include <glog/logging.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/search/impl/kdtree.hpp>

namespace sad {
Mat32d ComputeJacobian(const SE2& pose, const Eigen::Vector2d& point);

bool Icp2d::AlignGaussNewton(SE2& init_pose) {
    int iterations = 10;
    double cost = 0, lastCost = 0;
    SE2 current_pose = init_pose;
    const float max_dis2 = 3.5;    // 最近邻时的最远距离（平方） //1st: 0.5 2nd:2.5; 3rd:2.5 4th:3.5
    const int min_effect_pts = 4;  // 最小有效点数 //1st 4 2nd: 4 3rd: 6 ;4th:4

    for (int iter = 0; iter < iterations; ++iter) {
        Mat3d H = Mat3d::Zero();
        Vec3d b = Vec3d::Zero();
        cost = 0;

        int effective_num = 0;  // 有效点数

        // 遍历source
        for (const auto& point : source_scan_) {
            Vec2d pw = current_pose * point; // Transformation is directly applied to the point
            Point2d pt;
            pt.x = pw.x();
            pt.y = pw.y();

            // Nearest neighbor search
            std::vector<int> nn_idx;
            std::vector<float> dis;
            kdtree_.nearestKSearch(pt, 1, nn_idx, dis);

            if (nn_idx.size() > 0 && dis[0] < max_dis2) {
                effective_num++;
                // Compute the Jacobian for the transformation
                Mat32d J = ComputeJacobian(current_pose, point);

                Vec2d e(pt.x - target_cloud_->points[nn_idx[0]].x, pt.y - target_cloud_->points[nn_idx[0]].y);
                b += -J * e;
                H += J * J.transpose();
                cost += e.dot(e);
            }
        }

        if (effective_num < min_effect_pts) {
            return false;
        }

        // solve for dx
        Vec3d dx = H.ldlt().solve(b);
        if (isnan(dx[0])) {
            break;
        }

        cost /= effective_num;
        if (iter > 0 && cost >= lastCost) {
            break;
        }

        LOG(INFO) << "iter " << iter << " cost = " << cost << ", effect num: " << effective_num;

        current_pose.translation() += dx.head<2>();
        current_pose.so2() = current_pose.so2() * SO2::exp(dx[2]);
        lastCost = cost;
    }

    init_pose = current_pose;
    LOG(INFO) << "estimated pose: " << current_pose.translation().transpose()
              << ", theta: " << current_pose.so2().log();

    return true;
}

void Icp2d::BuildTargetKdTree() {
    if (target_scan_ .empty()) {
        LOG(ERROR) << "target is not set";
        return;
    }

    target_cloud_.reset(new Cloud2d);

    for (const auto& point : target_scan_) {
            Point2d p;
            p.x = point.x();
            p.y = point.y();
            target_cloud_->points.push_back(p);
        }

    target_cloud_->width = target_cloud_->points.size();
    target_cloud_->is_dense = false;
    kdtree_.setInputCloud(target_cloud_);
}


Mat32d ComputeJacobian(const SE2& pose, const Eigen::Vector2d& point) {
    // Extract translation and rotation from the pose
    Eigen::Vector2d translation = pose.translation();
    double rotation = pose.so2().log(); // Assuming so2() returns the rotation in log form

    // Rotation matrix
    double cos_theta = cos(rotation);
    double sin_theta = sin(rotation);

    // Point coordinates
    double x = point.x();
    double y = point.y();

    // Compute Jacobian
    Mat32d J;
    J(0, 0) = 1; // Partial derivative of x' with respect to translation x
    J(0, 1) = 0; // Partial derivative of x' with respect to translation y
    J(1, 0) = 0; // Partial derivative of y' with respect to translation x
    J(1, 1) = 1; // Partial derivative of y' with respect to translation y

    // Partial derivatives with respect to rotation
    J(2, 0) = -sin_theta * x - cos_theta * y; //dx / dtheta
    J(2, 1) = cos_theta * x - sin_theta * y; //dy / dtheta

    return J;
}

}  // namespace sad