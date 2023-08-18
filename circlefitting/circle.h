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

	// constructors
	Circle();
	Circle(reals aa, reals bb, reals cc, reals rr);

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

// Printing routine

void Circle::print(void)
{
	cout << endl;
	cout << setprecision(10) << "center (" <<Px <<","<< Py <<","<< Pz<<")  radius "
		 << r << "  sigma " << s << "  gradient " << g << "  iter "<< i << "  inner " << j << endl;
	cout <<"normal vector\n"<< normal << endl;
}


#endif //CIRCLE_H