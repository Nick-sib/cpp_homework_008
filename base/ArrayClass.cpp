#include <iostream>
#include "ArrayClass.h"
#include "ArrayException.h"

template <typename T> 
ArrayClass<T>::ArrayClass(int length): _length(length)
{
    if (length < 0) 
        throw ArrayLengthException(_length);
    
    if (length > 0)
    _data = new T[length]{};
}

template <typename T> 
ArrayClass<T>::ArrayClass(ArrayClass<T>& array): _length(array.getLength())
{
    if (_length < 0) 
        throw ArrayLengthException(_length);
    
    if (_length > 0)
    {
        _data = new T[_length];
        std::copy(array._data, array._data + _length, _data);
    }
}

template <typename T> 
ArrayClass<T>::~ArrayClass()
{
    delete[] _data;
}

template <typename T> 
void ArrayClass<T>::erase()
{
    delete[] _data;
    _data = nullptr;
    _length = 0;
}

template <typename T> 
void ArrayClass<T>::erase(T defaultValue)
{
    if (_length < 0 || !_data)
        throw ArrayDataException();
    fill_n(_data, _length, defaultValue);
}

template <typename T> 
T& ArrayClass<T>::operator[](int index)
{
    return get(index);
}

template <typename T> 
T& ArrayClass<T>::get(int index)
{   
    if (index < 0 || index >= _length)
        throw ArrayRangeException(index, _length - 1);
    return _data[index];
}

template <typename T> 
int ArrayClass<T>::findFirst(T value)
{
    int result = -1;
    for (int i = 0; i < _length; i++)
     if (_data[i] == value) 
         return i;
    
    return result;
}

template <typename T> 
int ArrayClass<T>::findLast(T value)
{
    int result = -1;
    for (int i = _length - 1; i > -1; i--)
     if (_data[i] == value) 
         return i;

    return result;
}

template <typename T> 
void ArrayClass<T>::reallocate(int newLength)
{
    erase();
    if (newLength <= 0)
        return;
    _data = new T[newLength];
    _length = newLength;
}

template <typename T> 
void ArrayClass<T>::resize(int newLength)
{
    if (newLength == _length)
        return;

    if (newLength <= 0)
        throw ArrayLengthException(newLength);

    T* newData{ new T[newLength] };

    if (_length > 0)
    {
        int elementsToCopy{ (newLength > _length) ? _length : newLength };
        for (int index = 0; index < elementsToCopy ; ++index)
            newData[index] = _data[index];
    }

    delete[] _data;

    _data = newData;
    _length = newLength;
}

template <typename T> 
void ArrayClass<T>::insertAt(T value, int index)
{
    if (index < 0 || index > _length)
        throw ArrayRangeException(index, _length);

    T* data{ new T[_length+1] };
    for (int before{ 0 }; before < index; ++before)
        data [before] = _data[before];

    data[index] = value;

    for (int after{ index }; after < _length; ++after)
        data[after+1] = _data[after];

    delete[] _data;
    _data = data;
    ++_length;
}

template <typename T> 
void ArrayClass<T>::remove(int index)
{
    if (index < 0 || index >= _length)
        throw ArrayRangeException(index, _length - 1);

    if (_length == 1)
    {
        erase();
        return;
    }

    T* data{ new T[_length - 1] };

    for (int before{ 0 }; before  < index; ++before)
        data[before] = _data[before];

    for (int after{ index + 1 }; after < _length; ++after)
        data[after - 1] = _data[after];

    delete[] _data;
    _data = data;
    --_length;
}