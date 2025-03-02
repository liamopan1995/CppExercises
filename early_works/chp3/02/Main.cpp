#include <iostream>
#include "console.h"
#include <string>
using namespace std;
// prototype
string myTrim(const string &str);

int main() {
    string testcase1 = " Some sample code using the RandomBag.";
    string outputof1 = myTrim(testcase1);
    cout<<"thi is the first case:"<<testcase1<<endl;
    cout<<"this is the first result:"<<outputof1<<endl;
    return 0;
}

string myTrim(const string &str){
    string result;
    for(int i=0;i<str.size();i++){
        if(str[i]!=' ') {result+=str[i];}
    }
    return result;
}
