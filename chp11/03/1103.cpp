#include <iostream>
#include <math.h>
#include <set>
using namespace std;
// did this to check git status ...
string integerToString(int num, int base);
int stringToInteger(string &str, int base);


int main () {
    string input = "111";
    cout << stringToInteger(input,2)<<endl;

    input = "921";
    cout << stringToInteger(input,9)<<endl;
    input = "423";
    
    cout << stringToInteger(input,10)<<endl;
    input = "3A";
    
    cout << stringToInteger(input,11)<<endl;
    input = "3B";
    
    cout << stringToInteger(input,11)<<endl;
    cout << stringToInteger(input,12)<<endl;
    input = "3K";
    cout << stringToInteger(input,11)<<endl;

    input = "3&";
    cout << stringToInteger(input,11)<<endl;

    input = "XX";
    cout << stringToInteger(input,36)<<endl;

    input = "-356";
    cout << stringToInteger(input,10)<<endl;

    cout<<"interger to string"<<endl;
    cout << integerToString(121,11)<<endl;
    cout << integerToString(8898,11)<<endl;
    cout << integerToString(8899,11)<<endl;
    cout << integerToString(8900,11)<<endl;
    cout << integerToString(8904,12)<<endl;
    cout << integerToString(8903,12)<<endl;
    cout << integerToString(8902,12)<<endl;

    cout << integerToString(10,2)<<endl;

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

int stringToInteger(string &str, int base){
    // char char_base ='~';
    // if (base > 9) {

    // } else {
    //     char_base = static_cast<char>(base);
    //     cout<< "xxx"<< char_base;
    // }

    // validation check
    if (str[0] == '-') {
        char max = '0';
        for (int i = 1;  i < str.length(); i++ ) {
            if ( !('0' <= str[i] && str[i] <= '9' || 'A' <= str[i] && str[i] <= 'Z')) {
                cout <<"invalid digit"<<"  "<< str[i]<<endl;
                return -1;
            }

            max = (str[i] > max)? str[i]:max;

            if ('0'<=max && max <='9' ) {
            if (max - '0'>= base) {
                cout << " digit out of range  " << max<<endl ;
                return -1;
            }
    
            } 
            else {
                if (max -'7'>= base ) {
                cout << " digit out of range  " << max<<endl ;
                return -1;
            }
            }
        }



        int result =0;
        int exponent = 0;
        for (int i = str.length()-1; i > 0; i--){

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
                case 'C': result +=  12 * pow(base,exponent); break;
                case 'D': result +=  13 * pow(base,exponent); break;
                case 'E': result +=  14 * pow(base,exponent); break;
                case 'F': result +=  15 * pow(base,exponent); break;
                case 'G': result +=  16 * pow(base,exponent); break;
                case 'H': result +=  17 * pow(base,exponent); break;
                case 'I': result +=  18 * pow(base,exponent); break;
                case 'J': result +=  19 * pow(base,exponent); break;
                case 'K': result +=  20 * pow(base,exponent); break;
                case 'L': result +=  21 * pow(base,exponent); break;
                case 'M': result +=  22 * pow(base,exponent); break;
                case 'N': result +=  23 * pow(base,exponent); break;
                case 'O': result +=  24 * pow(base,exponent); break;
                case 'P': result +=  25 * pow(base,exponent); break;
                case 'Q': result +=  26 * pow(base,exponent); break;
                case 'R': result +=  27 * pow(base,exponent); break;
                case 'S': result +=  28 * pow(base,exponent); break;
                case 'T': result +=  29 * pow(base,exponent); break;
                case 'U': result +=  30 * pow(base,exponent); break;
                case 'V': result +=  31 * pow(base,exponent); break;
                case 'W': result +=  32 * pow(base,exponent); break;
                case 'X': result +=  33 * pow(base,exponent); break;
                case 'Y': result +=  34 * pow(base,exponent); break;
                case 'Z': result +=  35 * pow(base,exponent); break;
                
            }
            exponent++;
        }
        return -result;}
        
    else {
        char max = '0';
        for (int i = 0;  i < str.length(); i++ ) {
            if ( !('0' <= str[i] && str[i] <= '9' || 'A' <= str[i] && str[i] <= 'Z')) {
                cout <<"invalid digit"<<"  "<< str[i]<<endl;
                return -1;
            }

            max = (str[i] > max)? str[i]:max;

            if ('0'<=max && max <='9' ) {
            if (max - '0'>= base) {
                cout << " digit out of range  " << max<<endl ;
                return -1;
            }
    
            } 
            else {
                if (max -'7'>= base ) {
                cout << " digit out of range  " << max<<endl ;
                return -1;
            }
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
                case 'C': result +=  12 * pow(base,exponent); break;
                case 'D': result +=  13 * pow(base,exponent); break;
                case 'E': result +=  14 * pow(base,exponent); break;
                case 'F': result +=  15 * pow(base,exponent); break;
                case 'G': result +=  16 * pow(base,exponent); break;
                case 'H': result +=  17 * pow(base,exponent); break;
                case 'I': result +=  18 * pow(base,exponent); break;
                case 'J': result +=  19 * pow(base,exponent); break;
                case 'K': result +=  20 * pow(base,exponent); break;
                case 'L': result +=  21 * pow(base,exponent); break;
                case 'M': result +=  22 * pow(base,exponent); break;
                case 'N': result +=  23 * pow(base,exponent); break;
                case 'O': result +=  24 * pow(base,exponent); break;
                case 'P': result +=  25 * pow(base,exponent); break;
                case 'Q': result +=  26 * pow(base,exponent); break;
                case 'R': result +=  27 * pow(base,exponent); break;
                case 'S': result +=  28 * pow(base,exponent); break;
                case 'T': result +=  29 * pow(base,exponent); break;
                case 'U': result +=  30 * pow(base,exponent); break;
                case 'V': result +=  31 * pow(base,exponent); break;
                case 'W': result +=  32 * pow(base,exponent); break;
                case 'X': result +=  33 * pow(base,exponent); break;
                case 'Y': result +=  34 * pow(base,exponent); break;
                case 'Z': result +=  35 * pow(base,exponent); break;
                
            }
            exponent++;
        }
        return result;}
    
}


string integerToString(int num, int base){
    string result;
    string append="@";
    if (num==0) return "0";
    while ( num>0 ) {

        int remainder = num % base;
        if (remainder > 9){
            switch(remainder){
                case 10 : append = 'A';break;
                case 11 : append = 'B';break;
            }

        }
        else {
            append = to_string(remainder);
        }
        result = append + result;
        num /= base;
    }
    return result;
}