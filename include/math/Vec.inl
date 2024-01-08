#include "Vec.hpp"

#include <cmath>

// COMPARISON OPERATORS
template<unsigned N, typename T, typename U>
constexpr bool operator==(const vec<N,T>& a, const vec<N,U>& b)
{
    for (unsigned i = 0; i < N; ++i)
    {
        if (a[i] != b[i]) return false;
    }
    return true;
}

template<unsigned N, typename T, typename U>
constexpr bool operator!=(const vec<N,T>& a, const vec<N,U>& b)
{
    for (unsigned i = 0; i < N; ++i)
    {
        if (a[i] != b[i]) return true;
    }
    return false;
}

// BASIC PAIRWISE ARITHMETIC OPERATORS

namespace _details
{
    template<unsigned N, typename T, typename U>
    using common_vec = vec<N,std::common_type_t<T,U>>;

    template<unsigned N>
    struct vec_op;

    template<>
    struct vec_op<2>
    {
        template<typename T, typename U>
        static constexpr common_vec<2, T, U> pairwise_add(const vec<2,T>& a, const vec<2,U>& b)
        {
            return common_vec<2, T, U>{ 
                a[0] + b[0], 
                a[1] + b[1] 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<2, T, U> pairwise_sub(const vec<2,T>& a, const vec<2,U>& b)
        {
            return common_vec<2, T, U>{ 
                a[0] - b[0], 
                a[1] - b[1] 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<2, T, U> pairwise_mult(const vec<2,T>& a, const vec<2,U>& b)
        {
            return common_vec<2, T, U>{ 
                a[0] * b[0], 
                a[1] * b[1] 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<2, T, U> pairwise_div(const vec<2,T>& a, const vec<2,U>& b)
        {
            return common_vec<2, T, U>{ 
                a[0] / b[0], 
                a[1] / b[1] 
            };
        }
    
        template<typename T, typename U>
        static constexpr common_vec<2, T, U> scale_add(const vec<2,T>& a, U b)
        {
            return common_vec<2, T, U>{ 
                a[0] + b, 
                a[1] + b 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<2, T, U> scale_sub(const vec<2,T>& a, U b)
        {
            return common_vec<2, T, U>{ 
                a[0] - b, 
                a[1] - b 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<2, T, U> scale_mult(const vec<2,T>& a, U b)
        {
            return common_vec<2, T, U>{ 
                a[0] * b, 
                a[1] * b 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<2, T, U> scale_div(const vec<2,T>& a, U b)
        {
            return common_vec<2, T, U>{ 
                a[0] / b, 
                a[1] / b 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<2, T, U> scale_add(U b, const vec<2,T>& a)
        {
            return common_vec<2, T, U>{ 
                b + a[0], 
                b + a[1] 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<2, T, U> scale_sub(U b, const vec<2,T>& a)
        {
            return common_vec<2, T, U>{ 
                b - a[0], 
                b - a[1] 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<2, T, U> scale_mult(U b, const vec<2,T>& a)
        {
            return common_vec<2, T, U>{ 
                b * a[0], 
                b * a[1] 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<2, T, U> scale_div(U b, const vec<2,T>& a)
        {
            return common_vec<2, T, U>{ 
                b / a[0], 
                b / a[1] 
            };
        }
    };

    template<>
    struct vec_op<3>
    {
        template<typename T, typename U>
        static constexpr common_vec<3, T, U> pairwise_add(const vec<3,T>& a, const vec<3,U>& b)
        {
            return common_vec<3, T, U>{ 
                a[0] + b[0], 
                a[1] + b[1],
                a[2] + b[2]
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<3, T, U> pairwise_sub(const vec<3,T>& a, const vec<3,U>& b)
        {
            return common_vec<3, T, U>{ 
                a[0] - b[0], 
                a[1] - b[1],
                a[2] - b[2]
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<3, T, U> pairwise_mult(const vec<3,T>& a, const vec<3,U>& b)
        {
            return common_vec<3, T, U>{ 
                a[0] * b[0], 
                a[1] * b[1],
                a[2] * b[2]
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<3, T, U> pairwise_div(const vec<3,T>& a, const vec<3,U>& b)
        {
            return common_vec<3, T, U>{ 
                a[0] / b[0], 
                a[1] / b[1],
                a[2] / b[2]
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<3, T, U> scale_add(const vec<3,T>& a, U b)
        {
            return common_vec<3, T, U>{ 
                a[0] + b, 
                a[1] + b,
                a[2] + b 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<3, T, U> scale_sub(const vec<3,T>& a, U b)
        {
            return common_vec<3, T, U>{ 
                a[0] - b, 
                a[1] - b,
                a[2] - b 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<3, T, U> scale_mult(const vec<3,T>& a, U b)
        {
            return common_vec<3, T, U>{ 
                a[0] * b, 
                a[1] * b,
                a[2] * b 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<3, T, U> scale_div(const vec<3,T>& a, U b)
        {
            return common_vec<3, T, U>{ 
                a[0] / b, 
                a[1] / b,
                a[2] / b 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<3, T, U> scale_add(U b, const vec<3,T>& a)
        {
            return common_vec<3, T, U>{ 
                a[0] + b, 
                a[1] + b,
                a[2] + b 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<3, T, U> scale_sub(U b, const vec<3,T>& a)
        {
            return common_vec<3, T, U>{ 
                b - a[0], 
                b - a[1],
                b - a[2] 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<3, T, U> scale_mult(U b, const vec<3,T>& a)
        {
            return common_vec<3, T, U>{ 
                b * a[0], 
                b * a[1],
                b * a[2] 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<3, T, U> scale_div(U b, const vec<3,T>& a)
        {
            return common_vec<3, T, U>{ 
                b / a[0], 
                b / a[1],
                b / a[2] 
            };
        }
    };

    template<>
    struct vec_op<4>
    {
        template<typename T, typename U>
        static constexpr common_vec<4, T, U> pairwise_add(const vec<4,T>& a, const vec<4,U>& b)
        {
            return common_vec<4, T, U>{ 
                a[0] + b[0], 
                a[1] + b[1],
                a[2] + b[2],
                a[3] + b[3]
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<4, T, U> pairwise_sub(const vec<4,T>& a, const vec<4,U>& b)
        {
            return common_vec<4, T, U>{ 
                a[0] - b[0], 
                a[1] - b[1],
                a[2] - b[2],
                a[3] - b[3]
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<4, T, U> pairwise_mult(const vec<4,T>& a, const vec<4,U>& b)
        {
            return common_vec<4, T, U>{ 
                a[0] * b[0], 
                a[1] * b[1],
                a[2] * b[2],
                a[3] * b[3]
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<4, T, U> pairwise_div(const vec<4,T>& a, const vec<4,U>& b)
        {
            return common_vec<4, T, U>{ 
                a[0] / b[0], 
                a[1] / b[1],
                a[2] / b[2],
                a[3] / b[3]
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<4, T, U> scale_add(const vec<4,T>& a, U b)
        {
            return common_vec<4, T, U>{ 
                a[0] + b, 
                a[1] + b,
                a[2] + b,
                a[3] + b 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<4, T, U> scale_sub(const vec<4,T>& a, U b)
        {
            return common_vec<4, T, U>{ 
                a[0] - b, 
                a[1] - b,
                a[2] - b,
                a[3] - b 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<4, T, U> scale_mult(const vec<4,T>& a, U b)
        {
            return common_vec<4, T, U>{ 
                a[0] * b, 
                a[1] * b,
                a[2] * b,
                a[3] * b 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<4, T, U> scale_div(const vec<4,T>& a, U b)
        {
            return common_vec<4, T, U>{ 
                a[0] / b, 
                a[1] / b,
                a[2] / b,
                a[3] / b 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<4, T, U> scale_add(U b, const vec<4,T>& a)
        {
            return common_vec<4, T, U>{ 
                b + a[0], 
                b + a[1],
                b + a[2],
                b + a[3] 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<4, T, U> scale_sub(U b, const vec<4,T>& a)
        {
            return common_vec<4, T, U>{ 
                b - a[0], 
                b - a[1],
                b - a[2],
                b - a[3] 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<4, T, U> scale_mult(U b, const vec<4,T>& a)
        {
            return common_vec<4, T, U>{ 
                b * a[0], 
                b * a[1],
                b * a[2],
                b * a[3] 
            };
        }

        template<typename T, typename U>
        static constexpr common_vec<4, T, U> scale_div(U b, const vec<4,T>& a)
        {
            return common_vec<4, T, U>{ 
                b / a[0], 
                b / a[1],
                b / a[2],
                b / a[3] 
            };
        }
    };
}

template<unsigned N, typename T, typename U>
constexpr vec<N,std::common_type_t<T,U>> operator+(const vec<N,T>& a, const vec<N,U>& b)
{
    if constexpr(N <= 4)
    {
        return _details::vec_op<N>::pairwise_add(a, b);
    }
    else
    {
        _details::common_vec<N,T,U> res{};
        for (unsigned i = 0; i < N; ++i)
        {
            res[i] = a[i] + b[i];
        }
        return res;
    }
}

template<unsigned N, typename T, typename U>
constexpr vec<N,std::common_type_t<T,U>> operator-(const vec<N,T>& a, const vec<N,U>& b)
{
    if constexpr(N <= 4)
    {
        return _details::vec_op<N>::pairwise_sub(a, b);
    }
    else
    {
        _details::common_vec<N,T,U> res{};
        for (unsigned i = 0; i < N; ++i)
        {
            res[i] = a[i] - b[i];
        }
        return res;
    }
}

template<unsigned N, typename T, typename U>
constexpr vec<N,std::common_type_t<T,U>> operator*(const vec<N,T>& a, const vec<N,U>& b)
{
    if constexpr(N <= 4)
    {
        return _details::vec_op<N>::pairwise_mult(a, b);
    }
    else
    {
        _details::common_vec<N,T,U> res{};
        for (unsigned i = 0; i < N; ++i)
        {
            res[i] = a[i] * b[i];
        }
        return res;
    }
}

template<unsigned N, typename T, typename U>
constexpr vec<N,std::common_type_t<T,U>> operator/(const vec<N,T>& a, const vec<N,U>& b)
{
    if constexpr(N <= 4)
    {
        return _details::vec_op<N>::pairwise_div(a, b);
    }
    else
    {
        _details::common_vec<N,T,U> res{};
        for (unsigned i = 0; i < N; ++i)
        {
            res[i] = a[i] / b[i];
        }
        return res;
    }
}

// VECTOR-SCALAR OPERATIONS
template<unsigned N, typename T, typename U>
constexpr vec<N,std::common_type_t<T,U>> operator+(const vec<N,T>& a, U k)
{
    if constexpr(N <= 4)
    {
        return _details::vec_op<N>::scale_add(a, k);
    }
    else
    {
        _details::common_vec<N, T, U> res{};
        for (unsigned i = 0; i < N; ++i)
        {
            res[i] = a[i] + k;
        }
        return res;
    }
}

template<unsigned N, typename T, typename U>
constexpr vec<N,std::common_type_t<T,U>> operator-(const vec<N,T>& a, U k)
{
    if constexpr(N <= 4)
    {
        return _details::vec_op<N>::scale_sub(a, k);
    }
    else
    {
        _details::common_vec<N, T, U> res{};
        for (unsigned i = 0; i < N; ++i)
        {
            res[i] = a[i] - k;
        }
        return res;
    }
}

template<unsigned N, typename T, typename U>
constexpr vec<N,std::common_type_t<T,U>> operator*(const vec<N,T>& a, U k)
{
    if constexpr(N <= 4)
    {
        return _details::vec_op<N>::scale_mult(a, k);
    }
    else
    {
        _details::common_vec<N, T, U> res{};
        for (unsigned i = 0; i < N; ++i)
        {
            res[i] = a[i] * k;
        }
        return res;
    }
}

template<unsigned N, typename T, typename U>
constexpr vec<N,std::common_type_t<T,U>> operator/(const vec<N,T>& a, U k)
{
    if constexpr(N <= 4)
    {
        return _details::vec_op<N>::scale_div(a, k);
    }
    else
    {
        _details::common_vec<N, T, U> res{};
        for (unsigned i = 0; i < N; ++i)
        {
            res[i] = a[i] / k;
        }
        return res;
    }
}

template<unsigned N, typename U, typename T>
constexpr vec<N,std::common_type_t<U,T>> operator+(U k, const vec<N,T>& a)
{
    if constexpr(N <= 4)
    {
        return _details::vec_op<N>::scale_add(k, a);
    }
    else
    {
        _details::common_vec<N, T, U> res{};
        for (unsigned i = 0; i < N; ++i)
        {
            res[i] = k + a[i];
        }
        return res;
    }
}

template<unsigned N, typename U, typename T>
constexpr vec<N,std::common_type_t<U,T>> operator-(U k, const vec<N,T>& a)
{
    if constexpr(N <= 4)
    {
        return _details::vec_op<N>::scale_sub(k, a);
    }
    else
    {
        _details::common_vec<N, T, U> res{};
        for (unsigned i = 0; i < N; ++i)
        {
            res[i] = k - a[i];
        }
        return res;
    }
}

template<unsigned N, typename U, typename T>
constexpr vec<N,std::common_type_t<U,T>> operator*(U k, const vec<N,T>& a)
{
    if constexpr(N <= 4)
    {
        return _details::vec_op<N>::scale_mult(k, a);
    }
    else
    {
        _details::common_vec<N, T, U> res{};
        for (unsigned i = 0; i < N; ++i)
        {
            res[i] = k * a[i];
        }
        return res;
    }
}

template<unsigned N, typename U, typename T>
constexpr vec<N,std::common_type_t<U,T>> operator/(U k, const vec<N,T>& a)
{
    if constexpr(N <= 4)
    {
        return _details::vec_op<N>::scale_div(k, a);
    }
    else
    {
        _details::common_vec<N, T, U> res{};
        for (unsigned i = 0; i < N; ++i)
        {
            res[i] = k / a[i];
        }
        return res;
    }
}

// VECTOR OPERATIONS
template<typename T>
constexpr vec<3,T> cross(const vec<3,T>& a, const vec<3,T>& b)
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