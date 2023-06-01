#include "mystring.h"
#include "mystringpriv.h"


MyString::MyString(std::string inputStr ) {
    arraySize = inputStr.length();
    arr = new char[arraySize];
    for (int i = 0; i < arraySize; i++) {
        arr[i] = inputStr[i];
    }
}

MyString::~MyString() {
    delete[] arr;
}

std::string MyString::toString() const{
    std:: string cStr = "";
    for (int i = 0; i < arraySize; i++) {
    cStr += arr[i];
    }
    return cStr;
};

int MyString::length() const{
    return arraySize;
}

MyString & MyString::substr(int start, int n) const{

    //compute stringlength for new string
    int strLen = 0;
    if(n == -1 ||  start + n > arraySize) {
        strLen = arraySize - start;
    }
    else{
        strLen = n;
    }

    // create a placce holder

    char * stringHolder = new char[strLen ];

    // copy chars within the range from mystring to the place holder

    for (int i=0; i < strLen; i++) {
        stringHolder[i] = arr[start++];
    }

    // initiate a new instance substrin
    MyString* substring = new MyString ("");

    // adjust values in substring
    // WARNING: this works but violates the conception of encapsulation, it has to be improved 
    // in further
    substring->arr = stringHolder;
    substring->arraySize = strLen;
    // snippet above needs MOdification!!

    return *substring;
 }

 MyString & MyString::substr(int start) const{
    return substr(start,-1);

 }
