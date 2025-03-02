#ifndef INTARRAY_H
#define INTARRAY_H

class IntArray {
public:
    IntArray(int n);
    ~IntArray();
    int size() const;
    int get(int k) const;
    void put(int k, int value);
 // update an new operator 
    int & operator[](int k) const;
 // update deep copy
    IntArray(const IntArray& other);
    IntArray& operator=(const IntArray& other);

private:
    int* arr;
    int arraySize;
    void copyInternalData(const IntArray & cstk) ;
    
    
};

#endif
