#include <iostream>
#include "mystring.h"
#include <string>

int main() {
    // Create an IntArray object with size 5
    MyString arr("Hello world");
    std::string cstring  = arr.toString();
    std::cout<< cstring<<std::endl;
    std::cout<< "cstring's length is : "<< arr.length()<<std::endl;

    //
    std::cout<< "cstring's length is : "<< arr.length()<<std::endl;

    // Create a MyString object
    MyString myString("Hello, space!");

    // Test the substr method with two parameters
    MyString& substring1 = myString.substr(7, 5);
    std::cout << "Substring 1: " << substring1.toString() << std::endl;  // Output: "World"
    std::cout<< "Substring 1's length is : "<< substring1.length()<<std::endl;// 5

    // Test the substr method with a single parameter
    MyString& substring2 = myString.substr(0);
    std::cout << "Substring 2: " << substring2.toString() << std::endl;  // Output: "Hello, World!"
    std::cout<< "Substring 2's length is : "<< substring2.length()<<std::endl;// Output : 13
    //Cleanup: delete the dynamically allocated substrings

    return 0;

    


    return 0;
}
