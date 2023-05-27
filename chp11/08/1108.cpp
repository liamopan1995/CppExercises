#include <iostream>
#include "math.h"
using namespace std;


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