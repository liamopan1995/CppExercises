#include <iostream>
#include "console.h"
using namespace std;

/*
 */

//constants

//prototype
string acronym(const string &str);

//main
int main() {
    /* Some sample code . */

    string test1 = "self-contained underwater breathing apparatus.";
    string output1 = acronym(test1);
    cout<<output1<<endl;

    string test2 = "Acquired  Immune  Deficiency  Syndrome.";
    string output2 = acronym(test2);
    cout<<output2<<endl;

    string test3 = "Imag!e  Maximum";
    string output3 = acronym(test3);
    cout<<output3<<endl;


    return 0;
}

//declaration

string acronym(const string &str){
    string result;
    if ((65<=str[0]&&str[0]<=90)||(97<=str[0]&&str[0]<=122)) result+=str[0];
    bool lastwasnonaphabetic = 0;
    for(int i=1;i<str.size();i++){
        bool isalphabetic = (65<=str[i]&&str[i]<=90)||(97<=str[i]&&str[i]<=122);
        if((lastwasnonaphabetic ==1)&&isalphabetic) {
            result+=str[i];
            lastwasnonaphabetic = 0;
        }
        if(!isalphabetic){

            lastwasnonaphabetic = 1;}

    }
    return result;

}
