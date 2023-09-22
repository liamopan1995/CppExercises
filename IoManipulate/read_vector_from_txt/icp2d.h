/*
Class: ICP 2d  Implementation 
*/
#ifndef ICP_2D_CLASS
#define ICP_2D_CLASS
#include "common/utilities.h"
#include "kdtree.h"
#include <numeric>
#include <glog/logging.h>
#include "bfnn.h"

struct MovementData {
    double timestamp_;
    Mat3d R_= Mat3d::Identity();
    Eigen::Vector3d v_;
    Eigen::Vector3d p_;

    MovementData() 
        : timestamp_(0.0), v_(Eigen::Vector3d::Zero()), p_(Eigen::Vector3d::Zero()) {} 
    
    MovementData(double timestamp, 
            const Mat3d &rotation_matrix = Mat3d::Identity(),
            const Eigen::Vector3d &velocity = Eigen::Vector3d::Zero(),
            const Eigen::Vector3d &position = Eigen::Vector3d::Zero())
        : timestamp_(timestamp),  v_(velocity), p_(position),R_(rotation_matrix) {}
};


class Icp2d {
   public:
    struct Options {
        ///int max_iteration_ = 20;                // 最大迭代次数
        double max_nn_distance_ = 1.0;          // 点到点最近邻查找时阈值
        int min_effective_pts_ = 10;            // 最近邻点数阈值
        ///double eps_ = 1e-2;                     // 收敛判定条件
        bool use_initial_translation_ = false;  // 是否使用初始位姿中的平移估计
    };

    Icp2d() {}
    Icp2d(Options options) : options_(options) {}

    /// 设置目标的Scan
    void SetTarget(std::vector<Vec3d>  target) {
        target_ = target;
        //BuildTargetKdTree();

        // 计算点云中心
        target_center_ = std::accumulate(target_.begin(), target_.end(), Vec3d::Zero().eval(),
                                         [](const Vec3d& c, const Vec3d& pt) -> Vec3d { return c + pt; }) /
                         target_.size();
        LOG(INFO) << "target center: " << target_center_.transpose();
    }

    /// 设置被配准的Scan
    void SetSource(std::vector<Vec3d> source) {
        source_ = source;
        source_center_ = std::accumulate(source_.begin(), source_.end(), Vec3d::Zero().eval(),
                                         [](const Vec3d& c, const Vec3d& pt) -> Vec3d { return c + pt; }) /
                         source_.size();
        LOG(INFO) << "source center: " << source_center_.transpose();
    }

    void SetGroundTruth(const SE2& gt_pose) {
        gt_pose_ = gt_pose;
        gt_set_ = true;
    }

    /// 使用gauss-newton方法进行配准, 点到点
    //bool AlignP2P(SE3& init_pose);

    /// 使用gauss-newton方法进行配准, 点到点, find nn via brutal force
    /// Implement this

    int check_matches(std::vector<std::pair<size_t, size_t>>& matches);

    bool pose_estimation_3d3d(
        // Mat3d& R, Vec3d& t
    );
    bool isSourceSet()const {
        return !source_.empty();
    } 

    MovementData Get_Odometry()const{
        return MovementData(0, R_,Vec3d(0, 0, 0), t_);
    }


    //     IMUData Get_IMU () const{ 
    // return IMUData(current_time_, 
    //                Sophus::SO3(Eigen::Matrix3d::Identity()), 
    //                Eigen::Vector3d(v_ *cos(sphi_), v_ *sin(sphi_), 0), 
    //                Eigen::Vector3d(sx_, sy_, 0));
   private:
    // 建立目标点云的Kdtree
    //void BuildTargetKdTree();

    std::shared_ptr<sad::KdTree> kdtree_ = nullptr;  // 第5章的kd树

    std::vector<Vec3d>  target_ ;
    std::vector<Vec3d>  source_ ;

    Vec3d target_center_ = Vec3d::Zero();
    Vec3d source_center_ = Vec3d::Zero();

    bool gt_set_ = false;  // 真值是否设置
    SE2 gt_pose_;// the ground  truth: translation & rotaion  that aligns the target to the source

    Options options_;
    Mat3d R_ = Mat3d::Zero();
    Vec3d t_ = Vec3d::Zero();
};

#endif  // ICP_2D_CLASS