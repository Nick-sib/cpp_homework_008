#include <iostream>
#include "IntArray.h"
#include "ArrayException.h"


IntArray::IntArray(int length): _length(length)
{
    if (length < 0) 
        throw ArrayLengthException(_length);
    
    if (length > 0)
    _data = new int[length]{};
}

IntArray::IntArray(IntArray& array): _length(array.getLength())
{
    if (array.getLength() < 0) 
        throw ArrayLengthException(_length);
    
    if (_length > 0)
    {
        _data = new int[_length];
        std::copy(array._data, array._data + _length, _data);
    }
}

IntArray::~IntArray()
{
    delete[] _data;
    // we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
}

void IntArray::erase()
{
    delete[] _data;
    // We need to make sure we set m_data to nullptr here, otherwise it will
    // be left pointing at deallocated memory!
    _data = nullptr;
    _length = 0;
}

void IntArray::erase(int defaultValue)
{
    if (_length < 0 || !_data)
        throw ArrayDataException();
    fill_n(_data, _length, defaultValue);
}

int& IntArray::operator[](int index)
{
    return get(index);
}

int& IntArray::get(int index)
{   
    if (index < 0 || index >= _length)
        throw ArrayRangeException(index, _length - 1);
    return _data[index];
}

int IntArray::findFirst(int value)
{
    int result = -1;
    for (int i = 0; i < _length; i++)
     if (_data[i] == value) 
         return i;
    
    return result;
}


int IntArray::findLast(int value)
{
    int result = -1;
    for (int i = _length - 1; i > 0; i--)
     if (_data[i] == value) 
         return i;

    return result;
}

void IntArray::reallocate(int newLength)
{
    // First we delete any existing elements
    erase();

    // If our array is going to be empty now, return here
    if (newLength <= 0)
        return;

    // Then we have to allocate new elements
    _data = new int[newLength];
    _length = newLength;
}

void IntArray::resize(int newLength)
{
    // if the array is already the right length, we're done
    if (newLength == _length)
        return;

    // If we are resizing to an empty array, do that and return
    if (newLength <= 0)
    {
        throw ArrayLengthException(newLength);
        //return;
    }

    // Now we can assume newLength is at least 1 element.  This algorithm
    // works as follows: First we are going to allocate a new array.  Then we
    // are going to copy elements from the existing array to the new array.
    // Once that is done, we can destroy the old array, and make m_data
    // point to the new array.

    // First we have to allocate a new array
    int* data{ new int[newLength] };

    // Then we have to figure out how many elements to copy from the existing
    // array to the new array.  We want to copy as many elements as there are
    // in the smaller of the two arrays.
    if (_length > 0)
    {
        int elementsToCopy{ (newLength > _length) ? _length : newLength };

        // Now copy the elements one by one
        for (int index{ 0 }; index < elementsToCopy ; ++index)
            data[index] = _data[index];
    }

    // Now we can delete the old array because we don't need it any more
    delete[] _data;

    // And use the new array instead!  Note that this simply makes m_data point
    // to the same address as the new array we dynamically allocated.  Because
    // data was dynamically allocated, it won't be destroyed when it goes out of scope.
    _data = data;
    _length = newLength;
}

void IntArray::insertAt(int value, int index)
{
    // Sanity check our index value

    if (index < 0 || index > _length)
        throw ArrayRangeException(index, _length);

    // First create a new array one element larger than the old array
    int* data{ new int[_length+1] };

    // Copy all of the elements up to the index
    for (int before{ 0 }; before < index; ++before)
        data [before] = _data[before];

    // Insert our new element into the new array
    data[index] = value;

    // Copy all of the values after the inserted element
    for (int after{ index }; after < _length; ++after)
        data[after+1] = _data[after];

    // Finally, delete the old array, and use the new array instead
    delete[] _data;
    _data = data;
    ++_length;
}

void IntArray::remove(int index)
{
    // Sanity check our index value
    if (index < 0 || index >= _length)
        throw ArrayRangeException(index, _length - 1);

    // If we're removing the last element in the array, we can just erase the array and return early
    if (_length == 1)
    {
        erase();
        return;
    }

    // First create a new array one element smaller than the old array
    int* data{ new int[_length-1] };

    // Copy all of the elements up to the index
    for (int before{ 0 }; before  < index; ++before)
        data[before] = _data[before];

    // Copy all of the values after the removed element
    for (int after{ index+1 }; after < _length; ++after)
        data[after-1] = _data[after];

    // Finally, delete the old array, and use the new array instead
    delete[] _data;
    _data = data;
    --_length;
}

void IntArray::insertAtBeginning(int value) { insertAt(value, 0); }
void IntArray::insertAtEnd(int value) { insertAt(value, _length); }