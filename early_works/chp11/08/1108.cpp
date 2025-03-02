#include <iostream>
#include "math.h"
using namespace std;

// Design the prototype and write the code for a function integrate that
// calculates the definite integral by summing the areas of a set of rectangles.
// For example, to calculate the area of the shaded region in the earlier example,
// the client would write
// double value = integrate(sin, 0, PI, 20);
// where the last argument is the number of rectangles into which the area gets
// divided; the larger this value, the more accurate the approximation.

double integrate(double (*fn)(double), double left, double right,  int num_slices);


int main () {
    cout << integrate(sin,0,M_PI, 800)<<endl;
    cout << integrate(sin,0,2 * M_PI, 800)<<endl;
    return 0;
}


double integrate(double (*fn)(double), double left, double right,  int num_slices){
    double spaceLen = (right - left ) / num_slices;
    double height = 0.0;

    for (int i = 0; i <= num_slices ; i++) {
        double intervalPoint = left + (i - 0.5 ) * spaceLen; 
        height += fn(intervalPoint);
    }

    return spaceLen * height;

}