#include "Matrix.hpp"

// CONSTRUCTORS
template<typename T>
constexpr matrix<3,3,T>::matrix() : _data{ 
    vec<3,T>{ 1, 0, 0 }, 
    vec<3,T>{ 0, 1, 0 }, 
    vec<3,T>{ 0, 0, 1 } } {}

template<typename T>
constexpr matrix<3,3,T>::matrix(value_type fill) : _data{ 
    vec<3,T>{ fill, fill, fill }, 
    vec<3,T>{ fill, fill, fill }, 
    vec<3,T>{ fill, fill, fill } } {}

template<typename T>
constexpr matrix<3,3,T>::matrix(vec<3,T> c0, vec<3,T> c1, vec<3,T> c2) : _data{ c0, c1, c2 } {}

template<typename T>
template<typename U>
matrix<3,3,T>::matrix(const matrix<3,3,U>& cpy) : _data{ 
    static_cast<vec<3,T>>(cpy[0]), 
    static_cast<vec<3,T>>(cpy[1]), 
    static_cast<vec<3,T>>(cpy[2]) } {}

// ACCESSORS + MODIFIERS
template<typename T>
auto matrix<3,3,T>::operator[](unsigned idx) -> col_type& 
{
    return _data[idx];
}

template<typename T>
constexpr auto matrix<3,3,T>::operator[](unsigned idx) const -> const col_type&
{
    return _data[idx];
}

template<typename T>
auto matrix<3,3,T>::at(unsigned idx) -> col_type&
{
    if (idx >= 3) throw std::out_of_range{ "Index " + std::to_string(idx) + " out of range for mat3x3." };
    return _data[idx];
}

template<typename T>
constexpr auto matrix<3,3,T>::at(unsigned idx) const -> const col_type&
{
    if (idx >= 3) throw std::out_of_range{ "Index " + std::to_string(idx) + " out of range for mat3x3." };
    return _data[idx];
}

// EXPLICIT CONVERSION
template<typename T>
template<unsigned Dim, typename U, typename Enable>
matrix<3,3,T>::operator matrix<Dim,Dim,U>()
{
    matrix<Dim,Dim,U> res{ U() };
    for (unsigned i = 0; i < Dim; ++i)
    {
        res[i] = static_cast<vec<Dim,U>>(_data[i]);
    }
    return res;
}

// ASSIGNMENT
template<typename T>
template<typename U>
auto matrix<3,3,T>::operator=(const matrix<3,3,U>& cpy) -> matrix&
{
    _data[0] = static_cast<vec<3,T>>(cpy[0]);
    _data[1] = static_cast<vec<3,T>>(cpy[1]);
    _data[2] = static_cast<vec<3,T>>(cpy[2]);
    return *this;
}

// OPERATORS
template<typename T>
template<typename U>
matrix<3,3,T>& matrix<3,3,T>::operator+=(const matrix<3,3,U>& mat)
{
    _data[0] += mat[0];
    _data[1] += mat[1];
    _data[2] += mat[2];
    return *this;
}

template<typename T>
matrix<3,3,T>& matrix<3,3,T>::operator+=(value_type scalar)
{
    _data[0] += scalar;
    _data[1] += scalar;
    _data[2] += scalar;
    return *this;
}

template<typename T>
template<typename U>
matrix<3,3,T>& matrix<3,3,T>::operator-=(const matrix<3,3,U>& mat)
{
    _data[0] -= mat[0];
    _data[1] -= mat[1];
    _data[2] -= mat[2];
    return *this;
}

template<typename T>
matrix<3,3,T>& matrix<3,3,T>::operator-=(value_type scalar)
{
    _data[0] -= scalar;
    _data[1] -= scalar;
    _data[2] -= scalar;
    return *this;
}

template<typename T>
template<typename U>
matrix<3,3,T>& matrix<3,3,T>::operator*=(const matrix<3,3,U>& mat)
{
    _data[0] *= mat[0];
    _data[1] *= mat[1];
    _data[2] *= mat[2];
    return *this;
}

template<typename T>
matrix<3,3,T>& matrix<3,3,T>::operator*=(value_type scalar)
{
    _data[0] *= scalar;
    _data[1] *= scalar;
    _data[2] *= scalar;
    return *this;
}

template<typename T>
template<typename U>
matrix<3,3,T>& matrix<3,3,T>::operator/=(const matrix<3,3,U>& mat)
{
    _data[0] /= mat[0];
    _data[1] /= mat[1];
    _data[2] /= mat[2];
    return *this;
}

template<typename T>
matrix<3,3,T>& matrix<3,3,T>::operator/=(value_type scalar)
{
    _data[0] /= scalar;
    _data[1] /= scalar;
    _data[2] /= scalar;
    return *this;
}

template<typename T>
template<typename U>
matrix<3,3,T>& matrix<3,3,T>::operator%=(const matrix<3,3,U>& mat)
{
    _data[0] %= mat[0];
    _data[1] %= mat[1];
    _data[2] %= mat[2];
    return *this;
}

template<typename T>
matrix<3,3,T>& matrix<3,3,T>::operator%=(value_type scalar)
{
    _data[0] %= scalar;
    _data[1] %= scalar;
    _data[2] %= scalar;
    return *this;
}

template<typename T>
matrix<3,3,T>& matrix<3,3,T>::operator++()
{
    ++_data[0];
    ++_data[1];
    ++_data[2];
    return *this;
}

template<typename T>
matrix<3,3,T> matrix<3,3,T>::operator++(int)
{
    matrix<3,3,T> cpy{ *this };
    _data[0]++;
    _data[1]++;
    _data[2]++;
    return cpy;
}

template<typename T>
matrix<3,3,T>& matrix<3,3,T>::operator--()
{
    --_data[0];
    --_data[1];
    --_data[2];
    return *this;
}

template<typename T>
matrix<3,3,T> matrix<3,3,T>::operator--(int)
{
    matrix<3,3,T> cpy{ *this };
    _data[0]++;
    _data[1]++;
    _data[2]++;
    return cpy;
}
