#ifndef MYSTRING_H
#define MYSTRING_H
#include<string>
class MyString {
public:
    MyString( std::string inputStr );
    ~MyString();
    std::string toString() const;
    int length() const;
    MyString & substr(int start, int n) const;
    MyString & substr(int start) const;


private:
    char* arr;
    int arraySize;
    // void copyInternalData(const IntArray & cstk) ;
    
    
};

#endif
