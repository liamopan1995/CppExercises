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

private:
    int* arr;
    int arraySize;

    // Private copy constructor and assignment operator to prevent copying
    IntArray(const IntArray& other);
    IntArray& operator=(const IntArray& other);
};

#endif
