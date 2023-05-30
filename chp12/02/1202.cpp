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
    try {
        std::cout << arr.get(10) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
