#ifndef INTARRAY_H
#define INTARRAY_H

class IntArray {
public:
    IntArray(int n);
    ~IntArray();
    int size() const;
    int get(int k) const;
    void put(int k, int value);

private:
    int* arr;
    int arraySize;

    // Private copy constructor and assignment operator to prevent copying

    //  says : "IntArray::IntArray(const IntArray &other)" (declared at
    //  line 17 of "/home/liam/git/CppExercises/chp12/02/intarray.h") is inaccessible
    IntArray(const IntArray& other);
    IntArray& operator=(const IntArray& other);
};

#endif
