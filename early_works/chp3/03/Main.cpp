#include <iostream>
#include "console.h"
#include "string"
#include "error.h"
using namespace std;

/*
 */
// prototype
string mysubstr (const string &str,int pos,int n);
string mysubstr (const string &str,int pos);
//main
int main() {
    string test1 = "ABCDEFG";
    string output1 = mysubstr(test1,2);
    cout<<output1;
    cout<<endl<<"....."<<endl;
    string test2 = "ABCDEFG";
    string output2 = mysubstr(test2,2,3);
    cout<<output2;
    cout<<endl<<"....."<<endl;
    string test3 = "ABCDEFG";
    string output3 = mysubstr(test3,99,3);
    cout<<output3;

    return 0;
}

string mysubstr (const string &str,int pos,int n ){


    int strlen = str.size();
    if (pos > strlen-1) error("invalid input of pos");
    string result;
    if(n > strlen) {n = strlen-pos;}
    for(int i = 0;i<n;i++){
        result+=str[pos+i];
    }
    return result;

}

string mysubstr (const string &str,int pos){

    string result;
    int strlen = str.size();
    int n = strlen-pos;
    if (pos > strlen-1) error("invalid input of pos");
    for(int i = 0;i<n;i++){
        result+=str[i+pos];
    }
    return result;

}
