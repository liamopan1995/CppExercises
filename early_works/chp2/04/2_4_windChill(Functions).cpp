/******************************************************************************
 *                              ------------
                                **TEMPLATE**
                                -------------
                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/



/*
 * File: windChill.cpp
 * ---------------------
 *  a program windChill that takes the values of t and v and returns the 
wind chill.

Formula  IS :  wind chill (Fahrenheit) = 35.74 + 0.6215 * T +35.75 * (pow(v,o.16)) +0.4275 * T * (pow(v,o.16))
•  If there is no wind, windChill should return the original temperature t. 
•  If  the  temperature  is  greater  than  40° F,  the  wind  chill  is  undefined,  and 
your function should call error with an appropriate message. 

 */
 
 
 /*
 * Notifications  after complete this      （********笔记********）
   A.    函数定义后的花括号后 不需要有分号  void error(string msg) { }
   B.   C++ 的Boolean 1 为正确 0 为错误  （注意-1 不代表错误 i。e。“非”）
   C.   全局变量定义在程序体中， 即main 和其他函数的函数体外
   D.   写完 function prototype后 把他复制到 Function declaration 里， 省得经常 上下 arguments 类型有偏差
 * ---------------------
 * 
 */
 
 
/* lib import*/

#include <iostream>
#include<math.h> // pow(,)
using namespace std;

/* Function prototypes */

  void getData ( float &windSpeed,float&temperature);
  void computewindChill(float windSpeed,float temperature,float & windChill);
  void showWindCill (float windChill);

/* Global Variables Declaration */
  //全局变量定义在程序体中， 即main 和其他函数的函数体外
  
/* Main program */
int main() {
    float windSpeed = 0;
    float temperature = 0;
    float windChill = 0;
   getData ( windSpeed,temperature);
   computewindChill(windSpeed,temperature,windChill);
   showWindCill (windChill);
   
   return 0;
}

/*
 * Function: getData
 * Usage:  getData( float &windSpeed,float&temperature);
 * ------------------
 * this function get temperature and windSpeed from user
 */
  void getData ( float &windSpeed,float&temperature)
{
    cout<< "temperature"<<endl;
    cin>>temperature;
    cout<< "windSpeed"<<endl;
    cin>>windSpeed;
    
    
}

/*
 * Function: computewindChill
 * Usage:  computewindChill(float windSpeed,float temperature,float & temperature, );
 * ------------------
 * this function compute the windChill with the given windSpeed and temperature
 */
  void computewindChill(float windSpeed,float temperature,float & windChill)
{
    windChill = int(35.74 + 0.6215 * temperature -35.75 * pow(windSpeed,0.16) +0.4275 * temperature * pow(windSpeed,0.16));
    
}

/*
 * Function: showWindCill
 * Usage:   showWindCill (float windChill);
 * ------------------
 * this fuction show resulted windChill throught iostream by cout
 */
void showWindCill (float windChill){
cout <<windChill <<endl;}


/*
 * Function: error
 * Usage:   errorl (msg);
 * ------------------
 * throw info msg and terminate running
 */


void error(string msg) {
   cerr << msg << endl;
   exit(EXIT_FAILURE);
}


