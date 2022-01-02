#ifndef INTARRAY_H
#define INTARRAY_H

class IntArray
{
private:
    int _length{};
    int* _data{};

public:
    IntArray() = default;
    IntArray(int length);

    //extend fuctionality copying
    IntArray(IntArray& data);

    ~IntArray();

    void erase();
    void erase(int defaultValue);
    int& operator[](int index);
    int& get(int index);
    //if value is not finded find return -1
    int findFirst(int value);
    int findLast(int value);
    // reallocate resizes the array.  Any existing elements will be destroyed.  This function operates quickly.
    void reallocate(int newLength);
    // resize resizes the array.  Any existing elements will be kept.  This function operates slowly.
    void resize(int newLength);
    void insertAt(int value, int index);
    void remove(int index);

    // A couple of additional functions just for convenience
    void insertAtBeginning(int value);
    void insertAtEnd(int value);
    void Add(int value) { return insertAtEnd(value); }

    int getLength() const { return _length; }
};

#endif