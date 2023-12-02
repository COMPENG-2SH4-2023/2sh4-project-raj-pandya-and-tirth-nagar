#include "objPosArrayList.h"
#include "objPos.h"

// This class is a custom implementation of an array list that holds objPos objects.

// Constructor for the objPosArrayList class.
// It initializes the size of the array to a maximum capacity, 
// sets the size of the list to 0, and allocates memory for the array.
objPosArrayList::objPosArrayList()
{
    sizeArray = ARRAY_MAX_CAP; // Set the size of the array to the maximum capacity.
    sizeList = 0; // Initialize the size of the list to 0.
    aList = new objPos[sizeArray]; // Allocate memory for the array.
}

// Destructor for the objPosArrayList class.
// It deallocates the memory that was previously allocated for the array.
objPosArrayList::~objPosArrayList()
{
    delete[] aList; // Deallocate the memory for the array.
}

// This function returns the current size of the list.
int objPosArrayList::getSize()
{
    return sizeList; // Return the size of the list.
}

// This function inserts a new objPos object at the head of the list.
// It shifts all the existing elements to the right to make space for the new element.
void objPosArrayList::insertHead(objPos thisPos)
{
    for (int i = sizeList; i > 0; i--) {
        aList[i].setObjPos(aList[i - 1]); // Shift the elements to the right.
    }
    aList[0].setObjPos(thisPos); // Insert the new element at the head of the list.
    sizeList++;
}

// This function inserts a new objPos object at the tail of the list.
void objPosArrayList::insertTail(objPos thisPos)
{
    aList[sizeList].setObjPos(thisPos); // Insert the new element at the tail of the list.
    sizeList++;
}

// This function removes the head element of the list.
// It shifts all the existing elements to the left to fill the gap.
void objPosArrayList::removeHead()
{
    for (int i = 0; i < sizeList - 1; i++) {
        aList[i].setObjPos(aList[i + 1]); // Shift the elements to the left.
    }
    sizeList--; // Decrease the size of the list by 1.
}

// This function removes the tail element of the list.
// It simply decreases the size of the list by 1.
void objPosArrayList::removeTail()
{
    sizeList--; // Decrease the size of the list by 1.
}

// This function gets the head element of the list.
// It sets the passed objPos object to the head element of the list.
void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]); // Set the passed objPos object to the head element.
}

// This function gets the tail element of the list.
// It sets the passed objPos object to the tail element of the list.
void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList - 1]); // Set the passed objPos object to the tail element.
}

// This function gets an element at a specific index of the list.
// It sets the passed objPos object to the element at the specified index.
void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]); // Set the passed objPos object to the element at the specified index.
}