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

void printMainScreen(int position) {
    cls();
            
    cout << "\n  Доступные функции:\n\n"
        << (position == 1 ? " > " : "   ")  << " 1 - Создать массив\n"
        << (position == 2 ? " > " : "   ")  << " 2 - Показать массив\n"
        << (position == 3 ? " > " : "   ")  << " 3 - Изменить размер\n"
        << (position == 4 ? " > " : "   ")  << " 4 - Очистить массив\n"
        << "-------------------------------------\n"
        << (position == 5 ? " > " : "   ")  << " 5 - Изменить данные массива\n"
        << (position == 6 ? " > " : "   ")  << " 6 - Найти элемент\n"
        << "-------------------------------------\n"
        << (position == 7 ? " > " : "   ")  << " 7 - Сгенерировать ошибку\n"
        << "-------------------------------------\n"
        << (position == 0 ? " > " : "   ") << "0 - выход\n";
}

void printCreateArrayScreen()
{
    cls();
    cout << "\n  Введите размер массива:\n\n" 
        << "       (значения меньше 0 вызовут исключение)\n\n";

}

void printResizeArrayScreen()
{
    cls();
    cout << "\n  Введите новый размер массива:\n\n" 
        << "       (значения меньше 0 вызовут исключение)\n\n";
}

void printEraseArrayScreen()
{
    cls();
    cout << "\n  Введите значение которым заполниться массив:\n\n";
}
/*
void printArrayVertical(IntArray& intArray, int position, int editTypeIndex)
{
    cls();
    int length = intArray.getLength();
    cout << "\n  Введите значение которым заполниться массив:\n\n" 
        << "    " << (position == -1 ? editToText[editTypeIndex] : "       ") << "-1 = [error]\n";
    for (int i = 0; i < length; i++)
    {
        cout << "    " << (position == i ? editToText[editTypeIndex] : "        ") << i << " = [" << intArray[i] << "]\n";
    }
    cout << "    " << (position == length ? editToText[editTypeIndex] : "        ") << length << " = [new/error]\n";
    cout << "    " << (position == length + 1 ? editToText[editTypeIndex] : "        ") << length + 1 << " = [error]\n";
    cout << "     ----------------------------------------\n";
    cout << "    " << (position == length + 2 ? "<-->  " : "      ")  <<  "  exit\n";
}

*/




