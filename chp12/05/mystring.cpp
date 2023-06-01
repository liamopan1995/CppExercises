#include "mystring.h"
#include "mystringpriv.h"


MyString::MyString(std::string inputStr ) {
    arraySize = inputStr.length();
    arr = new char[arraySize];
    for (int i = 0; i < arraySize; i++) {
        arr[i] = inputStr[i];
    }
}

MyString::MyString(const char* inputArr, int length) {
    arraySize = length;
    arr = new char[arraySize];
    for (int i = 0; i < arraySize; i++) {
        arr[i] = inputArr[i];
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

// MyString MyString::substr(int start, int n) const{

//     //compute stringlength for new string
//     int strLen = 0;
//     if(n == -1 ||  start + n > arraySize) {
//         strLen = arraySize - start;
//     }
//     else{
//         strLen = n;
//     }

//     // create a placce holder

//     char * subStringHolder = new char[strLen ];

//     // copy chars within the range from mystring to the place holder

//     for (int i=0; i < strLen; i++) {
//         subStringHolder[i] = arr[start++];
//     }

//     // initiate a new instance substrin
//     // MyString* substring = new MyString ("");

//     // // adjust values in substring
//     // // WARNING: this works but violates the conception of encapsulation, it has to be improved 
//     // // in further
//     // substring->arr = stringHolder;
//     // substring->arraySize = strLen;
//     // snippet above needs MOdification!!

//     // Create a new MyString object with the substring data
//     MyString arr(subStringHolder,strLen);
//     delete[] subStringHolder;
//     return arr;
//  }

MyString MyString::substr(int start, int n) const {
    // Compute string length for new substring
    int strLen = 0;
    if (n == -1 || start + n > arraySize) {
        strLen = arraySize - start;
    } else {
        strLen = n;
    }

    // Create a placeholder for the substring
    char* subStringHolder = new char[strLen];

    // Copy characters within the range from mystring to the placeholder
    for (int i = 0; i < strLen; i++) {
        subStringHolder[i] = arr[start++];
    }

    // Create a new MyString object with the substring data
    MyString * substring = new MyString (subStringHolder, strLen);

    // Clean up dynamically allocated memory
    delete[] subStringHolder;

    // Return the newly created MyString object by value
    return *substring;
}




//  MyString MyString::substr(int start) const{
//     return substr(start,-1);

//  }


// Return a substring of the string
// MyString MyString::substr(int start, int n ) const {
//     if (n == -1) {
//         n = arraySize - start;
//     }
//     MyString result("");
//     if (start < arraySize && n > 0) {
//         n = std::min(n, arraySize - start);
//         result.arr = new char[n + 1];
//         std::copy(arr + start, arr + start + n, result.arr);
//         result.arr[n] = '\0';
//         result.arraySize = n;
//     }
//     return result;
// }

MyString MyString::operator+( const MyString &adder) const {
    int newSize = this->arraySize + adder.arraySize;
    char *charPlaceHolder = new char[newSize];

    for (int i = 0; i < this->arraySize; i++) {
        charPlaceHolder[i] = arr[i];
    }

    for (int i = 0;i <adder.arraySize;i++) {
        charPlaceHolder[this->arraySize + i] = adder.arr[i];
    }

    // Create a new MyString object with the substring data
    MyString * substring = new MyString (charPlaceHolder, newSize);

    return *substring;

}

std::ostream& operator<<(std::ostream& os, const MyString& obj) {
    os << obj.toString();
    return os;
    }

char & MyString::operator[](int k) const{
    if (k < 0 || k >= arraySize) {
        error("Index out of bounds");
    }
    return arr[k];
}

// update : deep copy
MyString::MyString(const MyString&  other) {
    copyInternalData(other);
}

MyString & MyString::operator=(const MyString& other){
    if (this != &other) {
    delete[] arr;
    copyInternalData(other);
    }
    return *this;
}