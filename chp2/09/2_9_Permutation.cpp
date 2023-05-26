/******************************************************************************
 *                              ------------
                                **TEMPLATE**
                                -------------
                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/



/*
 * File: permutation.cpp
 * ---------------------
 *  a program  reads  in  two  integer  n and k , and return the permutation (n,k),which determines the number of ways you . 
    can choose k values frome n elements ,where orders of the elements also matter!
for example:  permutation(3,2)=6

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

int permu(int n,int k);



/* Global Variables Declaration */
  //全局变量定义在程序体中， 即main 和其他函数的函数体外
  
/* Main program */
int main() {
  int n= 0, k=0;
  cout<<"please indicate the scale of elements: n"<<endl;
  cin >> n;
  cout<<"please indicate the scale of choices: k"<<endl;
  cin >> k;
  cout<< permu(n,k);
   return 0;
}


/*
 * Function: permu
 * Usage: int p = permu(int n,int k);
 * ------------------
 * this Function a program  reads  in  two  integer  n and k , and return the permutation (n,k),which determines the number of ways you . 
    can choose k values frome n elements ,where orders of the elements also matter!
for example:  permutation(3,2)=6
 */

int permu(int n,int k){   //   permu(n,k) = (n-k)+1)! 
    int q = n-k+1;
    int result = 1;
    for(q;q<=n;q++){
        cout <<"q: "<<q<<endl;
        result *=q;
    }
    return result;
}
