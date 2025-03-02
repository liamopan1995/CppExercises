#include <iostream>
#include "intarray.h"

int main() {
    // Create an IntArray object with size 5
    IntArray arr(5);

    // Print the initial size of the array
    std::cout << "Array size: " << arr.size() << std::endl;

    // Access and modify elements using the get() and put() methods
    arr.put(0, 10);
    arr.put(1, 20);
    arr.put(2, 30);

    // Print the values at specific indices
    std::cout << "Value at index 0: " << arr.get(0) << std::endl;
    std::cout << "Value at index 1: " << arr.get(1) << std::endl;
    std::cout << "Value at index 2: " << arr.get(2) << std::endl;

    // Attempt to access an out-of-bounds index
    std::cout << "Value at index 10: ";
    std::cout << "get value via index: "<< arr[2]<< std::endl;
    std::cout << "modify a value via index: "<< std::endl;
    arr[2]= 40 ; 
    std::cout << "after arr[2] beening modified to 40: "<< arr[2]<< std::endl;


    try {
        std::cout << arr.get(10) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // test deep copy 
    IntArray arrcopy1(5);
    arrcopy1 = arr;
    IntArray arrcopy2 = arr;

    // see whether values in it will change if value in arr was changed:
    arr[1]=99;
    arr[2]=99;

    std::cout << "Value of arrcopy1 at index 0  : " << arrcopy1.get(0) << std::endl;
    std::cout << "Value at arrcopy1 at index 1: " << arrcopy1.get(1) << std::endl;
    std::cout << "Value at arrcopy1 at index 2: " << arrcopy1.get(2) << std::endl;

    std::cout << "Value of arrcopy2 at index 0  : " << arrcopy2[0] << std::endl;
    std::cout << "Value at arrcopy2 at index 1: " << arrcopy2[1] << std::endl;
    std::cout << "Value at arrcopy2 at index 2: " << arrcopy2[2] << std::endl;



    return 0;
}
