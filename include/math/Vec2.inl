#include "Vec.hpp"

// default constructible
template<typename T>
vec<2, T>::vec() : _data{} {}

// initialize data explicitly
template<typename T>
vec<2, T>::vec(value_type x, value_type y) : _data{ x, y } {}

// copy constructible from castible type
template<typename T>
template<typename U>
vec<2, T>::vec(const vec<2,U>& cpy) : _data{ static_cast<T>(cpy[0]), static_cast<T>(cpy[1]) } {}

// initialize data of convertible type
template<typename T>
template<typename T0, typename T1>
vec<2, T>::vec(T0 x, T1 y) : _data{ static_cast<T>(x), static_cast<T>(y) } {}

// access through subscript operator. no bounds checking
template<typename T>
auto vec<2, T>::operator[](unsigned idx) -> value_type&
{
    return _data[idx];
}

template<typename T>
auto vec<2, T>::operator[](unsigned idx) const -> const value_type&
{
    return _data[idx];
}

// access through method. bounds checked. throws index out of range
template<typename T>
auto vec<2, T>::at(unsigned idx) -> value_type&
{
    if (idx >= 2) throw std::out_of_range{ "Index " + std::to_string(idx) + " out of range for vec2." };
    return _data[idx];
}

template<typename T>
auto vec<2, T>::at(unsigned idx) const -> const value_type&
{
    if (idx >= 2) throw std::out_of_range{ "Index " + std::to_string(idx) + " out of range for vec2." };
    return _data[idx];
}

// access elements through common name. returns by value
template<typename T>
auto vec<2,T>::x() const -> value_type
{
    return _data[0];
}

template<typename T>
auto vec<2,T>::y() const -> value_type
{
    return _data[1];
}

// OPERATORS
template<typename T>
template<typename U>
vec<2,T>& vec<2,T>::operator=(const vec<2,U>& cpy)
{
    _data[0] = static_cast<T>(cpy[0]);
    _data[1] = static_cast<T>(cpy[1]);
    return *this;
}

template<typename T>
template<typename U>
vec<2,T>& vec<2,T>::operator+=(const vec<2,U>& vector)
{
    _data[0] += static_cast<T>(vector[0]);  
    _data[1] += static_cast<T>(vector[1]);
    return *this;  
}

template<typename T>
vec<2,T>& vec<2,T>::operator+=(value_type scalar)
{
    _data[0] += scalar;
    _data[1] += scalar;
    return *this;
}


template<typename T>
template<typename U>
vec<2,T>& vec<2,T>::operator-=(const vec<2,U>& vector)
{
    _data[0] -= static_cast<T>(vector[0]);  
    _data[1] -= static_cast<T>(vector[1]);
    return *this;  
}

template<typename T>
vec<2,T>& vec<2,T>::operator-=(value_type scalar)
{
    _data[0] -= scalar;
    _data[1] -= scalar;
    return *this;
}


template<typename T>
template<typename U>
vec<2,T>& vec<2,T>::operator*=(const vec<2,U>& vector)
{
    _data[0] *= static_cast<T>(vector._data[0]);  
    _data[1] *= static_cast<T>(vector._data[1]);
    return *this;  
}

template<typename T>
vec<2,T>& vec<2,T>::operator*=(value_type scalar)
{
    _data[0] *= scalar;
    _data[1] *= scalar;
    return *this;
}


template<typename T>
template<typename U>
vec<2,T>& vec<2,T>::operator/=(const vec<2,U>& vector)
{
    _data[0] /= static_cast<T>(vector._data[0]);  
    _data[1] /= static_cast<T>(vector._data[1]);
    return *this;  
}

template<typename T>
vec<2,T>& vec<2,T>::operator/=(value_type scalar)
{
    _data[0] /= scalar;
    _data[1] /= scalar;
    return *this;
}

// UNARY INC-DEC OPS
template<typename T>
vec<2,T>& vec<2,T>::operator++()
{
    ++_data[0];
    ++_data[1];
    return *this;
}

template<typename T>
vec<2,T> vec<2,T>::operator++(int)
{
    vec<2,T> orig{ *this };
    _data[0]++;
    _data[1]++;
    return orig;
}

template<typename T>
vec<2,T>& vec<2,T>::operator--()
{
    --_data[0];
    --_data[1];
    return *this;
}

template<typename T>
vec<2,T> vec<2,T>::operator--(int)
{
    vec<2,T> orig{ *this };
    _data[0]--;
    _data[1]--;
    return orig;
}
