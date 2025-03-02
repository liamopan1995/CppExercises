#ifndef MYSTRING_H
#define MYSTRING_H

#include <string>

class MyString {
public:
    MyString(std::string inputStr);                       // Constructor taking a string as input
    MyString(const char* inputArr, int length);           // Constructor taking a character array and its length as input
    ~MyString();                                          // Destructor
    std::string toString() const;                         // Returns a string representation of the MyString object
    int length() const;                                   // Returns the length of the MyString object
    MyString substr(int start, int n = -1) const;         // Returns a substring of the MyString object
    MyString operator+(const MyString& adder) const;      // Concatenates two MyString objects using the + operator
    char& operator[](int k) const;                        // Returns a reference to the character at index k in the MyString object

    // Deep copy constructor
    MyString(const MyString& other);

    // Deep copy assignment operator
    MyString& operator=(const MyString& other);

    friend std::ostream& operator<<(std::ostream& os, const MyString& obj);  // Overloaded << operator for output stream

private:
    char* arr;        // Pointer to the character array holding the MyString data
    int arraySize;    // Size of the character array

    void copyInternalData(const MyString& other);  // Helper function to perform a deep copy of internal data

};

#endif
