#ifndef INTARRAYPRIV_H
#define INTARRAYPRIV_H

#include <iostream>
#include <stdexcept>


// Error function to display error message and throw an exception
void error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    throw std::runtime_error(message);
}

void IntArray::put(int k, int value) {
    if (k < 0 || k >= arraySize) {
        error("Index out of bounds");
    }
    arr[k] = value;
}



#endif
