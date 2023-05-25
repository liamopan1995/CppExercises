#include <iostream>
#include <math.h>
#include <set>
using namespace std;

string integerToString(int num, int base);
int stringToInteger(string &str, int base);
int BinaryToDecimal(string &str, int base);

int main () {
    string input = "111";
    cout << BinaryToDecimal(input,2)<<endl;

    input = "921";
    cout << BinaryToDecimal(input,9)<<endl;
    input = "423";
    
    cout << BinaryToDecimal(input,10)<<endl;
    input = "3A";
    
    cout << BinaryToDecimal(input,11)<<endl;
    input = "3K";
    cout << BinaryToDecimal(input,11)<<endl;
    return 0;
}


// int stringToInteger (string &str, int base){
//     int result =0;
//     for (int i = str.length()-1; i > -1; i--){

//         if(str[i]=='1'){
//             result += str[i] * pow(base,i);
//         }
//     }
//     return result;
// }

int BinaryToDecimal(string &str, int base){
    // char char_base ='~';
    // if (base > 9) {

    // } else {
    //     char_base = static_cast<char>(base);
    //     cout<< "xxx"<< char_base;
    // }

    // validation check
    for (int i = 0;  i < str.length(); i++ ) {
        if ( !('0' <= str[i] && str[i] <= '9' || 'A' <= str[i] && str[i] <= 'B')) {
            cout<< "digits are outof range for base: "<<base<<endl;
            cout <<"invalid digit"<<"  "<< str[i]<<endl;
            return -1;
        }
    }




    int result =0;
    int exponent = 0;
    for (int i = str.length()-1; i > -1; i--){

        switch(str[i]){
            case '0': result +=  0 * pow(base,exponent); break;
            case '1': result +=  1 * pow(base,exponent); break;
            case '2': result +=  2 * pow(base,exponent); break;
            case '3': result +=  3 * pow(base,exponent); break;
            case '4': result +=  4 * pow(base,exponent); break;
            case '5': result +=  5 * pow(base,exponent); break;
            case '6': result +=  6 * pow(base,exponent); break;
            case '7': result +=  7 * pow(base,exponent); break;
            case '8': result +=  8 * pow(base,exponent); break;
            case '9': result +=  9 * pow(base,exponent); break;
            case 'A': result +=  10 * pow(base,exponent); break;
            case 'B': result +=  11 * pow(base,exponent); break;
            


        }
        exponent++;
    }
    return result;
}
