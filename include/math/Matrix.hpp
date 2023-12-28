#ifndef JGRAPHICS_MATRIX_HPP
#define JGRAPHICS_MATRIX_HPP

#include <iostream>

#include "Vec.hpp"

/**
 * Column-major matrix
 * matrix<num of col, num of row>
*/
template<unsigned Col, unsigned Row, typename T>
class matrix;

template<typename T>
class matrix<2,2,T>
{
public:
    using col_type = vec<2,T>;
    using value_type = T;
    static constexpr unsigned Rows = 2;
    static constexpr unsigned Cols = 2;
private:
    col_type _data[2];
public: 
    // CONSTRUCTORS
    matrix();
    matrix(const matrix&) = default;
    matrix(matrix&&) = default;

    explicit matrix(value_type fill);

    explicit matrix(vec<2,T> c0, vec<2,T> c1);

    template<typename U>
    explicit matrix(const matrix<2,2,U>& cpy);

    // ACCESSORS + MODIFIERS
    col_type& operator[](unsigned idx);
    const col_type& operator[](unsigned idx) const;
    col_type& at(unsigned idx);
    const col_type& at(unsigned idx) const;

    // ASSIGNMENT
    matrix& operator=(const matrix&) = default;
    matrix& operator=(matrix&&) = default;

    template<typename U>
    matrix& operator=(const matrix<2,2,U>& cpy);

    // OPERATORS
    template<typename U>
    matrix& operator+=(const matrix<2,2,U>& mat);
    matrix& operator+=(value_type scalar);

    template<typename U>
    matrix& operator-=(const matrix<2,2,U>& mat);
    matrix& operator-=(value_type scalar);

    template<typename U>
    matrix& operator*=(const matrix<2,2,U>& mat);
    matrix& operator*=(value_type scalar);

    template<typename U>
    matrix& operator/=(const matrix<2,2,U>& mat);
    matrix& operator/=(value_type scalar);

    template<typename U>
    matrix& operator%=(const matrix<2,2,U>& mat);
    matrix& operator%=(value_type scalar);

    matrix& operator++();
    matrix operator++(int);
    matrix& operator--();
    matrix operator--(int);
};

#include "Matrix2x2.inl"

//====================================================================================//

template<typename T>
class matrix<3,3,T>
{
public:
    using col_type = vec<3,T>;
    using value_type = T;
    static constexpr unsigned Rows = 3;
    static constexpr unsigned Cols = 3;
private:
    col_type _data[3];
public: 
    // CONSTRUCTORS
    matrix();
    matrix(const matrix&) = default;
    matrix(matrix&&) = default;

    explicit matrix(value_type fill);

    explicit matrix(vec<3,T> c0, vec<3,T> c1, vec<3,T> c2);

    template<typename U>
    explicit matrix(const matrix<3,3,U>& cpy);

    col_type& operator[](unsigned idx);
    const col_type& operator[](unsigned idx) const;
    col_type& at(unsigned idx);
    const col_type& at(unsigned idx) const;

    // EXPLICIT CONVERSION
    template<unsigned Dim, typename U, typename Enable = std::enable_if<(Dim <= 3 && Dim <= 3 && std::is_convertible_v<T,U>)>>
    explicit operator matrix<Dim,Dim,U>();

    // ASSIGNMENT
    matrix& operator=(const matrix&) = default;
    matrix& operator=(matrix&&) = default;

    template<typename U>
    matrix& operator=(const matrix<3,3,U>& cpy);

    // OPERATORS
    template<typename U>
    matrix& operator+=(const matrix<3,3,U>& mat);
    matrix& operator+=(value_type scalar);

    template<typename U>
    matrix& operator-=(const matrix<3,3,U>& mat);
    matrix& operator-=(value_type scalar);

    template<typename U>
    matrix& operator*=(const matrix<3,3,U>& mat);
    matrix& operator*=(value_type scalar);

    template<typename U>
    matrix& operator/=(const matrix<3,3,U>& mat);
    matrix& operator/=(value_type scalar);

    template<typename U>
    matrix& operator%=(const matrix<3,3,U>& mat);
    matrix& operator%=(value_type scalar);

    matrix& operator++();
    matrix operator++(int);
    matrix& operator--();
    matrix operator--(int);
};

#include "Matrix3x3.inl"

//====================================================================================//

template<typename T>
class matrix<4,4,T>
{
public:
    using col_type = vec<4,T>;
    using value_type = T;
    static constexpr unsigned Rows = 4;
    static constexpr unsigned Cols = 4;
private:
    col_type _data[4];
public: 
    // CONSTRUCTORS
    matrix();
    matrix(const matrix&) = default;
    matrix(matrix&&) = default;

    explicit matrix(value_type fill);

    explicit matrix(vec<4,T> c0, vec<4,T> c1, vec<4,T> c2, vec<4,T> c3);

    template<typename U>
    explicit matrix(const matrix<4,4,U>& cpy);

    col_type& operator[](unsigned idx);
    const col_type& operator[](unsigned idx) const;
    col_type& at(unsigned idx);
    const col_type& at(unsigned idx) const;

    // EXPLICIT CONVERSION
    template<unsigned Dim, typename U, typename Enable = std::enable_if<(Dim <= 4 && Dim <= 4 && std::is_convertible_v<T,U>)>>
    explicit operator matrix<Dim,Dim,U>();

    // ASSIGNMENT
    matrix& operator=(const matrix&) = default;
    matrix& operator=(matrix&&) = default;

    template<typename U>
    matrix& operator=(const matrix<4,4,U>& cpy);

    // OPERATORS
    template<typename U>
    matrix& operator+=(const matrix<4,4,U>& mat);
    matrix& operator+=(value_type scalar);

    template<typename U>
    matrix& operator-=(const matrix<4,4,U>& mat);
    matrix& operator-=(value_type scalar);

    template<typename U>
    matrix& operator*=(const matrix<4,4,U>& mat);
    matrix& operator*=(value_type scalar);

    template<typename U>
    matrix& operator/=(const matrix<4,4,U>& mat);
    matrix& operator/=(value_type scalar);

    template<typename U>
    matrix& operator%=(const matrix<4,4,U>& mat);
    matrix& operator%=(value_type scalar);

    matrix& operator++();
    matrix operator++(int);
    matrix& operator--();
    matrix operator--(int);
};

#include "Matrix4x4.inl"

//====================================================================================//

using mat2x2 = matrix<2,2,double>;
using mat3x3 = matrix<3,3,double>;
using mat4x4 = matrix<4,4,double>;

//====================================================================================//
// MATRIX FREE FUNCTIONS

#define RESULT(T1,T2,OP) decltype(std::declval<T1>() OP std::declval<T2>())

// BINARY OPERATIONS
template<unsigned Dim, typename T, typename U>
matrix<Dim,Dim,RESULT(T,U,+)> operator+(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2);

template<unsigned Dim, typename T, typename U>
matrix<Dim,Dim,RESULT(T,U,-)> operator-(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2);

template<typename T, typename U>
matrix<2,2,RESULT(T,U,*)> operator*(const matrix<2,2,T>& m1, const matrix<2,2,U>& m2);

template<typename T, typename U>
matrix<3,3,RESULT(T,U,*)> operator*(const matrix<3,3,T>& m1, const matrix<3,3,U>& m2);

template<typename T, typename U>
matrix<4,4,RESULT(T,U,*)> operator*(const matrix<4,4,T>& m1, const matrix<4,4,U>& m2);

template<typename T, typename U>
vec<2,RESULT(T,U,*)> operator*(const matrix<2,2,T>& m, const vec<2,U>& v);

template<typename T, typename U>
vec<3,RESULT(T,U,*)> operator*(const matrix<3,3,T>& m, const vec<3,U>& v);

template<typename T, typename U>
vec<4,RESULT(T,U,*)> operator*(const matrix<4,4,T>& m, const vec<4,U>& v);

// BASIC MATRIX OPERATIONS
template<typename T>
matrix<2,2,T> transpose(const matrix<2,2,T>& m);

template<typename T>
matrix<3,3,T> transpose(const matrix<3,3,T>& m);

template<typename T>
matrix<4,4,T> transpose(const matrix<4,4,T>& m);

template<typename T>
T determinant(const matrix<2,2,T>& m);

template<typename T>
T determinant(const matrix<3,3,T>& m);

template<typename T>
T determinant(const matrix<4,4,T>& m);

template<typename T>
matrix<2,2,T> inverse(const matrix<2,2,T>& m);

template<typename T>
matrix<3,3,T> inverse(const matrix<3,3,T>& m);

template<typename T>
matrix<4,4,T> inverse(const matrix<4,4,T>& m);

// STREAM OPERATOR
template<unsigned Col, unsigned Row, typename T>
std::ostream& operator<<(std::ostream& out, const matrix<Col,Row,T>& mat);

#include "Matrix_Func.inl"

#endif