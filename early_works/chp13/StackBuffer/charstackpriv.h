/*
* File: charstackpriv.h
* ---------------------
* This file contains the private data for the CharStack class.
*/
private:
/* Instance variables */
char *array;
int capacity;
int count;
/* Dynamic array of characters
*/
/* Allocated size of that array */
/* Current count of chars pushed */
/* Private function prototype */
void expandCapacity();