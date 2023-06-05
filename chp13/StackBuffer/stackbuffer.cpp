/*
* File: stackbuffer.cpp
* ---------------------
* This file implements the EditorBuffer class using a pair of
* stacks to represent the buffer.
*/
#include <iostream>
#include "stackbuffer.h"
#include "charstack.h"
using namespace std;
/*
* Implementation notes: Constructor and destructor
* ------------------------------------------------
* In this implementation, all dynamic allocation is managed by the
* CharStack class, which means that there is no work for the
* EditorBuffer class to do.
*/
EditorBuffer::EditorBuffer() {
/* Empty */
}
EditorBuffer::~EditorBuffer() {
/* Empty */
}
/*
* Implementation notes: moveCursor methods
* ----------------------------------------
* The four moveCursor methods use push and pop to transfer values
* between the two stacks.
*/
void EditorBuffer::moveCursorForward() {
if (!after.isEmpty()) {
before.push(after.pop());
}
}
void EditorBuffer::moveCursorBackward() {
if (!before.isEmpty()) {
after.push(before.pop());
}
}

void EditorBuffer::moveCursorToStart() {
while (!before.isEmpty()) {
after.push(before.pop());
}
}
void EditorBuffer::moveCursorToEnd() {
while (!after.isEmpty()) {
before.push(after.pop());
}
}
/*
* Implementation notes: insertCharacter and deleteCharacter
* ---------------------------------------------------------
* Each of the functions that inserts or deletes characters
* can do so with a single push or pop operation.
*/
void EditorBuffer::insertCharacter(char ch) {
before.push(ch);
}
void EditorBuffer::deleteCharacter() {
if (!after.isEmpty()) {
after.pop();
}
}
/*
* Implementation notes: showContents()
* ------------------------------------
* The showContents operator is complicated in the stack-based version,
* but it is not part of the fundamental operator set.
*/
void EditorBuffer::showContents() {
int nBefore = before.size();
moveCursorToStart();
while (!after.isEmpty()) {
cout << ' ' << after.peek();
moveCursorForward();
}
cout << endl;
moveCursorToStart();
for (int i = 0; i < nBefore; i++) {
cout << "  ";
moveCursorForward();
}
cout << '^' << endl;
}