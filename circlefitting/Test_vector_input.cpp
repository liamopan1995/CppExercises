#include <iostream>
#include <vector>
#include "CircleFitByLeastSquare.cpp"
#include "CircleFitByHyper.cpp"
#include <Eigen/Dense>
#include <cmath> 
#include "circle.h"

void fit_plane( Eigen::Matrix<float, Eigen::Dynamic, 3>& P, Eigen::Vector3f& P_mean, Eigen::Vector3f& normal, float& d) {
    /*
    This function takes points and find its centriod, and the normal vector of the plane that most points are close to 
    not sure what if the use of d..
    After running fit_plane , P actually refer to the points been centerized, 
    */

    P_mean = P.colwise().mean(); // Calculate mean along columns
    std::cout<< "p_mean in fit_plane inside:"<< P_mean<<std::endl;  
    // simply save P_centered in P instead create a new P_centered object
    // Eigen::Matrix<float, Eigen::Dynamic, 3> P_centered = P.rowwise() - P_mean.transpose();
    // Eigen::JacobiSVD<Eigen::Matrix<float, Eigen::Dynamic, 3>> svd(P_centered, Eigen::ComputeFullU | Eigen::ComputeFullV);

    P = P.rowwise() - P_mean.transpose();
    Eigen::JacobiSVD<Eigen::Matrix<float, Eigen::Dynamic, 3>> svd(P, Eigen::ComputeFullU | Eigen::ComputeFullV);
    Eigen::Matrix3f V = svd.matrixV();

    normal = -1 * V.col(2); // Third column of V
    d = -P_mean.dot(normal); // d = -<p,n>

}


/*
The following rodrigues_rot function implementation is not accelerated by vectorization
*/


Eigen::MatrixXf rodrigues_rot_original(const Eigen::MatrixXf& P, const Eigen::Vector3f& n0, const Eigen::Vector3f& n1)
/*
    This function takes and then rotates the points in 3d from the plane define by n0 , 
    into the X-Y plane ,it returns a matrix of shape (n,3)
*/ 
{

    Eigen::MatrixXf P_rot = Eigen::MatrixXf::Zero(P.rows(), 3);

    Eigen::Vector3f n0_norm =  n0.normalized();
    Eigen::Vector3f n1_norm = n1.normalized();
    
    // Get the axis around which the rotation is be applied
    Eigen::Vector3f k = n0_norm.cross(n1_norm);
    k.normalize();
    std::cout<<"\ndot product:\n"<<n0_norm.dot(n1_norm)<<std::endl;
    // Get the radian for which the rotation is applied 
    float theta = std::acos(n0_norm.dot(n1_norm)); //  has same effort of applying dot product with [0,0,1]


    // Compute the points coords after rotation.
    for (int i = 0; i < P.rows(); ++i) {
        /*
        seeking a way to write it in vectorizd form
        */
        Eigen::Vector3f P_row = P.row(i); // Convert row to a 3D vector
        P_rot.row(i)  = P_row * std::cos(theta) + k.cross(P_row) * std::sin(theta) + k * k.dot(P_row) * (1 - std::cos(theta));
    }


    std::cout<<"\nn0:\n"<<n0_norm<<"\nn1:\n"<<n1_norm<<"\nk:\n"<<k<<"\ntheta:\n"<< theta <<"\n P_rot:\n "<<P_rot<<std::endl;

    return P_rot;
}




Eigen::MatrixXf rodrigues_rot_vec(const Eigen::MatrixXf& P, const Eigen::Vector3f& n0, const Eigen::Vector3f& n1) 
/*
    This function takes and then rotates the points in 3d from the plane define by n0 , 
    into the X-Y plane ,it returns a matrix of shape (n,3)
*/
{
    Eigen::MatrixXf P_rot = Eigen::MatrixXf::Zero(P.rows(), 3);
    Eigen::Vector3f n0_norm =  n0.normalized(); // -1 *
    Eigen::Vector3f n1_norm = n1.normalized();
    Eigen::Vector3f k = n0_norm.cross(n1_norm);
    k.normalize();


    float theta = std::acos( n0_norm.dot(n1_norm));
    Eigen::Matrix3f rot_matrix;

    rot_matrix = Eigen::AngleAxisf(theta, k);
    Eigen::MatrixXf P_rot2 = Eigen::MatrixXf::Zero(P.rows(), 3);
    P_rot2 = P * rot_matrix.transpose();

    std::cout<<"\n P_rot2:\n"<<P_rot2<<std::endl;


    Eigen::Matrix3f I = Eigen::Matrix3f::Identity(); // Identity matrix
    Eigen::Matrix3f K = Eigen::Matrix3f::Zero();
    K <<  0, -k(2), k(1),
          k(2), 0, -k(0),
         -k(1), k(0), 0;

    Eigen::Matrix3f R = I + std::sin(theta) * K + (1 - std::cos(theta)) * K * K;

    P_rot = P * R.transpose();

    return P_rot;
}


Eigen::MatrixXf rodrigues_rot_lib(const Eigen::MatrixXf& P, const Eigen::Vector3f& n0, const Eigen::Vector3f& n1) 
/*
    This function takes and then rotates the points in 3d from the plane define by n0 , 
    into the X-Y plane ,it returns a matrix of shape (n,3)
*/
{
    Eigen::MatrixXf P_rot = Eigen::MatrixXf::Zero(P.rows(), 3);
    Eigen::Matrix3f rot_matrix;

    Eigen::Vector3f n0_norm =  n0.normalized();
    Eigen::Vector3f n1_norm = n1.normalized();
    Eigen::Vector3f k = n0_norm.cross(n1_norm);
    k.normalize();

    float theta = std::acos(n0_norm.dot(n1_norm));
    rot_matrix = Eigen::AngleAxisf(theta, k);
    std::cout<< "rot matrix \n"<<rot_matrix<<std::endl;
    P_rot = P * rot_matrix.transpose();
    return P_rot;
}


Circle CircleFitting_3D( Eigen::Matrix<float, Eigen::Dynamic, 3> P)
/*  
    A wrapper function, which does follows:

        1. Take a set of points <x,y,z>  : P 
        2. Compute its mean : P_mean and norml: normal
        3. Use one of the the rodrigues_rot function to rotate the points in 3D onto the x-y plane Pxy
        4. Apply a circle fitting function in 2d , which results at first the fitted circle on x-y plane
        5. Rerotate the circle back to 3D, and updates its coeffients accordingly.(rodrigues_rot is used again for reversion)

    This function still can be improved by modifying the ways of passing arguments, by pointers, or references
    TODO: .. 
*/
{   
    Circle circle;
    Eigen::Vector3f P_mean = Eigen::Vector3f::Zero();
    Eigen::Vector3f normal = Eigen::Vector3f::Zero();
    Eigen::MatrixXf Pxyz  = Eigen::MatrixXf::Zero(1, 3);
    float d = 0.0;
    fit_plane(P,P_mean,normal,d);
    Eigen::Vector3f n1(0.0, 0.0, 1);
    // std::cout<< "P_mean inside CF 3d is:"<< P_mean<<endl;
    Eigen::MatrixXf Pxy = rodrigues_rot_lib(P, normal, n1); 
    
    //circle = CircleFitByLeastSquare_vectorized (P_rot);
    circle = CircleFitByHyper_vectorized (Pxy);
    // std::cout<<" circle.Px, circle.Py:  "<< circle.Px << ","<<circle.Py<<std::endl;

    // //Remap the circle center into 3d space
    Pxyz  = rodrigues_rot_original(Eigen::Matrix<float, 1, 3> (circle.Px, circle.Py, 0) ,n1,  normal);
    // std::cout<<" PXYZ ' FIRST ELEMENT :"<< Pxyz(0);
    // circle.Px = P_circle_3d(0) + P_mean(0);
    circle.Px = Pxyz(0) + P_mean(0);
    circle.Py = Pxyz(1) + P_mean(1);
    circle.Pz = Pxyz(2) + P_mean(2);
    // write the normal into circle.
    circle.normal =  normal;

    return circle;
}
    


int main() {

/*
    Testing of function with vector as input
*/
    // std::vector<double> x = {1.0, 2.0, 3.0};
    // std::vector<double> y = {2.0, 4.0, 6.0};
    // std::vector<double> w = {1.0, 0.5, 2.0};

    // auto result = CircleFitByLeastSquare(x, y, w);
    // std::cout << "xc: " << std::get<0>(result) << ", yc: " << std::get<1>(result) << ", r: " << std::get<2>(result) << std::endl;



/*
    Code snippet :  Writing the cloud points into a matrix 

*/
    Eigen::Matrix<double, Eigen::Dynamic, 3> pointsMatrix; // Dynamic-sized matrix for points

    // Simulate adding points dynamically
    for (int i = 0; i < 5; ++i) {
        double x = i * 1.0;
        double y = i * 2.0;
        double z = i * 3.0;
        pointsMatrix.conservativeResize(pointsMatrix.rows() + 1, Eigen::NoChange);
        pointsMatrix.row(pointsMatrix.rows() - 1) << x, y, z;
    }

    // Printing the points matrix
    // std::cout << "Points Matrix:" << std::endl;
    // std::cout << pointsMatrix << std::endl;


/*
    Manually construct a P using the snippet above, P is sampled from python DiskFitting

*/  
    // Points in 3D :P  n=10   radian=" 1 " ;

    // Define the values of x, y, and z
    float x_values[] = {1.01, 0.94, 0.79, 0.48, 0.15, -0.25, -0.46, -0.71, -1.13, -0.96};
    float y_values[] = {0.04, 0.43, 0.65, 0.76, 1.04, 0.87, 1.13, 0.87, 0.43, -0.12};
    float z_values[] = {0.52, 0.78, 0.64, 0.67, 0.36, -0.01, -0.24, -0.31, -0.60, -0.78};

    Eigen::Matrix<float, Eigen::Dynamic, 3> P; // Dynamic-sized matrix for points

    for (int i = 0; i < 10; ++i) {
        P.conservativeResize(P.rows() + 1, Eigen::NoChange);  // Add a row
        // P(P.rows() - 1, 0) = x_values[i];  // Set x values in the first column
        // P(P.rows() - 1, 1) = y_values[i];  // Set y values in the second column
        // P(P.rows() - 1, 2) = z_values[i];  // Set z values in the third column
        P.row(P.rows() - 1) << x_values[i], y_values[i], z_values[i];
    }



    

/*
    Testing of single units:
                            1.rodrigues_rot_original, 
                            2.rodrigues_rot_vec,
                            3.rodrigues_rot_lib,
                            4.CircleFitByLeastSquare_vectorized
                            5.CircleFitByHyper_vectorized
*/

    // Printing the matrix P
    // std::cout << "Matrix P:\n" << P << std::endl;


    // Eigen::Vector3f P_mean = Eigen::Vector3f::Zero();
    // Eigen::Vector3f normal = Eigen::Vector3f::Zero();
    // float d = 0.0;
    // fit_plane(P,P_mean,normal,d);
    // P_mean = P.colwise().mean().transpose();
    // std::cout << "\n P_mean:\n" << P_mean << std::endl;  
    // // std::cout << "P_mean:\n " << P_mean.transpose() << std::endl;
    // // std::cout << "Normal: " << normal.transpose() << std::endl;
    // // std::cout << "d: " << d << std::endl;
    // std::cout << "\nMatrix P_centered:\n" << P << std::endl;    

    // Eigen::Vector3f n1(0.0, 0.0, 1);
    // //Eigen::MatrixXf P_rot = rodrigues_rot_original(P, normal, n1);
    // //Eigen::MatrixXf P_rot = rodrigues_rot_vec(P, normal, n1);
    // Eigen::MatrixXf P_rot = rodrigues_rot_lib(P, normal, n1);

    // std::cout << "\nP_rot:\n" << P_rot << std::endl;


    // Eigen::Matrix<float, Eigen::Dynamic, 3> P_centered = P.rowwise() - P_mean.transpose();



    // std::cout << "P_centered:\n " << P_centered << std::endl;

    // Eigen::JacobiSVD<Eigen::Matrix<float, Eigen::Dynamic, 3>> svd(P_centered, Eigen::ComputeFullU | Eigen::ComputeFullV);
    // Eigen::Matrix3f V = svd.matrixV();
    // std::cout << "V:\n " << V << std::endl;
    // normal = V.col(2); // Third column of V

    // std::cout << "normal:\n " << normal.transpose() << std::endl;

    // d = -P_mean.dot(normal); // d = -<p,n>

    // std::cout << "d:\n " << d << std::endl;

    // Circle circle = CircleFitByLeastSquare_vectorized (P_rot);
    // cout << "\n  LS  fit:  center (" 
    //       << circle.Px <<","<< circle.Py <<")  radius "
    //       << circle.r << "  sigma  modify this later" <<std::endl;

    // Circle circle2 = CircleFitByHyper_vectorized (P_rot);
    //     cout << "\n  Hyper  fit:  center (" 
    //       << circle2.Px <<","<< circle2.Py <<circle2.Pz<<")  radius "
    //       << circle2.r << "  sigma  modify this later" <<std::endl;


/*  
    After testing of each unit was succed , encapsulize them into one single wrapepr function called CircleFitting_3D.
    Test of the wrapper function : CircleFitting_3D 
*/

    Circle circle = CircleFitting_3D(P);

    circle.print();

    return 0;



}








