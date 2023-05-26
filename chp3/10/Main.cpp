#include <iostream>
#include "console.h"
using namespace std;

/*
 */

//constants

//prototype
string replaceAll(string str,char c1,char c2);
string replaceAll(string str,string c1,string c2);
//main
int main() {
    /* Some sample code . */

    string test1 ="nannies";
    cout<<replaceAll(test1,"ies","tt")<<endl;// expecting nanntt
    cout<<replaceAll(test1,"anni","tt")<<endl;//expecting nttes
    cout<<replaceAll(test1,"ie","tt")<<endl;// nanntts
    cout<<replaceAll(test1,"s","tt")<<endl;//nanniett  here was a BUG!solved!
    cout<<replaceAll(test1,"n","tt")<<endl;//ttannies
    cout<<replaceAll(test1,'n','q');
    return 0;
}

//declaration
string replaceAll(string str,char c1,char c2){
    string output = str;
    for (int i=0;i<output.size();i++){
        if (output[i]==c1) output[i]=c2;
    }
    return output;
}

// overloaded version
string replaceAll(string str,string c1,string c2){
    // first letter the same record index start
    // start forloop on c1 and str
    //once the token was true until last letter in c1, and c1
    //also identical, record the end index
    // writte a ouput with the index
    int start = -1;
    bool hasstart =false;
    //bool endfound=false;
    int end = -1;
    string output=str;
    for(int i=0;i<str.size()+1;i++){
        if(hasstart){
            int j=0;
            while( j<str.size()-start/*-c1.size()*/){
                if (str[start+j]!=c1[j]){
                    /*endfound=false;*/break;}
                end =start+j;
                //endfound =true;
                if(/*endfound&&*/(j+1)==c1.size()) return output = str.substr(0,start)+c2+str.substr(end+1);
                j++;
            }

        }
        if(!hasstart){
            if (str[i]==c1[0]){
                hasstart = true;
                start =i;
            }
        }
    }
    return output;
}
