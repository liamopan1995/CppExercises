/*
* File: stackbufferpriv.h
* ------------------
* This file contains the private section of the EditorBuffer
* class for the stack-based editor.
*/
/*
* Implementation notes: Buffer data structure
* -------------------------------------------
* In the stack-based buffer model, the characters are stored in two
* stacks. Characters before the cursor are stored in a stack named
* "before"; characters after the cursor are stored in a stack named
* "after". In each case, the characters closest to the cursor are
* closer to the top of the stack. The advantage of this
* representation is that insertion and deletion at the current
* cursor position occurs in constant time.
*/

private:
/* Instance variables */
CharStack before;
CharStack after;
/* Stack of characters before the cursor */
/* Stack of characters after the cursor */
/* Make it illegal to copy editor buffers */
EditorBuffer(const EditorBuffer & value) { }
const EditorBuffer & operator=(const EditorBuffer & rhs) { return *this; }