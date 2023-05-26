#include <iostream>
#include "console.h"
//#include "string"

using namespace std;

/* Prints out how many items are in the bag. Note that we have to mark the
 * RandomBag::size() member function const for this to work, since otherwise
 * C++ won't know that member function doesn't mutate the bag.
 */

// constant parameters
string capitalize(const string &str);

//fuction prototype

// main
int main() {

    string test1 = "boolean";
    string test2 = "BOOLEAN";
    string test3 = "BO0!eAN";
    string output1 = capitalize(test1);
    string output2 = capitalize(test2);
    string output3= capitalize(test3);
    cout<<output1<<endl;
    cout<<output2<<endl;
    cout<<output3<<endl;
    return 0;
}

// function declaration

string capitalize(const string &str){
    string result = str;
    if(97<=result[0] && result[0]<=122) {result[0]=result[0]-32;}
    for(int i=1;i<result.size();i++){
        if(65<=result[i] && result[i]<=90) {result[i]=result[i]+32;}
        }
    return result;
}
