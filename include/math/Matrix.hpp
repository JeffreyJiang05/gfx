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
    constexpr matrix();
    matrix(const matrix&) = default;
    matrix(matrix&&) = default;

    constexpr explicit matrix(value_type fill);

    constexpr explicit matrix(vec<2,T> c0, vec<2,T> c1);

    template<typename U>
    explicit matrix(const matrix<2,2,U>& cpy);

    // ACCESSORS + MODIFIERS
    col_type& operator[](unsigned idx);
    constexpr const col_type& operator[](unsigned idx) const;
    col_type& at(unsigned idx);
    constexpr const col_type& at(unsigned idx) const;

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
    constexpr matrix();
    matrix(const matrix&) = default;
    matrix(matrix&&) = default;

    constexpr explicit matrix(value_type fill);

    constexpr explicit matrix(vec<3,T> c0, vec<3,T> c1, vec<3,T> c2);

    template<typename U>
    explicit matrix(const matrix<3,3,U>& cpy);

    col_type& operator[](unsigned idx);
    constexpr const col_type& operator[](unsigned idx) const;
    col_type& at(unsigned idx);
    constexpr const col_type& at(unsigned idx) const;

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
    constexpr matrix();
    matrix(const matrix&) = default;
    matrix(matrix&&) = default;

    constexpr explicit matrix(value_type fill);

    constexpr explicit matrix(vec<4,T> c0, vec<4,T> c1, vec<4,T> c2, vec<4,T> c3);

    template<typename U>
    explicit matrix(const matrix<4,4,U>& cpy);

    col_type& operator[](unsigned idx);
    constexpr const col_type& operator[](unsigned idx) const;
    col_type& at(unsigned idx);
    constexpr const col_type& at(unsigned idx) const;

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
constexpr matrix<Dim,Dim,RESULT(T,U,+)> operator+(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2);

template<unsigned Dim, typename T, typename U>
constexpr matrix<Dim,Dim,RESULT(T,U,-)> operator-(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2);

template<unsigned Dim, typename T, typename U>
constexpr matrix<Dim,Dim,RESULT(T,U,*)> operator*(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2);

template<unsigned Dim, typename T, typename U>
constexpr vec<Dim,RESULT(T,U,*)> operator*(const matrix<Dim,Dim,T>& m, const vec<Dim,U>& v);

template<unsigned Dim, typename T, typename U>
constexpr matrix<Dim,Dim,RESULT(T,U,*)> operator*(const matrix<Dim,Dim,T>& m, U val);

template<unsigned Dim, typename T, typename U>
constexpr matrix<Dim,Dim,RESULT(T,U,/)> operator/(const matrix<Dim,Dim,T>& m, U val);

// BASIC MATRIX OPERATIONS
template<unsigned N, typename T>
constexpr matrix<N,N,T> transpose(const matrix<N,N,T>& m);

template<unsigned N, typename T>
constexpr T determinant(const matrix<N,N,T>& m);

template<unsigned N, typename T>
constexpr matrix<N,N,T> inverse(const matrix<N,N,T>& m);

// STREAM OPERATOR
template<unsigned Col, unsigned Row, typename T>
std::ostream& operator<<(std::ostream& out, const matrix<Col,Row,T>& mat);

#include "Matrix_Func.inl"

#endif