//
//  Matrix.hpp
//  Algorithms
//
//  Created by lva on 3/10/18.
//  Copyright © 2018 Pandora. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdlib.h>

// MARK: -

template<typename T>
class Matrix
{
    struct Buffer
    {
        Buffer() : _refs(1), _data(nullptr), _rN(0), _cN(0) {}
        int _refs;
        T*  _data;
        int _rN, _cN;
    };
    
    Buffer* _sharedData;
    int _rN, _cN;
    int _r0, _c0;
private:
    Matrix();
private:
    void AllocateBuffer();
    void AssigneBuffer(Buffer* buffer);
    void DeleteBuffer();
public:
    explicit Matrix(int rN, int cN);
    explicit Matrix(int rN, int cN, void(*f)(T& v));
    virtual ~Matrix();
    
    Matrix(const Matrix<T>& matrix);
    Matrix(const Matrix<T>& matrix, int r0, int rN, int c0, int cN);
    
    Matrix<T> Row(int r);
    Matrix<T> Col(int c);
    
    T&  value(int r, int c) const;
    
    int Rows() const { return _rN; }
    int Cols() const { return _cN; }
    int Vals() const { return Rows()*Cols(); }
    
    void foreach( void(*f)(T& v) );
    void foreach( void(*f)(T& v, int r, int c, int rN, int cN) );
};

template<typename T>
Matrix<T> operator*(const Matrix<T>& A, const Matrix<T>& B)
{
    assert( A.Cols() == B.Rows() );
    Matrix<T> C(A.Rows(), B.Cols());
    
    for (int r=0; r<C.Rows(); ++r)
        for (int c=0; c<C.Cols(); ++c)
            for (int k=0; k<A.Cols(); ++k)
                C.value(r,c) += A.value(r,k) * B.value(k,c);
    
    return C;
}

// MARK: -

template<typename T>
void Matrix<T>::foreach( void(*f)(T& v) )
{
    for (int r=_r0; r<_r0+_rN; ++r)
    {
        for (int c=_c0; c<_c0+_cN; ++c)
        {
            f( _sharedData->_data[r*_sharedData->_cN+c] );
        }
    }
}

template<typename T>
void Matrix<T>::foreach( void(*f)(T& v, int r, int c, int rN, int cN) )
{
    for (int r=_r0; r<_r0+_rN; ++r)
    {
        for (int c=_c0; c<_c0+_cN; ++c)
        {
            f( _sharedData->_data[r*_sharedData->_cN+c], r-_r0, c-_c0, _rN, _cN );
        }
    }
}

template<typename T>
void Matrix<T>::AllocateBuffer()
{
    _sharedData = new Buffer();
    _sharedData->_rN = _rN;
    _sharedData->_cN = _cN;
    _sharedData->_data = new T[ _sharedData->_rN * _sharedData->_cN ];
}

template<typename T>
void Matrix<T>::AssigneBuffer(Buffer* buffer)
{
    _sharedData = buffer;
    _sharedData->_refs += 1;
}

template<typename T>
void Matrix<T>::DeleteBuffer()
{
    _sharedData->_refs -= 1;
    if ( 0 == _sharedData->_refs )
    {
        delete [] _sharedData->_data;
        
        delete _sharedData;
        _sharedData = nullptr;
    }
}

template<typename T>
Matrix<T>::Matrix(int rN, int cN) : _rN(rN) , _cN(cN), _r0(0), _c0(0)
{
    AllocateBuffer();
    foreach( [](T& v)->void{ v = T(0); } );
}

template<typename T>
Matrix<T>::Matrix(int rN, int cN, void(*f)(T& v)) : _rN(rN) , _cN(cN), _r0(0), _c0(0)
{
    AllocateBuffer();
    foreach( f );
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& matrix)
    : _sharedData(nullptr)
    , _r0(matrix._r0), _rN(matrix._rN)
    , _c0(matrix._c0), _cN(matrix._cN)
{
    AssigneBuffer(matrix._sharedData);
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& matrix, int r0, int rN, int c0, int cN)
    : _sharedData(matrix._sharedData)
    , _r0(matrix._r0 + r0), _rN(rN)
    , _c0(matrix._c0 + c0), _cN(cN)
{
    AssigneBuffer(matrix._sharedData);
}

template<typename T>
Matrix<T>::~Matrix()
{
    DeleteBuffer();
    _r0 = _rN = _c0 = _cN = 0;
}

template<typename T>
Matrix<T> Matrix<T>::Row(int r)
{
    return Matrix<T>( *this, r, 1, _c0, _cN );
}

template<typename T>
Matrix<T> Matrix<T>::Col(int c)
{
    return Matrix<T>( *this, _r0, _rN, c, 1 );
}

template<typename T>
T& Matrix<T>::value(int r, int c) const
{
    return _sharedData->_data[(r+_r0)*_sharedData->_cN+c+_c0];
}

#endif /* Matrix_hpp */






















