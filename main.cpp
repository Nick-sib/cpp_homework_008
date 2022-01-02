#include <iostream>
#include "base/IntArray.h"
#include "base/ArrayException.h"
#include "Screen.h"

using namespace std;

#define LINUX

using namespace std;

const char CHAR_EXIT = (char) 27;
#ifdef LINUX 
const char CHAR_RETURN = (char) 13;
const char CHAR_DOWN = (char) 66;
const char CHAR_UP = (char) 65;
const char CHAR_RIGTH = (char) 67;
const char CHAR_LEFT = (char) 68;
#else 
const char CHAR_RETURN = (char) 10;
const char CHAR_DOWN = (char) 80;
const char CHAR_UP = (char) 72;
const char CHAR_RIGTH = (char) 77;
const char CHAR_LEFT = (char) 75;
#endif

void createArray(IntArray** intArray)
{
    printCreateArrayScreen();

    int arrayLength;
    cin >> arrayLength;

    try
    {
        *intArray = new IntArray(arrayLength);
    }
    catch(ArrayLengthException& e)
    {
        cerr << "\nВведите размер массива 0 или больше\n\n";
        cout << "press any key\n";
        getChar();
        getChar();
    }
    catch(BaseArrayExeption& e)
    {
        cout << endl << e.what() << endl;
        cout << "press any key\n";
        getChar();
        getChar();
    }
    catch(exception& e)
    {
        cerr << endl << e.what() << endl;
        cout << "press any key\n";
        getChar();
        getChar();
    }
}

void printArray(IntArray* intArray)
{
    cls();
    if (!intArray)
        throw "NPE!";
    cout << "МАССИВ:\n\n[";
    int length = intArray->getLength();
    for (int i = 0; i < length; i++)
    {
        cout << intArray->get(i);
        if (i != length - 1)
                cout << ", ";
    }
    cout << "]\n\npress any key\n";
    getChar();
}

void resizeArray(IntArray* intArray)
{
    printResizeArrayScreen();
    if (!intArray)
        throw "NPE!";
    
    int newArrayLength;
    cin >> newArrayLength;

try
    {
        intArray->resize(newArrayLength);
    }
    catch(ArrayLengthException& e)
    {
        cerr << "\nВведите размер массива 0 или больше\n\n";
        cout << "press any key\n";
        getChar();
        getChar();
    }
    catch(BaseArrayExeption& e)
    {
        cout << endl << e.what() << endl;
        cout << "press any key\n";
        getChar();
        getChar();
    }
    catch(exception& e)
    {
        cerr << endl << e.what() << endl;
        cout << "press any key\n";
        getChar();
        getChar();
    }
}

void eraseArray(IntArray* intArray)
{
    printEraseArrayScreen();
    if (!intArray)
        throw "NPE!";
    
    int defaultValue;
    cin >> defaultValue;
    try
    {
        intArray->erase(defaultValue);
    }
    catch(ArrayLengthException& e)
    {
        cerr << "\nВведите размер массива 0 или больше\n\n";
        cout << "press any key\n";
        getChar();
        getChar();
    }
    catch(BaseArrayExeption& e)
    {
        cout << endl << e.what() << endl;
        cout << "press any key\n";
        getChar();
        getChar();
    }
    catch(exception& e)
    {
        cerr << endl << e.what() << endl;
        cout << "press any key\n";
        getChar();
        getChar();
    }
}

void doEditing(IntArray* intArray, int position, EditType editType)
{
    int  value = 0;
    if (editType != DELETE)
    {
        cls();
        cout << "Введите значение для элкмента:\n\n";
        cin >> value;
    }
    switch (editType)
    {
        case ADD:
            intArray->insertAt(value ,position);
            break;
        case EDIT:
            intArray->get(position) = value;
            break;
        case DELETE:
            intArray->remove(position);
            break;
        default:
            break;
    }
}

void editArray(IntArray* intArray)
{
    if (!intArray)
        throw "NPE!";

    char ipunputedChar;
    int position = -1;
    int maxPosition = 0;
    int editTypeIndex = 0;
    while (true)
    {
        maxPosition = intArray->getLength() + 2;
        printArrayVertical(*intArray, position, editTypeIndex);
        ipunputedChar = getChar();
        switch (ipunputedChar) {
            case CHAR_DOWN:
                position = (position >= maxPosition ? -1 : position + 1);
                break;
            case CHAR_UP:
                position = (position <= -1 ? maxPosition : position - 1);
                break;
            case CHAR_RIGTH:
                editTypeIndex = (editTypeIndex >= 2 ? 0 : editTypeIndex + 1);
                break;
            case CHAR_LEFT:
                editTypeIndex = (editTypeIndex <= 0 ? 2 : editTypeIndex - 1);
                break;
            case CHAR_RETURN:
                if (position == maxPosition)
                {
                    return;
                } else {
                    try
                    {
                        doEditing(intArray, position, intToEditType(editTypeIndex));
                    }
                    catch(ArrayLengthException& e)
                    {
                        cerr << "\nНе верная длина массива\n\n";
                        cout << "press any key\n";
                        getChar();
                        getChar();
                    }
                    catch(ArrayRangeException& e)
                    {
                        cerr << "\nНе верный индекс массива\n\n";
                        cout << "press any key\n";
                        getChar();
                        getChar();
                    }
                    catch(BaseArrayExeption& e)
                    {
                        cout << endl << e.what() << endl;
                        cout << "press any key\n";
                        getChar();
                        getChar();
                    }
                    catch(exception& e)
                    {
                       cerr << endl << e.what() << endl;
                       cout << "press any key\n";
                       getChar();
                       getChar();
                    }
                }
                break;
            default:
                break;
        }
    }
}    

void findValue(IntArray* intArray)
{
    if (!intArray)
        throw "NPE!";
    cls();
    int value = 0;
    cout << "Введите искомое значение: ";
    cin >> value;
    int firstResult = intArray->findFirst(value);
    cout << "\n" 
        << (firstResult == -1 ? "значение не найдено (" : "первое вхождение элемента (") 
        << firstResult << ")\n";
    int lastResult = intArray->findLast(value);  
    if (firstResult != lastResult)
    {
        cout << "последнее вхождение элемента (" << lastResult << ")\n";
    }  
    cout << "\npress any key\n";
    getChar();
    getChar();
}

int main() 
{
    IntArray* intArray = nullptr;

    char ipunputedChar;
    int position = 1;

    while (true)  {
        printMainScreen(position);
        
        ipunputedChar = getChar();
        
        switch (ipunputedChar) {
            case '0': position = 0; break;
            case '1': position = 1; break;
            case '2': position = 2; break;
            case '3': position = 3; break;
            case '4': position = 4; break;
            case '5': position = 5; break;
            case '6': position = 6; break;
            case '7': position = 7; break;
            case '8': position = 8; break;
            case '9': position = 9; break;
            case CHAR_DOWN: 
                if (position >= 7) position = 0; else position++;
                break;
            case CHAR_UP:
                if (position <= 0) position = 7; else position--; 
                break;
            case CHAR_RETURN:
                try
                {
                    switch (position) 
                    {
                    case 0:
                        return 0;  
                    case 1: 
                        if (intArray)
                            delete intArray;
                        createArray(&intArray);
                        break;
                    case 2: 
                        printArray(intArray);
                        break;
                    case 3: 
                        resizeArray(intArray);
                        break;
                    case 4: 
                        eraseArray(intArray);
                        break;
                    case 5:
                        editArray(intArray);
                        break;
                    case 6:
                        findValue(intArray);
                        break;    
                    case 7:
                        intArray->get(-1);
                        break;    
                    default:
                        break;
                    }
                    break;
                }
                catch(const char* e)
                {
                    std::cerr << e << '\n';
                    cout << "\n\npress any key\n";
                    getChar();
                }
                default:
                    break;                
            }    
        }        
    delete intArray;
    return 0;
}