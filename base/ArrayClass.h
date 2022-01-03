#ifndef INTARRAY_H
#define INTARRAY_H

template<typename T> 
class ArrayClass
{
    private:
        int _length = 0;
        T* _data = nullptr;

    public:
        ArrayClass() = default;
        ArrayClass(int length);
        ArrayClass(ArrayClass& data);
        ~ArrayClass();

        void erase();
        void erase(T defaultValue);
        T& operator[](int index);
        T& get(int index);
        int findFirst(T value);
        int findLast(T value);
        void reallocate(int newLength);
        void resize(int newLength);
        void insertAt(T value, int index);
        void remove(int index);

        void insertAtBeginning(T value) { insertAt(value, 0); };
        void insertAtEnd(T value) { insertAt(value, _length); };
        void Add(T value) { insertAtEnd(value); };

        int getLength() const { return _length; };
};

template class ArrayClass<int>;
template class ArrayClass<long>;
template class ArrayClass<float>;
template class ArrayClass<double>;
template class ArrayClass<char>;
template class ArrayClass<std::string>;


#endif