#include <exception>
#include <iostream>
#include <sstream>

using namespace std;

class BaseArrayExeption: virtual public exception
{
public:
    virtual const char* what() const noexcept override {return "Somthig got wrong";}
};

class ArrayDataException: public BaseArrayExeption
{
public:
    const char* what() const noexcept override 
    {
        return "ARRAY DATA is not available\n";
    }
};

class ArrayLengthException: public BaseArrayExeption
{
private:
    int _length;
public:
    ArrayLengthException(int length): _length(length){};
    const char* what() const noexcept override 
    {
        stringstream strs;
        strs << "WRONG length == " <<  _length << "; must be 0 or more\n";
        string str = strs.str();
        const char* res = (char*) str.c_str();
        const int MESSAGE_SIZE = 50;
        char* result = new char[MESSAGE_SIZE];
        copy(res, res + MESSAGE_SIZE, result);
        return result;
    }
};

class ArrayRangeException: public BaseArrayExeption
{
private:
    int _index;
    int _maxIndex;
public:
    ArrayRangeException(int index, int maxIndex): _index(index), _maxIndex(maxIndex){};
    const char* what() const noexcept override 
    {
        stringstream strs;
        if (_maxIndex != -1)
        {
            strs << "WRONG index == " << _index << "; must be in range 0.." << _maxIndex << endl;
        } else {
            strs << "WRONG index == " << _index << "; IntArray is empty\n";
        }
        string str = strs.str();
        const char* res = (char*) str.c_str();
        const int MESSAGE_SIZE = 50;
        char* result = new char[MESSAGE_SIZE];
        copy(res, res + MESSAGE_SIZE, result);
        return result;
    }
};

