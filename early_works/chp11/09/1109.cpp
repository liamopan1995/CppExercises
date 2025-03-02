#include <iostream>
using namespace std;



int compareIgnoringCase(const string &s1, const string &s2) {
    int strLen = s1.length();
    if (strLen == s2.length()) {
        
        for (int i= 0; i< strLen; i++) {
            // compare asci number , when case ignored , the diference can only 
            // either be 0 or +- 32
            if (s1[i]- s2[i] != -32 && s1[i] -s2[i] !=  32 && s1[i]- s2[i] != 0){
                return -1;
            }
        }
        return 0;

    }
    // when lenths are different, two strings are obviously different
    return -1;
}

int main () {

    string str = "wolrd";
    string str2 = "wolrdww";
    cout << compareIgnoringCase(str,str2)<<endl;
    cout << compareIgnoringCase(str,"WOLRD")<<endl;
    cout << compareIgnoringCase("","")<<endl;
    cout << compareIgnoringCase(str,str)<<endl;
    cout << compareIgnoringCase("!@#$$#","!@#$$#")<<endl;

}