/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

/*
 * File: metersToFeetAndInches.cpp
 * ---------------------
 * This program   converts a distance in meters to the corresponding English 
distance in feet and inches.
where:
1 inch = 0.0254 meters 
1 foot = 12 inches
 

 */
 
 
/*
 * Notifications
 * ---------------------
 A. use void  then you should define those input arguments in main before void is called 

 

 */
 
/* lib import*/

#include <iostream>
using namespace std;
#include <math.h>        /* fmod */
/* Function prototypes */
void metersToInches (double meters, double & feet,double & inches);

/* Main program */
int main() {
    
   double meters; 
   double feet = 0;
   double inches = 0;
   cout << "This program   converts a distance in meters to the corresponding English distance in feet and inches" << endl;
   cout << "please give a number in meters ";
   cin  >> meters;
   metersToInches(meters,feet,inches);
   return 0;
}
/*
 * Function: celsiusToFahrenheit
 * Usage: int p = celsiusToFahrenheit (int c);
 * ----------------------------------
 * Takes a temperature in degrees Celsius and Returns the 
corresponding temperature in degrees Fahrenheit. .
 */
void metersToInches (double meters, double & feet , double & inches ) {
   feet =int(meters/0.0254)/12;
   inches = fmod(meters/0.0254,12); // fmod : get the remainder
   cout << "the given number in meters : "<< meters << endl;
   cout << "is equal to "<< feet << " feet " << " and " << inches<< " inches " <<endl;
}