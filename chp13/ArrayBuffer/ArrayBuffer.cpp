/*
* File: ArrayBuffer.cpp
* ---------------------
* This file implements the buffer.h interface using an array representation.
*/
#include <iostream>
#include "buffer.h"
using namespace std;
/* Constants */
const int INITIAL_CAPACITY = 10;
/*
* Implementation notes: Constructor and destructor
* ------------------------------------------------
* The constructor initializes the private fields. The destructor
* frees the heap-allocated memory, which is the dynamic array.
*/
EditorBuffer::EditorBuffer() {
capacity = INITIAL_CAPACITY;
array = new char[capacity];
length = 0;
cursor = 0;
}
EditorBuffer::~EditorBuffer() {
delete[] array;
}
/*
* Implementation notes: moveCursor methods
* ----------------------------------------
* The four moveCursor methods simply adjust the value of cursor.
*/
void EditorBuffer::moveCursorForward() {
    if (cursor < length) cursor++;
}
void EditorBuffer::moveCursorBackward() {
    if (cursor > 0) cursor--;
}
void EditorBuffer::moveCursorToStart() {
    cursor = 0;
}
void EditorBuffer::moveCursorToEnd() {
    cursor = length;
}

/*
* Implementation notes: insertCharacter and deleteCharacter
* ---------------------------------------------------------
* Each of the functions that inserts or deletes characters must shift
* all subsequent characters in the array, either to make room for new
* insertions or to close up space left by deletions.
*/
void EditorBuffer::insertCharacter(char ch) {
    if (length == capacity) expandCapacity();
    for (int i = length; i > cursor; i--) {
        array[i] = array[i - 1];
    }
    array[cursor] = ch;
    length++;
    cursor++;
}
void EditorBuffer::deleteCharacter() {
    if (cursor < length) {
        for (int i = cursor+1; i < length; i++) {
            array[i - 1] = array[i];
        }
    length--;
    }
}
/*
* Implementation notes: showContents
* ----------------------------------
* This method prints the contents of the buffer with one space between
* each character to leave room for a caret on the next line to indicate
* the position of the cursor.
*/
void EditorBuffer::showContents() {
    for (int i = 0; i < length; i++) {
        cout << " " << array[i];
    }
    cout << endl;
    cout << string(2 * cursor, ' ') << "^" << endl;
}