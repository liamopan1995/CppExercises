#include "icp2d.h"


// int Icp2d::check_matches(std::vector<std::pair<size_t, size_t>>& matches){
//     // keep the pairs whichs distance is under threshold 
//     // ruturns the final lentth of matches after excluding those invalid pairs
//     int i= 0;
//     const double MAX_DISTANCE_SQUARED = 2.5; // 

//     for(int j=0;j<matches.size();j++){
//         double dis = (target_[matches[j].first] - source_[matches[j].second]).squaredNorm();
//         if(dis < MAX_DISTANCE_SQUARED){
//             matches[i] = matches[j];
//             i++;
//         } else {
//             std::cout<< "*******************distance exceeds the threshold! for the pair****************:\n   "<<
//                 matches[j].first<<"and "<<matches[j].second<< "\ndistance: "<<dis<<std::endl;
//         }
//     }
//     matches = std::vector<std::pair<size_t, size_t>>(matches.begin(),matches.begin()+i);
//     return i;
// }



// void Icp2d::pose_estimation_3d3d (
//     // Mat3d& R, Vec3d& t
//     )
//     // compute the pose esimation by SE3 , for convinience , taking 2d cases as
//     // a special case in 3d space , und therefore format the issue in SE3 
//     // increase reusability and save time for development the 2d version . 
// {

//     std::vector<std::pair<size_t, size_t>>matches;
//     bfnn_cloud_mt(target_,source_,matches);
//     assert(matches.size() != 0);
//     int N = check_matches(matches);
//     std::cout<<"N: "<<N<<std::endl;

//     for( auto pair : matches) {
//         std::cout<<"idx: "<<pair.first<<" : "<< target_[pair.first].transpose()<<std::endl;
//         std::cout<<"pa_idx: "<<pair.second<<" : "<< source_[pair.second].transpose()<<std::endl;
//         std::cout<<"dis: "<<(target_[pair.first] - source_[pair.second]).squaredNorm()<<std::endl;
        

//     }

//     std::vector<Vec3d>     target_c ( N ), source_c ( N ); // holder for  centralized points
//     Vec3d p1, p2;     // center of mass
//     for ( int i=0; i<N; i++ )
//     {
//         p1 += target_[matches[i].first].cast<double>();
//         p2 += source_[matches[i].second].cast<double>();
//     }
//     p1 /= N;
//     p2 /= N;
//     for ( int i=0; i<N; i++ )
//     {
//         target_c[i] = target_[matches[i].first].cast<double>() - p1;
//         source_c[i] = source_[matches[i].second].cast<double>() - p2;
//     }

//     Eigen::Matrix3d W = Eigen::Matrix3d::Zero();
//     for ( int i=0; i<N; i++ )
//     {
//         W += Eigen::Vector3d ( target_c[i][0], target_c[i][1], target_c[i][2] ) * Eigen::Vector3d ( source_c[i][0], source_c[i][1], source_c[i][2] ).transpose();
//     }
//     std::cout<<"W="<<W<<std::endl;

//     // SVD on W
//     Eigen::JacobiSVD<Eigen::Matrix3d> svd ( W, Eigen::ComputeFullU|Eigen::ComputeFullV );
//     Eigen::Matrix3d U = svd.matrixU();
//     Eigen::Matrix3d V = svd.matrixV();
    
//     if (U.determinant() * V.determinant() < 0)
// 	{   std::cout<<" determinant v*u <0"<<std::endl;
//         for (int x = 0; x < 3; ++x)
//         {
//             U(x, 2) *= -1;
//         }
// 	}
    
//     std::cout<<"U="<<U<<std::endl;
//     std::cout<<"V="<<V<<std::endl;

//     R_ = U* ( V.transpose() );
//     t_ = Eigen::Vector3d ( p1[0], p1[1], p1[2] ) - R_ * Eigen::Vector3d ( p2[0], p2[1], p2[2] );

// }


int Icp2d::check_matches(std::vector<std::pair<size_t, size_t>>& matches){
    int i= 0;
    const double MAX_DISTANCE_SQUARED =    2.5;
                                           // 2.5 was great//2.5; we increase the threshold
                                           // to handel the case between two two scans to be matched,
                                           // there are scans discarded for insufficient match number
                                           // it is obvious that to this case the distance between same
                                           // object in two scans of diff time points will be larger

    for(int j=0;j<matches.size();j++){
        double dis = (target_[matches[j].first] - source_[matches[j].second]).squaredNorm();
        if(dis < MAX_DISTANCE_SQUARED){
            matches[i] = matches[j];
            i++;
        } else {
            LOG(WARNING) << "*******************distance exceeds the threshold! for the pair****************:\n   "
                         << matches[j].first << "and " << matches[j].second << "\ndistance: " << dis;
        }
    }
    matches = std::vector<std::pair<size_t, size_t>>(matches.begin(),matches.begin()+i);
    return i;
}

bool Icp2d::pose_estimation_3d3d() {
    const int MIN_MATCHED_PAIR = 3;  // 3 is the minimal number of equations to determine 3 unkonw factors
    std::vector<std::pair<size_t, size_t>> matches;
    bfnn_cloud_mt(target_, source_, matches);
    assert(matches.size() != 0);
    int N = check_matches(matches);

    LOG(INFO) << "N: " << N;
    if(N < MIN_MATCHED_PAIR) return  false;

    for (auto pair : matches) {
        LOG(INFO) << "idx: " << pair.first << " : " << target_[pair.first].transpose();
        LOG(INFO) << "pa_idx: " << pair.second << " : " << source_[pair.second].transpose();
        LOG(INFO) << "dis: " << (target_[pair.first] - source_[pair.second]).squaredNorm();
    }

    std::vector<Vec3d> target_c(N), source_c(N); // holder for centralized points
    Vec3d p1, p2; // center of mass
    for (int i = 0; i < N; i++) {
        p1 += target_[matches[i].first].cast<double>();
        p2 += source_[matches[i].second].cast<double>();
    }
    p1 /= N;
    p2 /= N;
    for (int i = 0; i < N; i++) {
        target_c[i] = target_[matches[i].first].cast<double>() - p1;
        source_c[i] = source_[matches[i].second].cast<double>() - p2;
    }

    Eigen::Matrix3d W = Eigen::Matrix3d::Zero();
    for (int i = 0; i < N; i++) {
        W += Eigen::Vector3d(target_c[i][0], target_c[i][1], target_c[i][2]) *
             Eigen::Vector3d(source_c[i][0], source_c[i][1], source_c[i][2]).transpose();
    }
    LOG(INFO) << "W=" << W;

    // SVD on W
    Eigen::JacobiSVD<Eigen::Matrix3d> svd(W, Eigen::ComputeFullU | Eigen::ComputeFullV);
    Eigen::Matrix3d U = svd.matrixU();
    Eigen::Matrix3d V = svd.matrixV();

    if (U.determinant() * V.determinant() < 0) {
        LOG(INFO) << "determinant v*u <0";
        for (int x = 0; x < 3; ++x) {
            U(x, 2) *= -1;
        }
    }

    LOG(INFO) << "U=" << U;
    LOG(INFO) << "V=" << V;

    R_ = U * (V.transpose());
    t_ = Eigen::Vector3d(p1[0], p1[1], p1[2]) - R_ * Eigen::Vector3d(p2[0], p2[1], p2[2]);
    return true;
}
