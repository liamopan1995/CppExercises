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

// void IntArray::put(int k, int value) {
//     if (k < 0 || k >= arraySize) {
//         error("Index out of bounds");
//     }
//     arr[k] = value;
// }
