#ifndef CIRCLE_H  
#define CIRCLE_H  

#include <Eigen/Dense>


//
//						 circle.h
//
/************************************************************************
			DECLARATION OF THE CLASS CIRCLE
************************************************************************/
// Class for Circle
// A circle has 7 fields: 
//     Px, Py,Pz,  r (of type reals), the circle parameters
//     s (of type reals), the estimate of sigma (standard deviation)
//     g (of type reals), the norm of the gradient of the objective function
//     i and j (of type int), the iteration counters (outer and inner, respectively)  later delte the unrelated parts
//     a normal , (and a auxiliary vector u)  (newly added)


//TODO : modify the sigma function in Utilities


#include"mystuff.h"


class Circle
{
public:

	// The fields of a Circle
	reals Px, Py, Pz, r, s, g, Gx, Gy;
	int i, j;
	Eigen::Vector3f  normal;// norm Vector
	Eigen::Vector3f  u;    // Orthonormal vectors n, u, <n,u>=0  for generating points on the circle in space from its coefficients.

	// constructors
	Circle();
	Circle(reals aa, reals bb, reals cc, reals rr);

	// helpers
	void computeMSE_3d(const Eigen::Matrix<float, Eigen::Dynamic, 3>& dataPoints);
	void computeMSE_2d(const Eigen::MatrixXf & dataPoints);
	Eigen::Matrix<float, Eigen::Dynamic, 3> generate_circle(void);

	// routines
	void print(void);

	// no destructor we didn't allocate memory by hand.
};


/************************************************************************
			BODY OF THE MEMBER ROUTINES
************************************************************************/
// Default constructor

Circle::Circle()
{
	Px=0.; Py=0.;Pz=0.; r=1.; s=0.; i=0; j=0;
}

// Constructor with assignment of the circle parameters only

Circle::Circle(reals aa, reals bb, reals cc, reals rr)
{
	Px=aa; Py=bb; Pz=cc;r=rr;
}


void Circle::computeMSE_3d(const Eigen::Matrix<float, Eigen::Dynamic, 3>& dataPoints)
/*
This function computes the Mean Squared Error (MSE) given a set of data points and an estimated circle.

Parameters:
	dataPoints (Eigen::Matrix<float, Eigen::Dynamic, 3>&): A matrix containing data points, where each row represents a point with (x, y, z) coordinates.

*/
{

    // Calculate the center of the estimated circle.
    Eigen::Vector3f center(Px, Py, Pz);

	//std::cout<<"\n center :\n"<<center<<std::endl;

    // Compute the squared differences between data points and the circle center. (dataPoints is of shape <n,3>! )
    Eigen::Matrix<float, Eigen::Dynamic, 1> squaredDistances = (dataPoints.rowwise() - center.transpose()).array().square().rowwise().sum();

    // Calculate the square root of each squared distance, then calculate the mean.
    std::cout<<"\n MSE 3d :\n"<<(squaredDistances.array().sqrt() - r).array().square().sqrt().mean();
	


}

void Circle::computeMSE_2d(const Eigen::MatrixXf & dataPoints)
/*
This function computes the Mean Squared Error on rotated plane (MSE) given a set of data points and an estimated circle.

Parameters:
	dataPoints (Eigen::Matrix<float, Eigen::Dynamic, 3>&): A matrix containing data points, where each row represents a point with (x, y, z) coordinates.

*/
{
	// print();
    // Calculate the center of the estimated circle.
    Eigen::Vector2f center(Px, Py);
	// std::cout<<"\n center :\n"<<center<<std::endl;
    // Compute the squared differences between data points and the circle center. (dataPoints is of shape <n,3>! )
    Eigen::Matrix<float, Eigen::Dynamic, 1> squaredDistances = (dataPoints.leftCols<2>().rowwise() - center.transpose()).array().square().rowwise().sum();
	// std::cout<<"\n squaredDistances :\n"<<squaredDistances<<std::endl;


    // Calculate the square root of each squared distance, then calculate the mean.
    s  = (squaredDistances.array().sqrt() - r).array().square().sqrt().mean();
	std::cout<<"\n MSE 2d :\n"<<s<<std::endl;

}

// Printing routine

void Circle::print(void)
{
	cout << endl;
	cout << setprecision(10) << "center (" <<Px <<","<< Py <<","<< Pz<<")  radius " 
	<< r << "  MSE: " << s << endl;
	cout <<"normal vector\n"<< normal << endl;
}


#endif //CIRCLE_H