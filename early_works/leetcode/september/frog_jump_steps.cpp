#include<iostream>
#include<vector>
using namespace std;

int frog_possibilities( int n){
    if(n<0) return -1;
    if (n<4) return n;

    vector<int> steps(n+1);
    steps[2] =2;
    steps[3] =3;

    for (int i=4;i<=n;i++){
        steps[i]=steps[i-1] + steps[i-2];
    }

    return steps[n];


}

int main(){
    cout<<frog_possibilities( 4)<<endl;
    return 0;
}