#include <iostream>
#include <math.h>
using namespace std;

void generateGrayCode(int nBits);
void generateGrayCode_core(int nBits,string* arr, int arrLen);
int main() {

    int a;
    cout<< "please enter  integer greater than 0"<<endl;
    cin>>a;
    generateGrayCode(a); 
    return 0;
}

void generateGrayCode(int nBits){
    if (nBits < 1) {
         cout<<"invalid nBits!"<<endl;
    }
    else {
        string* strArray = new string[2]{"02","19"};
        generateGrayCode_core(nBits,strArray,2);
        delete[] strArray;  // Deallocate the dynamically allocated array
    }

}

void generateGrayCode_core(int nBits,string* arr, int arrLen) {
    if (nBits == 1) {
        for (int i = 0; i < arrLen; i++){
            if(arr != nullptr) {
                // string* ptr_template= arr;
                cout << *arr++ << endl;
                
        } 
        // delete[] arr;
        }
        
    }

    else {
        return;
    }

}

// void display 