#ifndef MYSTRING_H
#define MYSTRING_H
#include<string>
class MyString {
public:
    MyString( std::string inputStr );
    MyString(const char* inputArr, int length);
    ~MyString();
    std::string toString() const;
    int length() const;
    MyString  substr(int start, int n = -1) const;
    // MyString  substr(int start) const;
    MyString operator+( const MyString &adder) const;
    char & operator[](int k) const;

     // update deep copy
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);



    // friend M

    friend std::ostream& operator<<(std::ostream& os, const MyString& obj);

private:
    char* arr;
    int arraySize;
    void copyInternalData(const MyString & other); 
    
    
};

#endif
