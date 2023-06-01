#ifndef MYSTRINGPRIV_H
#define MYSTRINGPRIV_H

#include <iostream>
#include <stdexcept>


// Error function to display error message and throw an exception
void error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    throw std::runtime_error(message);
}

// void IntArray::put(int k, int value) {
//     if (k < 0 || k >= arraySize) {
//         error("Index out of bounds");
//     }
//     arr[k] = value;
// }

// // update deep copy 
// void IntArray::copyInternalData(const IntArray & other) {
// arr = new int[other.arraySize];
// for (int i = 0; i < other.arraySize; i++) {
// arr[i] = other.arr[i];
// }
// arraySize = other.arraySize;

// }



#endif
