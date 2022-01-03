#include <iostream>
#include "base/ArrayClass.h"

enum EditType {
        EDIT = 0,
        ADD = 1,
        DELETE = 2
    };

static const char* editToText[] = {"<edit> ", "<add>  ", "<del>  "};

static EditType intToEditType(int value) 
{
    return static_cast<EditType>(value);
}

void cls();
char getChar();
void printVerticalMenu(const char* title, const std::string* menu, int size, int position);

template <typename T>
void printTemplateMenuWithMarker(
    const char* title, 
    T* menu, 
    int size, 
    int position,
    bool extendAdd,
    const char* marker,
    const char* clear
){
    const int exitIndex = extendAdd ? size + 1 : size;
    cls();
    std::cout << title;
    for (int i = 0; i < size; i++)
    {
        std::cout << "   " << (position == i ? marker : clear) << i << " = [" << menu[i] << "]\n";
    }
    if (extendAdd) {
        std::cout << "   " << (position == size ? marker : clear) << size << " = [add/error" << "]\n";    
    }
    std::cout << "     ----------------------------------------\n"
        << "    " << (position == exitIndex ? " >  " : "      ")  <<  "  exit\n";

};