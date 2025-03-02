#include <iostream>
#include "mystring.h"
#include <string>

int main() {
    // Create an IntArray object with size 5
    MyString arr("Hello world");
    std::string cstring  = arr.toString();
    std::cout<< cstring<<std::endl;
    std::cout<< "cstring's length is : "<< arr.length()<<std::endl;

    //  Test of the length() method
    std::cout<< "cstring's length is : "<< arr.length()<<std::endl;

    // Create a MyString object
    MyString myString("Hello, space!");

    // Test the substr method() with two parameters
    MyString substring1 = myString.substr(7, 5);
    std::cout << "Substring 1: " << substring1.toString() << std::endl;  // Output: "World"
    std::cout<< "Substring 1's length is : "<< substring1.length()<<std::endl;// 5

    // Test of the substr() method with a single parameter
    MyString substring2 = myString.substr(0);
    std::cout << "Substring 2: " << substring2.toString() << std::endl;  // Output: "Hello, World!"
    std::cout<< "Substring 2's length is : "<< substring2.length()<<std::endl;// Output : 13
    //Cleanup: delete the dynamically allocated substrings

    // Test of the + operator
    MyString strsum = substring1 + substring2;
    std::cout<<strsum.toString()<< std::endl;
    std::cout<<"strsum's length is : "<< strsum.length()<< std::endl;

    // Test of the << operaotr
    std::cout<< strsum<< std::endl;

    //// Test of the [] operaotr
    strsum[0] = '%';
    std::cout<< strsum<< std::endl;
    

    // Test of the deep copying
    MyString strCopy1 = strsum;
    std::cout<< strCopy1<< std::endl;

    MyString strCopy2("");
    strCopy2 = strsum;
    std::cout<< strCopy1<< std::endl;

    // test of error function and []'s bound check
    strsum[99]= '%';// Error :Index out of bounds

    return 0;

    


    return 0;
}
