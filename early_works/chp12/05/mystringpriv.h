#ifndef MYSTRINGPRIV_H
#define MYSTRINGPRIV_H

#include <iostream>
#include <stdexcept>


// Error function to display error message and throw an exception
void error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    throw std::runtime_error(message);
}

// update deep copy 
void MyString::copyInternalData(const MyString & other) {
arr = new char[other.arraySize];
for (int i = 0; i < other.arraySize; i++) {
arr[i] = other.arr[i];
}
arraySize = other.arraySize;

}



#endif
