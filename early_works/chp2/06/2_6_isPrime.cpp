/******************************************************************************
 *                              ------------
                                **TEMPLATE**
                                -------------
                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/



/*
 * File: isPrime.cpp
 * ---------------------
 *  a program  reads  in  an  integer  and  then  predicts whether it is a prime, . 
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

bool isPrime(int n);


/* Global Variables Declaration */
  //全局变量定义在程序体中， 即main 和其他函数的函数体外
  
/* Main program */
int main() {
    for(int j=1;j<=100;j++){
    if(isPrime(j)==1){
   cout<<"found a new prime which is :"<<j<<endl;} // expected result :1
}
return 0;
}

/*
 * Function: isPrime
 * Usage: bool d = isPrime(int p);
 * ------------------
 * this Function predicts whether the integer p is prime 
 */
bool isPrime(int p){
    bool isprime = true;
    int i= 1;
    while(i<=p)
    {
    
        if((p%i)==0&&i!=p&&i!=1||p==1){         //   ||p==1  : or when p equal to 1
            isprime = false;
            break;
        }
        i++;
    }
    return isprime;
}



