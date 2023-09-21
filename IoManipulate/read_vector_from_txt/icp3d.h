/*
Class: ICP 3d  Implementation 
*/
#ifndef ICP_3D_CLASS
#define ICP_3D_CLASS
#include "common/utilities.h"
#include "kdtree.h"
#include <numeric>
#include <glog/logging.h>

class Icp3d {
   public:
    struct Options {
        int max_iteration_ = 20;                // 最大迭代次数
        double max_nn_distance_ = 1.0;          // 点到点最近邻查找时阈值
        int min_effective_pts_ = 10;            // 最近邻点数阈值
        double eps_ = 1e-2;                     // 收敛判定条件
        bool use_initial_translation_ = false;  // 是否使用初始位姿中的平移估计
    };

    Icp3d() {}
    Icp3d(Options options) : options_(options) {}

    /// 设置目标的Scan
    void SetTarget(CloudPtr target) {
        target_ = target;
        BuildTargetKdTree();

        // 计算点云中心
        target_center_ = std::accumulate(target->points.begin(), target_->points.end(), Vec3d::Zero().eval(),
                                         [](const Vec3d& c, const PointType& pt) -> Vec3d { return c + ToVec3d(pt); }) /
                         target_->size();
        LOG(INFO) << "target center: " << target_center_.transpose();
    }

    /// 设置被配准的Scan
    void SetSource(CloudPtr source) {
        source_ = source;
        source_center_ = std::accumulate(source_->points.begin(), source_->points.end(), Vec3d::Zero().eval(),
                                         [](const Vec3d& c, const PointType& pt) -> Vec3d { return c + ToVec3d(pt); }) /
                         source_->size();
        LOG(INFO) << "source center: " << source_center_.transpose();
    }

    void SetGroundTruth(const SE3& gt_pose) {
        gt_pose_ = gt_pose;
        gt_set_ = true;
    }

    /// 使用gauss-newton方法进行配准, 点到点
    bool AlignP2P(SE3& init_pose);

    /// 使用gauss-newton方法进行配准, 点到点, find nn via brutal force
    /// Implement this
    bool AlignP2P_bf(SE3& init_pose);


   private:
    // 建立目标点云的Kdtree
    void BuildTargetKdTree();

    std::shared_ptr<sad::KdTree> kdtree_ = nullptr;  // 第5章的kd树

    CloudPtr target_ = nullptr;
    CloudPtr source_ = nullptr;

    Vec3d target_center_ = Vec3d::Zero();
    Vec3d source_center_ = Vec3d::Zero();

    bool gt_set_ = false;  // 真值是否设置
    SE3 gt_pose_;// the ground  truth: translation & rotaion  that aligns the target to the source

    Options options_;
};

#endif  // ICP_3D_CLASS