#include "Vec.hpp"

#include <cmath>

// COMPARISON OPERATORS
template<unsigned N, typename T, typename U>
bool operator==(const vec<N,T>& a, const vec<N,U>& b)
{
    for (unsigned i = 0; i < N; ++i)
    {
        if (a[i] != b[i]) return false;
    }
    return true;
}

template<unsigned N, typename T, typename U>
bool operator!=(const vec<N,T>& a, const vec<N,U>& b)
{
    for (unsigned i = 0; i < N; ++i)
    {
        if (a[i] /= b[i]) return true;
    }
    return false;
}

// BASIC PAIRWISE ARITHMETIC OPERATORS
template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator+(const vec<N,T>& a, const vec<N,U>& b)
{
    using common_vec = vec<N,std::common_type_t<T,U>>;
    common_vec res{};
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = a[i] + b[i];
    }
    return res;
}

template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator-(const vec<N,T>& a, const vec<N,U>& b)
{
    using common_vec = vec<N,std::common_type_t<T,U>>;
    common_vec res{};
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = a[i] - b[i];
    }
    return res;
}

template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator*(const vec<N,T>& a, const vec<N,U>& b)
{
    using common_vec = vec<N,std::common_type_t<T,U>>;
    common_vec res{};
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = a[i] * b[i];
    }
    return res;
}

template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator/(const vec<N,T>& a, const vec<N,U>& b)
{
    using common_vec = vec<N,std::common_type_t<T,U>>;
    common_vec res{};
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = a[i] / b[i];
    }
    return res;
}

// VECTOR-SCALAR OPERATIONS
template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator+(const vec<N,T>& a, U k)
{
    using common_vec = vec<N,std::common_type_t<T,U>>;
    common_vec res{};
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = a[i] + k;
    }
    return res;
}

template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator-(const vec<N,T>& a, U k)
{
    using common_vec = vec<N,std::common_type_t<T,U>>;
    common_vec res{};
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = a[i] - k;
    }
    return res;
}

template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator*(const vec<N,T>& a, U k)
{
    using common_vec = vec<N,std::common_type_t<T,U>>;
    common_vec res{};
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = a[i] * k;
    }
    return res;
}

template<unsigned N, typename T, typename U>
vec<N,std::common_type_t<T,U>> operator/(const vec<N,T>& a, U k)
{
    using common_vec = vec<N,std::common_type_t<T,U>>;
    common_vec res{};
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = a[i] / k;
    }
    return res;
}

template<unsigned N, typename U, typename T>
vec<N,std::common_type_t<U,T>> operator+(U k, const vec<N,T>& a)
{
    using common_vec = vec<N,std::common_type_t<U,T>>;
    common_vec res{};
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = k + a[i];
    }
    return res;
}

template<unsigned N, typename U, typename T>
vec<N,std::common_type_t<U,T>> operator-(U k, const vec<N,T>& a)
{
    using common_vec = vec<N,std::common_type_t<U,T>>;
    common_vec res{};
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = k - a[i];
    }
    return res;
}

template<unsigned N, typename U, typename T>
vec<N,std::common_type_t<U,T>> operator*(U k, const vec<N,T>& a)
{
    using common_vec = vec<N,std::common_type_t<U,T>>;
    common_vec res{};
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = k * a[i];
    }
    return res;
}

template<unsigned N, typename U, typename T>
vec<N,std::common_type_t<U,T>> operator/(U k, const vec<N,T>& a)
{
    using common_vec = vec<N,std::common_type_t<U,T>>;
    common_vec res{};
    for (unsigned i = 0; i < N; ++i)
    {
        res[i] = k / a[i];
    }
    return res;
}

// VECTOR OPERATIONS
template<typename T>
vec<3,T> cross(const vec<3,T>& a, const vec<3,T>& b)
{
    return vec<3,T>{ 
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0]
    };
}

template<unsigned N,typename T>
T dot(const vec<N,T>& a, const vec<N,T>& b)
{
    T sum{};
    for (unsigned i = 0; i < N; ++i)
    {
        sum += a[i] * b[i];
    }
    return sum;
}

template<unsigned N, typename T>
double magnitude(const vec<N,T>& a)
{
    T sum{};
    for (unsigned i = 0; i < N; ++i)
    {
        sum += a[i] * a[i];
    }
    return sqrt(sum);
}

template<unsigned N, typename T>
vec<N,double> normalize(const vec<N,T>& a)
{
    return magnitude(a) * a;
}

// OUT STREAM FORMATTING
template<unsigned N, typename T>
std::ostream& operator<<(std::ostream& out, const vec<N, T>& vec)
{
    out << "(";
    for (unsigned i = 0; i < N; ++i)
    {
        out << vec[i];
        if (i < N-1) out << ",";
    }
    return out << ")";
}