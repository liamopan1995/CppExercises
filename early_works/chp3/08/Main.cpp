#include <iostream>
#include "console.h"
using namespace std;

/*   Same function but this time we operate on the input string directly
 */

//constants

//prototype
//void removeCharactersbyR (  string &str,const string &remove);
void removeRec (string &str,const string &remove);
void removeOneChar (string &str,const char &remove);
//main
int main() {

    cout<<"expected output : cntrrvltnrs"<<endl;
    string test1 = "counterrevolutionaries";
    removeRec(test1,"aeiou");
    cout<<"the ouput of the programm: "<< test1;

    cout<<"expected output : oueeouioaie, cut all the consonant"<<endl;
    string test2 = "counterrevolutionaries";
    removeRec(test2,"cntrrvls");
    cout<<"the ouput of the programm: "<< test2;


    return 0;
}

//declaration
//void removeCharactersbyR (  string &str,const string &remove){

//    //removeRec(str,remove);
//}

void removeRec (string &str,const string &remove){
    //basecase
    if (remove.size()!=0){
        removeOneChar(str,remove[0]);
        string leftToRemove = remove.substr(1);
        removeRec(str,leftToRemove);
    }
    // if condition not fullfilled the void func runs to the end and program
    // terminates

}

void removeOneChar (string &str,const char &remove){
    for (int i=0;i<str.size();i++){
        if (str[i]==remove) {str = str.substr(0,i)+str.substr(i+1);}
        }
}
