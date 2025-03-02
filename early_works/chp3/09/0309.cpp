#include <iostream>
// #include "console.h"
using namespace std;

/*
 */

//constants

//prototype
string removeDoubledLetters (string str);

//main
int main() {
    /* Some sample code . */

    string test1 = "bookkeepeeerrrrr";
    string output1  = removeDoubledLetters(test1);
    cout<<"original string: "<<test1<<endl;
    cout<<output1<<endl;
    string test2 = "bookkeeper";
    cout<<"original string: "<<test2<<endl;

    string output2  = removeDoubledLetters(test2);
    cout<<output2<<endl;
    string test3 = "";
    cout<<"see if it can handel empty string"<<endl;
    cout<<"original string: "<<test3<<endl;

    string output3  = removeDoubledLetters(test3);
    cout<<output3<<endl;
    return 0;
}

//declaration
string removeDoubledLetters (string str){
    string output;
    char currentChar=str[0];
    for(int i=0;i<str.size();i++){
        if (str[i]!=currentChar){
            //if(i<str.size()){
                output+=str[i-1];
                currentChar = str[i];
            //}
        }
    }
    //if (str[str.size()-1] != str[str.size()-2])
    output +=str[str.size()-1]; // since we never get to check the last letter
    return output;
}
