#include <iostream>
#include <math.h>
using namespace std;


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


// declaration of wrapper function
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
// Declaration of recursive function
void generateGrayCode_core(int nBits,string* arr, int arrLen) {
    string *ptr1 = arr;
    if (nBits == 1) {
        for (int i = 0; i < arrLen; i++){
            if(arr != nullptr) {
                // string* ptr_template= arr;
                cout << *arr++ <<"  -> "<< i<< endl;            
            } 
        }
        
    }

    else {
        string* strArray = new string[2* arrLen];
        
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
