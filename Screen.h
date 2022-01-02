#include <iostream>
#include "base/IntArray.h"

enum EditType {
        EDIT = 0,
        ADD = 1,
        DELETE = 2
    };

static const char* editToText[] = {"<edit>  ", "<add>   ", "<del>   "};

static EditType intToEditType(int value) 
{
    return static_cast<EditType>(value);
}

void cls();
char getChar();
void printMainScreen(int position);

void printCreateArrayScreen();
void printResizeArrayScreen();
void printEraseArrayScreen();
void printArrayVertical(IntArray& intArray, int position, int editTypeIndex);