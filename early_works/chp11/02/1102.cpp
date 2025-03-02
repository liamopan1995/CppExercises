#include <iostream>
#include <math.h>
using namespace std;


//Write a recursive function generateGrayCode(nBits) that generates
//the Gray code patterns for the specified number of bits.


// functin prototypes
void generateGrayCode(int nBits);
void generateGrayCode_core(int nBits,string* arr, int arrLen);



int main() {

    int a;
    cout<< "please enter  integer greater than 0"<<endl;
    cin>>a;
    generateGrayCode(a); 
    return 0;
}


// Definition  of wrapper function
void generateGrayCode(int nBits){
    if (nBits < 1) {                                
         cout<<"invalid nBits!"<<endl;
    }
    else {                                             
        string* strArray = new string[2]{"0","1"};
        generateGrayCode_core(nBits,strArray,2);
        delete[] strArray;  // Deallocate the dynamically allocated array
    }

}
// Definition of recursive function
void generateGrayCode_core(int nBits,string* arr, int arrLen) {
    string *ptr1 = arr;
    if (nBits == 1) {                                                   // base case
        for (int i = 0; i < arrLen; i++){
            if(arr != nullptr) {
                // string* ptr_template= arr;
                cout << *arr++ <<"  -> "<< i<< endl;            
            } 
        }
        
    }

    else {                                                              // recusive case
        string* strArray = new string[2* arrLen];
        
        // create a new aray with doubled size ,fill first half of it with "0" , the rest with "1"
        // concatenate strings from old arr in sequnce and in reverse respectivly to first and 
        // second half.

        for (int i = 0; i < arrLen; i++) {
            strArray[i] = "0" + *arr++;
        }
        for (int i = 2*arrLen -1; i >= arrLen; i--) {
            strArray[i] = "1" + *ptr1++;  // why is not allowed to continue use pointer arr at here?
        }

        generateGrayCode_core(nBits-1, strArray, 2*arrLen);
        delete[] strArray;
    }

}
