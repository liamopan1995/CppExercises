#ifndef UTILITIE
#define UTILITIE
#include <Eigen/Dense>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include "sophus/se3.h"
#include "sophus/se2.h"
using Vec3f = Eigen::Vector3f;
using Vec3d = Eigen::Vector3d;
using Vec6d = Eigen::Matrix<double, 6, 1>;
using Mat3d = Eigen::Matrix3d;
using Mat3f = Eigen::Matrix3f;
using Mat6d = Eigen::Matrix<double, 6, 6>;
using PointType = pcl::PointXYZI;
using PointCloudType = pcl::PointCloud<PointType>;
using CloudPtr = PointCloudType::Ptr;
using SE3 = Sophus::SE3;
using SE2 = Sophus::SE2;
using SO3 = Sophus::SO3;
using IndexVec = std::vector<int>;

inline Vec3d ToVec3d(const PointType& pt) { return pt.getVector3fMap().cast<double>(); }
inline Vec3d ToVec3d(const pcl::PointXYZRGB& pt) { return pt.getVector3fMap().cast<double>(); }

inline Vec3f ToVec3f(const PointType& pt) { return pt.getVector3fMap(); }
inline Vec3f ToVec3f(const pcl::PointXYZRGB& pt) { return pt.getVector3fMap(); }

template <typename S>
inline PointType ToPointType(const Eigen::Matrix<S, 3, 1>& pt) {
    PointType p;
    p.x = pt.x();
    p.y = pt.y();
    p.z = pt.z();
    return p;
}

#endif