#include <iostream>
#include "base/ArrayClass.h"
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

const int CHAR_DELTA = (int) '0';

const int MENU_TYPES_SIZE = 3;
const string MENU_TYPES[MENU_TYPES_SIZE]  = 
    {
        "INTEGER",
        "FLOAT",
        "STRING"
    };

const int MENU_EVENT_SIZE = 6;
const string MENU_EVENT[MENU_EVENT_SIZE] = 
    {
        "Пересоздать массив",
        "Показать массив",
        "Изменить размер",
        "Очистить массив",
        "Изменить данные массива",
        "Найти элемент"
    };

template <typename T>
void printArray(ArrayClass<T>& array)
{
    cls();
    cout << "МАССИВ:\n\n[";
    int length = array.getLength();
    for (int i = 0; i < length; i++)
    {
        cout << array.get(i);
        if (i != length - 1)
                cout << ", ";
    }
    cout << "]\n\npress any key\n";
    getChar();
}

template <typename T>
void resizeArray(ArrayClass<T>& array)
{
    cls();
    cout << "\n  Введите новый размер массива:\n\n" 
        << "       (значения меньше 0 вызовут исключение)\n\n";
    
    int newArrayLength;
    cin >> newArrayLength;

    try
    {
        array.resize(newArrayLength);
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

template<typename T>
void eraseArray(ArrayClass<T>& array)
{
    cls();
    cout << "\n  Введите значение которым заполниться массив:\n\n";
    
    T defaultValue;
    cin >> defaultValue;
    try
    {
        array.erase(defaultValue);
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

template <typename T>
void doEditing(ArrayClass<T>& array, int position, EditType editType)
{
    T  value;
    if (editType != DELETE)
    {
        cls();
        cout << "Введите значение для элкмента:\n\n";
        cin >> value;
    }
    switch (editType)
    {
        case ADD:
            array.insertAt(value ,position);
            break;
        case EDIT:
            array.get(position) = value;
            break;
        case DELETE:
            array.remove(position);
            break;
        default:
            break;
    }
}

template <typename T>
void editArray(ArrayClass<T>& array)
{
    int length(array.getLength());
    T* menu = new T[length];

    for (int i = 0; i < length; i++)
        menu[i] = array.get(i);

    int position = 0;
    int maxPosition = 0;
    int editTypeIndex = 0;
    char ipunputedChar;
    while (true)
    {
        maxPosition = array.getLength() + 1;        
        printTemplateMenuWithMarker<T>(
            "Редактирование массива:\n\n",
            menu,
            length,
            position,
            true,
            editToText[editTypeIndex],
            "       "
        );

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
                       doEditing<T>(array, position, intToEditType(editTypeIndex));
                       delete[] menu;
                       length = array.getLength();
                       menu = new T[length];

                        for (int i = 0; i < length; i++)
                            menu[i] = array.get(i);
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
    delete[] menu;
}    

template<typename T>
void findValue(ArrayClass<T>& array)
{
    cls();
    T value;
    cout << "Введите искомое значение: ";
    cin >> value;
    int firstResult = array.findFirst(value);
    cout << "\n" 
        << (firstResult == -1 ? "значение не найдено (" : "первое вхождение элемента (") 
        << firstResult << ")\n";
    int lastResult = array.findLast(value);  
    if (firstResult != lastResult)
    {
        cout << "последнее вхождение элемента (" << lastResult << ")\n";
    }  
    cout << "\npress any key\n";
    getChar();
    getChar();
}

int doVerticalMenu(const char* title, const std::string* menu, int size)
{
    char ipunputedChar;
    int position = 1;
    while (true)  
    {
        printVerticalMenu(title, menu, size, position);        
        ipunputedChar = getChar();
        
        switch (ipunputedChar) 
        {
            case '0': case '1': case '2': case '3': 
            case '4': case '5': case '6': case '7': 
            case '8': case '9': 
                position = (int) ipunputedChar - CHAR_DELTA; 
                position = min(MENU_TYPES_SIZE, position);
                break;
            
            case CHAR_DOWN: 
                if (position >= size) position = 0; else position++;
                break;
            case CHAR_UP:
                if (position <= 0) position = size; else position--; 
                break;
            case CHAR_RETURN:
                return position;
            default:
                break;
        } 
    }     
} 

template <typename T>
bool workArray(int size)
{
    bool result = false;
    ArrayClass<T>* array;
    try
    {
        array = new ArrayClass<T>(size);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        getChar();
        return true;
    }
    
    
    int event;
    while (true)
    {
        event = doVerticalMenu(
            "  Доступные функции:\n",
            MENU_EVENT,
            MENU_EVENT_SIZE
        ) - 1;

        switch (event)
        {
            case -1: 
                return false;
            case 0:
                delete array;
                return true;
                break;
            case 1:
                printArray<T>(*array);
                break;   
            case 2:
                resizeArray<T>(*array);
                break;
            case 3:
                eraseArray<T>(*array);
                break;
            case 4:
                editArray<T>(*array);
                break;
            case 5:
                findValue<T>(*array);
                break;
            default:
                break;
        }        

    }
    delete array;
    return event != -1;
}

bool initArrayData(int& arrayType, int& arraySize)
{
    arrayType = doVerticalMenu(
        "  СОЗДАНИЕ МАССВА\n  ВЫБЕРИТЕ ФОРМАТ ДАННЫХ:\n",
        MENU_TYPES,
        MENU_TYPES_SIZE
    ) - 1;
    if (arrayType == -1) 
        return false;
    cls();
    arraySize = 0;
    cout << "  СОЗДАНИЕ МАССВА\n  ВВЕДИТЕ РАЗМЕР МАССИВА:\n\n";
    cin >> arraySize;
    cls();

    cout << "  БУДЕТ СОЗДАН МАССВ\n  array<" 
        << MENU_TYPES[arrayType] << "> (" << arraySize << ")\n\n"
        << "press any key\n";
        getChar();
    return true;    
}

int main() 
{
    
    int arrayType = 0;
    int arraySize = 0;


    bool process = true;
    while (process)
    {
        process = initArrayData(arrayType, arraySize);
        if (arraySize > 15)
        {
            cout << "\nКонечно создать массив такого размера можно но работать с ним будет крайне не удобно\n";
            getChar();
        }    
        switch (arrayType)
        {
            case 0:
                process = workArray<int>(arraySize);
                break;
            case 1:
                process = workArray<float>(arraySize);
                break;
            case 2:
                process = workArray<string>(arraySize);
                break;    
            default:
                process = false;
                break;
        }     
    }
    

    return 0;
}