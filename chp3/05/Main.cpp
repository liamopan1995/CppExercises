#include <iostream>
using namespace std;

/*
 */

//constants

//prototype
int scrabble(const string &str);
//main
int main() {
    /* Some sample code . */

    string test1 = "AAAD";
    cout<<"test1 has score :"<<scrabble(test1)<<endl;
    string test2 = "Huxin ++123 Pan";
    cout<<"test2 has score :"<<scrabble(test2)<<endl;
    return 0;
}

//declaration

int scrabble(const string &str){
    int point = 0;
    for(int i=0;i<str.size();i++){
        if(65<=str[i]&&str[i]<=90) {
            switch(str[i]){
            case 'A':case'E':case'I':case'L':case'N':
            case'R':case'S':case'T':case'U':case'O':
                point+=1;break;
            case'D':case'G':
                point+=2;break;
            case'B':case'C':case'M':case'P':
                point+=3;break;
            case'F':case'H':case'V':case'W':case'Y':
                point+=4;break;
            case'K':
                point+=5;break;
            case'J':case'X':
                point+=8;break;
            case'Q':case'Z':
                point+=8;break;

            }
        }
    }
    return point;
}
