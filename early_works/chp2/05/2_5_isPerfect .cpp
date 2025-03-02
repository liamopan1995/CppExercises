/******************************************************************************
 *                              ------------
                                **TEMPLATE**
                                -------------
                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/



/*
 * File:   isPerfect.cpp
 * ---------------------
 *  a program that takes an integer n and returns 
true  if  n  is  perfect,  and  false  otherwise...

Greek mathematicians took a special interest in numbers that are equal to the 
sum  of  their  proper  divisors  (a  proper  divisor  of  n  is  any  divisor  less  than  n 
itself).  They called such numbers perfect numbers.  For example, 6 is a perfect 
number because it is the sum of 1, 2, and 3, which are the integers less than 6 
that divide evenly into 6.  Similarly, 28 is a perfect number because it is the 
sum of 1, 2, 4, 7, and 14. 

 */
 
 
 /*
 * Notifications  after complete this      （********笔记********）
   A.    嵌套在for循环内的for循环无需进一步缩进！！
   B.   for 判断可用逻辑符 与或非 等高级的
   
   C.   do while 和 for 类似 while语句都是循环语句，功能都差不多，唯一的区别在于检验条件的时间上
         while语句在进入循环体之前要先判断条件是否成立，如果成立的话则进入循环体。 
        而do… while语句则相反，是先执行循环体，然后再判断条件是否成立
   D.   
 * ---------------------
 * 
 */
 
 
/* lib import*/

#include <iostream>
using namespace std;

/* Function prototypes */

bool isPerfect (int n);

/* Global Variables Declaration */
  //全局变量定义在程序体中， 即main 和其他函数的函数体外
  
/* Main program */
int main() {
  
for (int i=1;i<=9999;i++){
    
    if(isPerfect(i)==1)
    cout<<"found a new perfect number which is: "<<i<<endl;
    
}

    
return 0;
}

/*
 * Function: isperfect
 * Usage:  isperfect(int n);
 * ------------------
 * that takes an integer n and returns true  if  n  is  perfect,  and  false  otherwise.
 */
bool isPerfect( int n){  
bool isture = false ;
int k = n;
// int i=1;                       // 同样的功能用do while 实现如下：
// do
// {
// if (n%i==0) k = k-i;
// cout <<"k"<<k<<" ";
// i++;
// }
// while (k>0&&i<=n);  
// if (k==0)isture = true;
// if (k<0)  isture = false;
        
for (int i=1;i<n;i++){ // for 循环也能够并联多个条件的 用&& 与， 也可以用或等逻辑操作符！
    if(n%i==0) k=k-i;
}

if (k==0)isture = true;
if (k<0)  isture = false;     
return isture;
}


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


