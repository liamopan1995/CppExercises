/******************************************************************************
 *                              ------------
                                **TEMPLATE**
                                -------------
                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/



/*
 * File: sqrt.cpp
 * ---------------------
 *  a program  reads  in  an  number and return the square root of it. 

for example:  mySqrt(9) = 3;

 */
 
 
 /*
 * Notifications  after complete this      （********笔记********）
   A.   C++没有求幂的运算符，  
   B.   C++ 的Boolean 1 为正确 0 为错误  （注意-1 不代表错误 i。e。“非”）
   C.   全局变量定义在程序体中， 即main 和其他函数的函数体外
   D. 
 * ---------------------
 * T
 */
 
 
/* lib import*/

#include <iostream>
using namespace std;

/* Function prototypes */

float mySqrt(float n);


/* Global Variables Declaration */
  //全局变量定义在程序体中， 即main 和其他函数的函数体外
  
/* Main program */
int main() {
  float p = 0;
  cout<<"give a number";
  cin>>p;
  cout<<"the given number is "<<p<<endl;
  cout<<"it's square root is :"<<mySqrt(p);
  return 0;
}




/*
 * Function: mySqrt
 * Usage: float o = mySqrt(float n);
 * ------------------
 * gives the square root of that given number n
 */
float mySqrt(float x){
    float result =0;
    float g = x/2;
    while(true){
    if((g-x/g)<0.001){    // 此处允许了误差 ，因为用等于0作为条件计算量过大了 很多数是开不尽的
        result = g;
        break;
    }    
    g =0.5*(g+x/g);
    }
    return result;
}

