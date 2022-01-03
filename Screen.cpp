#include <iostream>
#include "Screen.h"

using namespace std;

#define LINUX // if OS = WINDOWS comment out this line
//#define WINDOWS // if OS = WINDOWS uncomment out this line

const string ERROR_TEXT = "error input";

void cls() {
    #ifdef WINDOWS
    system("cls");
    #else
    system("clear");
    #endif
}

char getChar() {
    #ifdef WINDOWS
    return getch();
    #else
    char result;
    system("stty raw -echo");
    result = getchar();
    system("stty -raw echo");
    return result;
    #endif
}

void printVerticalMenu(const char* title, const string* menu, int size, int position)
{
    cls();
    cout << endl << title << endl;
    for (int i = 0; i < size; i++)
    {
        cout << (position == i + 1 ? " > " : "   ") 
            << " " << i + 1 << " - " << menu[i] << endl;
    }
    cout << "-------------------------------------\n"
        << (position == 0 ? " > " : "   ") << " 0 - выход\n";   
}