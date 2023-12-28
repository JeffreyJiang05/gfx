#ifndef JGRAPHICS_VEC_HPP
#define JGRAPHICS_VEC_HPP

#include <iostream>
#include <stdexcept>

/**
 * represents a simple vector
 * allows only for simple read and write of components
 * access components through x,y,z,w functions if applicable. these are return by value.
 * access components through subscript operator. does not perform bounds checking
 * access components through vec<N>::at function. performs bounds checking and throws std::out_of_range exception 
 * 
 * T is required to be default constructible, support arithmetic operations, equality operations, copy and move constructible, etc
*/
template<unsigned N, typename T>
class vec;

//====================================================================================//

template<typename T>
class vec<2, T>
{
public:
    using value_type = T;
private:
    value_type _data[2];
public:
    // CONSTRUCTORS
    vec();
    vec(const vec&) = default;
    vec(vec&&) = default;
    vec& operator=(const vec&) = default;
    vec& operator=(vec&&) = default;

    explicit vec(value_type x, value_type y);

    template<typename U>
    explicit vec(const vec<2,U>& cpy);

    template<typename T0, typename T1>
    explicit vec(T0 x, T1 y);

    // ACCESSORS + MODIFIERS
    value_type& operator[](unsigned idx);
    const value_type& operator[](unsigned idx) const;
    value_type& at(unsigned idx);
    const value_type& at(unsigned idx) const;

    value_type x() const;
    value_type y() const;

    // OPERATORS
    template<typename U>
    vec& operator=(const vec<2,U>& cpy);

    // UNARY ARITHMETIC OPS
    template<typename U>
    vec& operator+=(const vec<2,U>& vector);
    vec& operator+=(value_type scalar);

    template<typename U>
    vec& operator-=(const vec<2,U>& vector);
    vec& operator-=(value_type scalar);

    template<typename U>
    vec& operator*=(const vec<2,U>& vector);
    vec& operator*=(value_type scalar);

    template<typename U>
    vec& operator/=(const vec<2,U>& vector);
    vec& operator/=(value_type scalar);

    // UNARY INC-DEC OPS
    vec& operator++();
    vec operator++(int);
    vec& operator--();
    vec operator--(int);
};

#include "Vec2.inl"

//====================================================================================//

template<typename T>
class vec<3, T>
{
public:
    using value_type = T;
private:
    value_type _data[3];
public:
    // CONSTRUCTORS
    vec();
    vec(const vec&) = default;
    vec(vec&&) = default;
    vec& operator=(const vec&) = default;
    vec& operator=(vec&&) = default;

    explicit vec(value_type x, value_type y, value_type z);

    template<typename U>
    explicit vec(const vec<2, U>& vec, value_type z);

    template<typename U>
    explicit vec(const vec<3,U>& cpy);

    template<typename T0, typename T1, typename T2>
    explicit vec(T0 x, T1 y, T2 z);

    // ACCESSORS + MODIFIERS
    value_type& operator[](unsigned idx);
    const value_type& operator[](unsigned idx) const;
    value_type& at(unsigned idx);
    const value_type& at(unsigned idx) const;

    value_type x() const;
    value_type y() const;
    value_type z() const;

    // EXPLICIT CONVERSIONS
    template<typename U>
    explicit operator vec<2, U>();

    // OPERATORS
    template<typename U>
    vec& operator=(const vec<3,U>& cpy);

    template<typename U>
    vec& operator+=(const vec<3,U>& vector);
    vec& operator+=(value_type scalar);

    template<typename U>
    vec& operator-=(const vec<3,U>& vector);
    vec& operator-=(value_type scalar);

    template<typename U>
    vec& operator*=(const vec<3,U>& vector);
    vec& operator*=(value_type scalar);

    template<typename U>
    vec& operator/=(const vec<3,U>& vector);
    vec& operator/=(value_type scalar);

    // UNARY INC-DEC OPS
    vec& operator++();
    vec operator++(int);
    vec& operator--();
    vec operator--(int);
};

#include "Vec3.inl"

//====================================================================================//

template<typename T>
class vec<4, T>
{
public:
    using value_type = T;
private:
    double _data[4];
public:
    // CONSTRUCTORS
    vec();
    vec(const vec&) = default;
    vec(vec&&) = default;
    vec& operator=(const vec&) = default;
    vec& operator=(vec&&) = default;

    vec(value_type x, value_type y, value_type z, value_type w);

    template<typename U>
    vec(const vec<2,U>& vec, value_type z, value_type w);

    template<typename U>
    vec(const vec<3,U>& vec, value_type w);

    template<typename U>
    explicit vec(const vec<4,U>& cpy);

    template<typename T0, typename T1, typename T2, typename T3>
    explicit vec(T0 x, T1 y, T2 z, T3 w);

    // ACCESSORS + MODIFIERS
    value_type& operator[](unsigned idx);
    const value_type& operator[](unsigned idx) const;
    value_type& at(unsigned idx);
    const value_type& at(unsigned idx) const;

    value_type x() const;
    value_type y() const;
    value_type z() const;
    value_type w() const;

    // EXPLICIT CONVERSIONS
    template<typename U>
    explicit operator vec<2,U>();

    template<typename U>
    explicit operator vec<3,U>();

    // OPERATORS
    template<typename U>
    vec& operator=(const vec<4,U>& cpy);

    template<typename U>
    vec& operator+=(const vec<4,U>& vector);
    vec& operator+=(value_type scalar);

    template<typename U>
    vec& operator-=(const vec<4,U>& vector);
    vec& operator-=(value_type scalar);

    template<typename U>
    vec& operator*=(const vec<4,U>& vector);
    vec& operator*=(value_type scalar);

    template<typename U>
    vec& operator/=(const vec<4,U>& vector);
    vec& operator/=(value_type scalar);

    // UNARY INC-DEC OPS
    vec& operator++();
    vec operator++(int);
    vec& operator--();
    vec operator--(int);
};

#include "Vec4.inl"

//====================================================================================//

using vec2 = vec<2, double>;
using vec3 = vec<3, double>;
using vec4 = vec<4, double>;

using ivec2 = vec<2, int>;
using ivec3 = vec<3, int>;
using ivec4 = vec<4, int>;

/**
 * Basic Vector Operations
 * Includes pairwise vector operations
 * Includes vector operations such as cross product, dot product, etc
 * Includes scalar vector operations
*/

// COMPARISON OPERATORS
template<unsigned N, typename T, typename U>
bool operator==(const vec<N,T>& a, const vec<N,U>& b);

template<unsigned N, typename T, typename U>
bool operator!=(const vec<N,T>& a, const vec<N,U>& b);

// BASIC PAIRWISE ARITHMETIC OPERATORS
template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator+(const vec<N,T>& a, const vec<N,U>& b);

template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator-(const vec<N,T>& a, const vec<N,U>& b);

template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator*(const vec<N,T>& a, const vec<N,U>& b);

template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator/(const vec<N,T>& a, const vec<N,U>& b);

// VECTOR-SCALAR OPERATIONS
template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator+(const vec<N,T>& a, U k);

template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator-(const vec<N,T>& a, U k);

template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator*(const vec<N,T>& a, U k);

template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator/(const vec<N,T>& a, U k);

template<unsigned N, typename U, typename T>
vec<N,std::common_type_t<U,T>> operator+(U k, const vec<N,T>& a);

template<unsigned N, typename U, typename T>
vec<N,std::common_type_t<U,T>> operator-(U k, const vec<N,T>& a);

template<unsigned N, typename U, typename T>
vec<N,std::common_type_t<U,T>> operator*(U k, const vec<N,T>& a);

template<unsigned N, typename U, typename T>
vec<N,std::common_type_t<U,T>> operator/(U k, const vec<N,T>& a);

// VECTOR OPERATIONS
template<typename T>
vec<3,T> cross(const vec<3,T>& a, const vec<3,T>& b);

template<unsigned N,typename T>
T dot(const vec<N,T>& a, const vec<N,T>& b);

template<unsigned N, typename T>
double magnitude(const vec<N,T>& a);

template<unsigned N, typename T>
vec<N,double> normalize(const vec<N,T>& a);

// OUT STREAM FORMATTING
template<unsigned N, typename T>
std::ostream& operator<<(std::ostream& out, const vec<N,T>& vec);

#include "Vec.inl"

#endif