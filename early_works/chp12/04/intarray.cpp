#include "intarray.h"
#include "intarraypriv.h"

IntArray::IntArray(int n) : arr(new int[n]), arraySize(n) {
    for (int i = 0; i < arraySize; i++) {
        arr[i] = 0;
    }
}

IntArray::~IntArray() {
    delete[] arr;
}

int IntArray::size() const {
    return arraySize;
}

int IntArray::get(int k) const {
    if (k < 0 || k >= arraySize) {
        error("Index out of bounds");
    }
    return arr[k];
}
// followings are updates 
int & IntArray::operator[](int k) const{
    if (k < 0 || k >= arraySize) {
        error("Index out of bounds");
    }
    return arr[k];
}
// update : deep copy
IntArray::IntArray(const IntArray&  other) {
    copyInternalData(other);
}

IntArray & IntArray::operator=(const IntArray& other){
    if (this != &other) {
    delete[] arr;
    copyInternalData(other);
    }
    return *this;
}
