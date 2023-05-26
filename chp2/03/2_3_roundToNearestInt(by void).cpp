/******************************************************************************
 *                              ------------
                                **TEMPLATE**
                                -------------
                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/



/*
 * File: roundToNearestInt.cpp
 * ---------------------
 *  a program  rounding  a  floating-point  value  to  the  nearest  integer. 

for example:  roundToNearestInt(1.3) = 1

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
using namespace std;

/* Function prototypes */

void roundToNearestInt(float n,int & rounded);
void showRounded (int rounded);
void getRoundee (float & n);

/* Global Variables Declaration */
  //全局变量定义在程序体中， 即main 和其他函数的函数体外
  
/* Main program */
int main() {
    int rounded = 0;
    float toRound = 0;
    while(true) {
    cout<<" input a number to  be rounded , by entering 0 to stop "<<endl;
   getRoundee ( toRound);
   roundToNearestInt(toRound, rounded);
   showRounded (rounded);
   if (toRound == 0) break;
    }
    cout<< "the testing procedure has been terminated !";
   return 0;
}


/*
 * Function: getDigit
 * Usage:  void roundToNearestInt(float n);
 * ------------------
 * this rounding  a  floating-point  value  to  the  nearest  integer, case differs depending on n is neagtive or positive
 */
void roundToNearestInt(float n,int &rounded)
{
    if (n >0){
    rounded = int(n+0.5);}
    else rounded =int(n-0.5);
    
}

/*
 * Function: getDigit
 * Usage:  void roundToNearestInt(float n);
 * ------------------
 * this rounding  a  floating-point  value  to  the  nearest  integer, case differs depending on n is neagtive or positive
 */
void showRounded (int rounded){
cout << "rounded number is: "<<rounded <<endl;}

/*
 * Function: getRoundee
 * Usage:  void getRoundeet(float &n);
 * ------------------
 * get the to rounded number from iostream
 */
void getRoundee (float & toRound)
{
   cout<<"please give a number to be rounded: "<<endl;
   cin>> toRound;
}
/*
 * Function: error
 * Usage: error(msg);
 * ------------------
 * Writes the string msg to the cerr stream and then exits the program
 * with a standard status value indicating that a failure has occurred.
 */
void error(string msg) {
   cerr << msg << endl;
   exit(EXIT_FAILURE);
}


