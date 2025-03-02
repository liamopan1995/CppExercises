/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;
int reverseNum(int x) {
    
    int reversedNum = 0; 

    while ( x != 0 ){
        reversedNum = reversedNum *10 + x%10;
        x /=10;
    }
    return reversedNum;
}
int main()
{
    cout<< reverseNum(139);

    return 0;
}
