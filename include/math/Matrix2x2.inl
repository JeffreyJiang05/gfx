#include "Matrix.hpp"

// CONSTRUCTORS
template<typename T>
constexpr matrix<2,2,T>::matrix() : _data{ vec<2,T>{ 1, 0 }, vec<2,T>{ 0, 1 } } {}

template<typename T>
constexpr matrix<2,2,T>::matrix(value_type fill) : _data{ vec<2,T>{ fill, fill }, vec<2,T>{ fill, fill } } {}

template<typename T>
constexpr matrix<2,2,T>::matrix(vec<2,T> c0, vec<2,T> c1) : _data{ c0, c1 } {}

template<typename T>
template<typename U>
matrix<2,2,T>::matrix(const matrix<2,2,U>& cpy) : _data{ static_cast<vec<2,T>>(cpy[0]), static_cast<vec<2,T>>(cpy[1]) } {}

// ACCESSORS + MODIFIERS
template<typename T>
auto matrix<2,2,T>::operator[](unsigned idx) -> col_type& 
{
    return _data[idx];
}

template<typename T>
constexpr auto matrix<2,2,T>::operator[](unsigned idx) const -> const col_type&
{
    return _data[idx];
}

template<typename T>
auto matrix<2,2,T>::at(unsigned idx) -> col_type&
{
    if (idx >= 2) throw std::out_of_range{ "Index " + std::to_string(idx) + " out of range for mat2x2." };
    return _data[idx];
}

template<typename T>
constexpr auto matrix<2,2,T>::at(unsigned idx) const -> const col_type&
{
    if (idx >= 2) throw std::out_of_range{ "Index " + std::to_string(idx) + " out of range for mat2x2." };
    return _data[idx];
}

// ASSIGNMENT
template<typename T>
template<typename U>
auto matrix<2,2,T>::operator=(const matrix<2,2,U>& cpy) -> matrix&
{
    _data[0] = static_cast<vec<2,T>>(cpy[0]);
    _data[1] = static_cast<vec<2,T>>(cpy[1]);
    return *this;
}

// OPERATORS
template<typename T>
template<typename U>
matrix<2,2,T>& matrix<2,2,T>::operator+=(const matrix<2,2,U>& mat)
{
    _data[0] += mat[0];
    _data[1] += mat[1];
    return *this;
}

template<typename T>
matrix<2,2,T>& matrix<2,2,T>::operator+=(value_type scalar)
{
    _data[0] += scalar;
    _data[1] += scalar;
    return *this;
}

template<typename T>
template<typename U>
matrix<2,2,T>& matrix<2,2,T>::operator-=(const matrix<2,2,U>& mat)
{
    _data[0] -= mat[0];
    _data[1] -= mat[1];
    return *this;
}

template<typename T>
matrix<2,2,T>& matrix<2,2,T>::operator-=(value_type scalar)
{
    _data[0] -= scalar;
    _data[1] -= scalar;
    return *this;
}

template<typename T>
template<typename U>
matrix<2,2,T>& matrix<2,2,T>::operator*=(const matrix<2,2,U>& mat)
{
    _data[0] *= mat[0];
    _data[1] *= mat[1];
    return *this;
}

template<typename T>
matrix<2,2,T>& matrix<2,2,T>::operator*=(value_type scalar)
{
    _data[0] *= scalar;
    _data[1] *= scalar;
    return *this;
}

template<typename T>
template<typename U>
matrix<2,2,T>& matrix<2,2,T>::operator/=(const matrix<2,2,U>& mat)
{
    _data[0] /= mat[0];
    _data[1] /= mat[1];
    return *this;
}

template<typename T>
matrix<2,2,T>& matrix<2,2,T>::operator/=(value_type scalar)
{
    _data[0] /= scalar;
    _data[1] /= scalar;
    return *this;
}

template<typename T>
template<typename U>
matrix<2,2,T>& matrix<2,2,T>::operator%=(const matrix<2,2,U>& mat)
{
    _data[0] %= mat[0];
    _data[1] %= mat[1];
    return *this;
}

template<typename T>
matrix<2,2,T>& matrix<2,2,T>::operator%=(value_type scalar)
{
    _data[0] %= scalar;
    _data[1] %= scalar;
    return *this;
}

template<typename T>
matrix<2,2,T>& matrix<2,2,T>::operator++()
{
    ++_data[0];
    ++_data[1];
    return *this;
}

template<typename T>
matrix<2,2,T> matrix<2,2,T>::operator++(int)
{
    matrix<2,2,T> cpy{ *this };
    _data[0]++;
    _data[1]++;
    return cpy;
}

template<typename T>
matrix<2,2,T>& matrix<2,2,T>::operator--()
{
    --_data[0];
    --_data[1];
    return *this;
}

template<typename T>
matrix<2,2,T> matrix<2,2,T>::operator--(int)
{
    matrix<2,2,T> cpy{ *this };
    _data[0]++;
    _data[1]++;
    return cpy;
}
