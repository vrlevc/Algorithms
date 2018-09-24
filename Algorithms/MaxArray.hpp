#ifndef MAXARRAY_H
#define MAXARRAY_H

// 1. Define arrary for working with
// 2. Functions for filling array with data.
// 3. Functions for printing arrays
// 4. Max subarray algorithms

#include <stdlib.h>
#include <algorithm>

// MARK: Array

template<typename T>
class Array
{
    T* buff;
    size_t size;
public:
    Array();
    Array(size_t N);
    Array(size_t N, void(*f)(T& v));
    ~Array();
    
    void SetSize(size_t N); // set size and reallocate buff if need
    void Foreach(void(*f)(T& v)); // call function for each array element
    void Foreach(bool diffArray, void(*f)(T& v));
private:

};

template<typename T>
Array<T>::~Array()
{
    delete [] buff;
    size = 0;
}

template<typename T>
Array<T>::Array() : buff(nullptr)
{
}

template<typename T>
Array<T>::Array(size_t N) : buff(nullptr)
{
    SetSize(N); // allocate array
    Foreach( [](T& v)->void{ v = T(0); } ); // fill array with T(0)
}

template<typename T>
Array<T>::Array(size_t N, void(*f)(T& v)) : buff(nullptr)
{
    SetSize(N); // allocate array
    Foreach(f); // fill array using function
}

template<typename T>
void Array<T>::SetSize(size_t N)
{
    if (N != size)
    {
        T* _newBuff = new T[N];
        for (size_t i=0; i<std::min(size,N); ++i)
            _newBuff[i] = buff[i];
        delete [] buff;
        buff = _newBuff;
        size = N;
    }
}

template<typename T>
void Array<T>::Foreach(void(*f)(T& v))
{
    for (size_t i=0; i<size; ++i)
        f( buff[i] );
}

template<typename T>
void Array<T>::Foreach(bool diffArray, void(*f)(T& v))
{
    // for (size_t)
}

// MARK: main

void mainArray();

#endif /* MAXARRAY_H */






















