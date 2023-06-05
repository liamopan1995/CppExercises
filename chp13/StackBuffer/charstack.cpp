/*
* File: charstack.cpp
* -------------------
* This file implements the CharStack class.
*/
#include "charstack.h"
#include "error.h"
using namespace std;
/*
* Constant: INITIAL_CAPACITY
* --------------------------
* This constant defines the initial allocated size of the dynamic
* array used to hold the elements. If the stack grows beyond its
* capacity, the implementation doubles the allocated size.
*/
const int INITIAL_CAPACITY = 20;
/*
* Implementation notes: CharStack constructor
* -------------------------------------------
* The constructor must allocate the array storage for the stack elements
* and initialize the fields of the object.
*/
CharStack::CharStack() {
capacity = INITIAL_CAPACITY;
array = new char[capacity];
count = 0;
}
/*
* Implementation notes: ~CharStack
* --------------------------------
* The destructor frees any heap memory allocated by the class, which
* is just the dynamic array of elements.
*/
CharStack::~CharStack() {
delete[] array;
}
int CharStack::size() {
return count;
}
bool CharStack::isEmpty() {
return count == 0;
}
void CharStack::clear() {
count = 0;
}

/*
* Implementation notes: push
* --------------------------
* This function must first check to see whether there is enough room for
* the character and expand the array storage if necessary.
*/
void CharStack::push(char ch) {
if (count == capacity) expandCapacity();
array[count++] = ch;
}
/*
* Implementation notes: pop, peek
* -------------------------------
* These functions must check for an empty stack and report an
* error if there is no top element.
*/
char CharStack::pop() {
if (isEmpty()) error("pop: Attempting to pop an empty stack");
return array[--count];
}
char CharStack::peek() {
if (isEmpty()) error("peek: Attempting to peek at an empty stack");
return array[count - 1];
}
/*
* Implementation notes: expandCapacity
* ------------------------------------
* This private method doubles the capacity of the elements array whenever
* it runs out of space. To do so, it must copy the pointer to the old
* array, allocate a new array with twice the capacity, copy the characters
* from the old array to the new one, and finally free the old storage.
*/
void CharStack::expandCapacity() {
char *oldArray = array;
capacity *= 2;
array = new char[capacity];
for (int i = 0; i < count; i++) {
array[i] = oldArray[i];
}
delete[] oldArray;
}