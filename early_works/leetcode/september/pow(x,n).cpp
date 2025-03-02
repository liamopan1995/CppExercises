#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
        // if (n ==0) return 1;
        // if (x ==0) return 0;
        // if (x ==1) return 1;
        if (n ==1) return x;
        if (n ==-1) return 1/x;

        double half_pow = myPow(x,n/2);

        return half_pow * half_pow *  ((n%2)?   (n > 0 ? x: 1/x) : 1);
        // ((n % 2 == 0) ? 1 : (n > 0 ? x : 1/x));
    }
};

int main (){
    Solution sol;
    cout<< sol.myPow(2,10)<<endl;
    return 0;
}