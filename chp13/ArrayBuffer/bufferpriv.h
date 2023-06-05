/*
* File: bufferpriv.h
* ------------------
* This file contains the private section of the EditorBuffer class for
* the array-based editor.
*/
/*
* Implementation notes: Buffer data structure
* -------------------------------------------
* In the array-based implementation of the buffer, the characters in the
* buffer are stored in a dynamic array. In addition to the array, the
* structure keeps track of the capacity of the buffer, the length of the
* buffer, and the cursor position. The cursor position is the index of
* the character that follows where the cursor would appear on the screen.
*/
private:
/* Instance variables */
    char *array;
    int capacity;
    int length;
    int cursor;

// Dynamic array of characters
// Allocated size of that arrayS
// Number of character in buffer
// Index of character after cursor

/* Make it illegal to copy editor buffers */
    EditorBuffer(const EditorBuffer & value) { }
    const EditorBuffer & operator=(const EditorBuffer & rhs) { return *this; }
/* Private method prototype */

    void expandCapacity() {
    char *oldArray = array;
    capacity *= 2;
    array = new char[capacity];
    for (int i = 0; i < length; i++) {
    array[i] = oldArray[i];
    }
    delete[] oldArray;
    }

