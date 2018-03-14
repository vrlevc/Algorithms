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
#include <math.h>

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
    
    Matrix<T>& operator= (const Matrix<T>& matrix);
    Matrix<T>& operator+=(const Matrix<T>& matrix);
    
    Matrix<T> Row(int r);
    Matrix<T> Col(int c);
    
    T&  value(int r, int c) const;
    
    int Rows() const { return _rN; }
    int Cols() const { return _cN; }
    int Vals() const { return Rows()*Cols(); }
    
    void foreach( void(*f)(T& v) );
    void foreach( void(*f)(T& v, int r, int c) );
    void foreach( void(*f)(T& v, int r, int c, int rN, int cN) );
};

template<typename T>
Matrix<T> operator+(const Matrix<T>& A, const Matrix<T>& B);

template<typename T>
Matrix<T> operator-(const Matrix<T>& A, const Matrix<T>& B);

template<typename T>
Matrix<T> operator*(const Matrix<T>& A, const Matrix<T>& B);

template<typename T>
bool operator==(const Matrix<T>& A, const Matrix<T>& B);

template<typename T>
bool operator!=(const Matrix<T>& A, const Matrix<T>& B);

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix)
{
    if ( _sharedData != matrix._sharedData )
    {
        assert( matrix.Rows() == Rows()&& matrix.Cols() == Cols() );
    
        for (int r=0; r<Rows(); ++r)
            for (int c=0; c<Cols(); ++c)
                value(r,c) = matrix.value(r,c);
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T> &matrix)
{
    assert( Rows() == matrix.Rows()&& Cols() == matrix.Cols() );
    
    for (int r=0; r<Rows(); ++r)
        for (int c=0; c<Cols(); ++c)
            value(r,c) += matrix.value(r,c);
    
    return *this;
}

template<typename T>
Matrix<T> operator+(const Matrix<T>& A, const Matrix<T>& B)
{
    assert( A.Rows() == B.Rows()&& A.Cols() == B.Cols() );
    Matrix<T> C(A.Rows(), A.Cols());
    
    for (int r=0; r<C.Rows(); ++r)
        for (int c=0; c<C.Cols(); ++c)
            C.value(r,c) = A.value(r,c) + B.value(r,c);
    
    return C;
}

template<typename T>
Matrix<T> operator-(const Matrix<T>& A, const Matrix<T>& B)
{
    assert( A.Rows() == B.Rows()&& A.Cols() == B.Cols() );
    Matrix<T> C(A.Rows(), A.Cols());
    
    for (int r=0; r<C.Rows(); ++r)
        for (int c=0; c<C.Cols(); ++c)
            C.value(r,c) = A.value(r,c) - B.value(r,c);
    
    return C;
}

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

template<typename T>
bool operator==(const Matrix<T>& A, const Matrix<T>& B)
{
    bool equal = ( A.Rows() == B.Rows()&& A.Cols() == B.Cols() );
    if ( equal )
    {
        for (int r=0; r<A.Rows()&&equal; ++r)
            for (int c=0; c<A.Cols()&&equal; ++c)
                equal = ( A.value(r,c) == B.value(r,c) );
    }
    return equal;
}

template<typename T>
bool operator!=(const Matrix<T>& A, const Matrix<T>& B)
{
    return !( A == B );
}

template<typename T>
Matrix<T> MatrixMultR(const Matrix<T>& A, const Matrix<T>& B)
{
    assert(A.Cols() == B.Rows());
    
    int N = A.Rows();
    Matrix<T> C(N, N);
    
    if ( N==1 )
    {
        C.value(0, 0) = A.value(0, 0) * B.value(0, 0);
    }
    else
    {
        int n = N / 2;
        
        Matrix<T> A11(A, 0, n, 0, n), A12(A, 0, n, n, n);
        Matrix<T> A21(A, n, n, 0, n), A22(A, n, n, n, n);
        
        Matrix<T> B11(B, 0, n, 0, n), B12(B, 0, n, n, n);
        Matrix<T> B21(B, n, n, 0, n), B22(B, n, n, n, n);
        
        Matrix<T> C11(C, 0, n, 0, n), C12(C, 0, n, n, n);
        Matrix<T> C21(C, n, n, 0, n), C22(C, n, n, n, n);
        
        C11 = MatrixMultR(A11,B11) + MatrixMultR(A12,B21);
        C12 = MatrixMultR(A11,B12) + MatrixMultR(A12,B22);
        C21 = MatrixMultR(A21,B11) + MatrixMultR(A22,B21);
        C22 = MatrixMultR(A21,B12) + MatrixMultR(A22,B22);
        
        if ( N % 2 == 1 )
        {
            Matrix<T> A13(A,   0, n, N-1, 1), A23(A,  n,  n, N-1, 1);
            Matrix<T> A31(A, N-1, 1,   0, n), A32(A, N-1, 1,   n, n);
            Matrix<T> A33(A, N-1, 1, N-1, 1), B33(B, N-1, 1, N-1, 1);
            Matrix<T> B13(B,   0, n, N-1, 1), B23(B,  n,  n, N-1, 1);
            Matrix<T> B31(B, N-1, 1,   0, n), B32(B, N-1, 1,   n, n);
            
            C11 += A13*B31;     C12 += A13*B32;
            C21 += A23*B31;     C22 += A23*B32;
            
            Matrix<T> C31(C, N-1, 1, 0, n), C32(C, N-1, 1, n, n);
            Matrix<T> C13(C, 0, n, N-1, 1), C23(C, n, n, N-1, 1);
            Matrix<T> C33(C, N-1, 1, N-1, 1);
            
            C31 = A31*B11 + A32*B21 + A33*B31;
            C32 = A31*B12 + A32*B22 + A33*B32;
            C13 = A11*B13 + A12*B23 + A13*B33;
            C23 = A21*B13 + A22*B23 + A23*B33;
            C33 = A31*B13 + A32*B23 + A33*B33;
        }
    }
    return C;
}

template<typename T>
Matrix<T> MatrixMultStrassen(const Matrix<T>& A, const Matrix<T>& B)
{
    assert(A.Cols() == B.Rows());
    
    int N = A.Rows();
    Matrix<T> C(N, N);
    
    if ( N==1 )
    {
        C.value(0, 0) = A.value(0, 0) * B.value(0, 0);
    }
    else
    {
        int n = N / 2;
        
        Matrix<T> A11(A, 0, n, 0, n), A12(A, 0, n, n, n);
        Matrix<T> A21(A, n, n, 0, n), A22(A, n, n, n, n);
        
        Matrix<T> B11(B, 0, n, 0, n), B12(B, 0, n, n, n);
        Matrix<T> B21(B, n, n, 0, n), B22(B, n, n, n, n);
        
        Matrix<T> S1(n,n), S2(n,n), S3(n,n), S4(n,n), S5(n,n), S6(n,n), S7(n,n), S8(n,n), S9(n,n), S10(n,n);
        
        S1  = B12 - B22;
        S2  = A11 + A12;
        S3  = A21 + A22;
        S4  = B21 - B11;
        S5  = A11 + A22;
        S6  = B11 + B22;
        S7  = A12 - A22;
        S8  = B21 + B22;
        S9  = A11 - A21;
        S10 = B11 + B12;

        Matrix<T> P1(n,n), P2(n,n), P3(n,n), P4(n,n), P5(n,n), P6(n,n), P7(n,n);
        
        P1 = MatrixMultStrassen(A11,  S1);
        P2 = MatrixMultStrassen( S2, B22);
        P3 = MatrixMultStrassen( S3, B11);
        P4 = MatrixMultStrassen(A22,  S4);
        P5 = MatrixMultStrassen( S5,  S6);
        P6 = MatrixMultStrassen( S7,  S8);
        P7 = MatrixMultStrassen( S9, S10);
        
        Matrix<T> C11(C, 0, n, 0, n), C12(C, 0, n, n, n);
        Matrix<T> C21(C, n, n, 0, n), C22(C, n, n, n, n);
        
        C11 = P5 + P4 - P2 + P6;
        C12 = P1 + P2;
        C21 = P3 + P4;
        C22 = P5 + P1 - P3 - P7;
        
        if ( N % 2 == 1 )
        {
            Matrix<T> A13(A,   0, n, N-1, 1), A23(A,  n,  n, N-1, 1);
            Matrix<T> A31(A, N-1, 1,   0, n), A32(A, N-1, 1,   n, n);
            Matrix<T> A33(A, N-1, 1, N-1, 1), B33(B, N-1, 1, N-1, 1);
            Matrix<T> B13(B,   0, n, N-1, 1), B23(B,  n,  n, N-1, 1);
            Matrix<T> B31(B, N-1, 1,   0, n), B32(B, N-1, 1,   n, n);
            
            C11 += A13*B31;     C12 += A13*B32;
            C21 += A23*B31;     C22 += A23*B32;
            
            Matrix<T> C31(C, N-1, 1, 0, n), C32(C, N-1, 1, n, n);
            Matrix<T> C13(C, 0, n, N-1, 1), C23(C, n, n, N-1, 1);
            Matrix<T> C33(C, N-1, 1, N-1, 1);
            
            C31 = A31*B11 + A32*B21 + A33*B31;
            C32 = A31*B12 + A32*B22 + A33*B32;
            C13 = A11*B13 + A12*B23 + A13*B33;
            C23 = A21*B13 + A22*B23 + A23*B33;
            C33 = A31*B13 + A32*B23 + A33*B33;
        }
    }
    
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
void Matrix<T>::foreach( void(*f)(T& v, int r, int c) )
{
    for (int r=_r0; r<_r0+_rN; ++r)
    {
        for (int c=_c0; c<_c0+_cN; ++c)
        {
            f( _sharedData->_data[r*_sharedData->_cN+c], r-_r0, c-_c0 );
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






















