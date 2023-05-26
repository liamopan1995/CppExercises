#include <iostream>
#include "console.h"
using namespace std;

/*
 */

//constants

//prototype
string removeCharacters (const  string &str,const string &remove);
//main
int main() {
    /* Some sample code . */
    cout<<"expected output : cntrrvltnrs"<<endl;
    cout<<"the ouput of the programm: "<< removeCharacters("counterrevolutionaries","aeiou");
    return 0;
}

//declaration
string removeCharacters (const  string &str,const string &remove){
    string output;
    for (int i=0;i<str.size();i++){
        bool Inremove = 0;
        for(int j=0;j<remove.size();j++){
            if (remove[j]==str[i]) {Inremove = true;break;}

        }
        if(!Inremove) output+=str[i];

    }
    return output;
}
