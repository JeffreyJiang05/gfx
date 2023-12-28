#include "Matrix.hpp"

// BINARY OPERATIONS
template<unsigned Dim, typename T, typename U>
matrix<Dim,Dim,RESULT(T,U,+)> operator+(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2)
{
    using result_t = RESULT(T,U,+);
    matrix<Dim,Dim,result_t> res{ 0 };
    for (unsigned i = 0; i < Dim; ++i)
    {
        res[i] = static_cast<vec<Dim,result_t>>(m1[i] + m2[i]);
    }
    return res;
}

template<unsigned Dim, typename T, typename U>
matrix<Dim,Dim,RESULT(T,U,-)> operator-(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2)
{
    using result_t = RESULT(T,U,-);
    matrix<Dim,Dim,result_t> res{ 0 };
    for (unsigned i = 0; i < Dim; ++i)
    {
        res[i] = static_cast<vec<Dim,result_t>>(m1[i] - m2[i]);
    }
    return res;
}

template<typename T, typename U>
matrix<2,2,RESULT(T,U,*)> operator*(const matrix<2,2,T>& m1, const matrix<2,2,U>& m2)
{
    using result_t = RESULT(T,U,*);
    return matrix<2,2,result_t>{ 
        vec<2,result_t>{ (m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1]), (m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1]) },
        vec<2,result_t>{ (m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1]), (m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1]) } 
    };
}

template<typename T, typename U>
matrix<3,3,RESULT(T,U,*)> operator*(const matrix<3,3,T>& m1, const matrix<3,3,U>& m2)
{
    using result_t = RESULT(T,U,*);
    return matrix<3,3,result_t>{
        vec<3,result_t>{ 
            (m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2]),
            (m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2]),
            (m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2])
        },
        vec<3,result_t>{ 
            (m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2]),
            (m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2]),
            (m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2])
        },
        vec<3,result_t>{ 
            (m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2]),
            (m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2]),
            (m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2])
        }
    };
}

template<typename T, typename U>
matrix<4,4,RESULT(T,U,*)> operator*(const matrix<4,4,T>& m1, const matrix<4,4,U>& m2)
{
    using result_t = RESULT(T,U,*);
    return matrix<4,4,result_t>{
        vec<4,result_t>{
            (m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] * m1[3][0] * m2[0][3]),
            (m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] * m1[3][1] * m2[0][3]),
            (m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] * m1[3][2] * m2[0][3]),
            (m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] * m1[3][3] * m2[0][3])
        },
        vec<4,result_t>{
            (m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] * m1[3][0] * m2[1][3]),
            (m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] * m1[3][1] * m2[1][3]),
            (m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] * m1[3][2] * m2[1][3]),
            (m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] * m1[3][3] * m2[1][3])
        },
        vec<4,result_t>{
            (m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] * m1[3][0] * m2[2][3]),
            (m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] * m1[3][1] * m2[2][3]),
            (m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] * m1[3][2] * m2[2][3]),
            (m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2] * m1[3][3] * m2[2][3])
        },
        vec<4,result_t>{
            (m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2] * m1[3][0] * m2[3][3]),
            (m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2] * m1[3][1] * m2[3][3]),
            (m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1] + m1[2][2] * m2[3][2] * m1[3][2] * m2[3][3]),
            (m1[0][3] * m2[3][0] + m1[1][3] * m2[3][1] + m1[2][3] * m2[3][2] * m1[3][3] * m2[3][3])
        }
    };
}

template<typename T, typename U>
vec<2,RESULT(T,U,*)> operator*(const matrix<2,2,T>& m, const vec<2,U>& v)
{
    using result_t = RESULT(T,U,*);
    return vec<2,result_t>{
        m[0][0] * v[0] + m[1][0] * v[1],
        m[0][1] * v[0] + m[1][1] * v[1]
    };
}

template<typename T, typename U>
vec<3,RESULT(T,U,*)> operator*(const matrix<3,3,T>& m, const vec<3,U>& v)
{
    using result_t = RESULT(T,U,*);
    return vec<3,result_t>{
        m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2],
        m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2],
        m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2]
    };
}

template<typename T, typename U>
vec<4,RESULT(T,U,*)> operator*(const matrix<4,4,T>& m, const vec<4,U>& v)
{
    using result_t = RESULT(T,U,*);
    return vec<4,result_t>{
        m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
        m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
        m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
        m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]
    };
}

// BASIC MATRIX OPERATIONS
template<typename T>
matrix<2,2,T> transpose(const matrix<2,2,T>& m)
{
    return matrix<2,2,T>{
        vec<2,T>{ m[0][0], m[1][0] },
        vec<2,T>{ m[0][1], m[1][1] }
    };
}

template<typename T>
matrix<3,3,T> transpose(const matrix<3,3,T>& m)
{
    return matrix<3,3,T>{
        vec<3,T>{ m[0][0], m[1][0], m[2][0] },
        vec<3,T>{ m[0][1], m[1][1], m[2][1] },
        vec<3,T>{ m[0][2], m[1][2], m[2][2] }
    };
}

template<typename T>
matrix<4,4,T> transpose(const matrix<4,4,T>& m)
{
    return matrix<4,4,T>{
        vec<4,T>{ m[0][0], m[1][0], m[2][0], m[3][0] },
        vec<4,T>{ m[0][1], m[1][1], m[2][1], m[3][1] },
        vec<4,T>{ m[0][2], m[1][2], m[2][2], m[3][2] },
        vec<4,T>{ m[0][3], m[1][3], m[2][3], m[3][3] }
    };
}

template<typename T>
T determinant(const matrix<2,2,T>& m)
{
    return static_cast<T>(m[0][0] * m[1][1] - m[0][1] * m[1][0]);
}

template<typename T>
T determinant(const matrix<3,3,T>& m)
{
    return static_cast<T>(
        m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
        m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]) +
        m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1])
    );
}

template<typename T>
T determinant(const matrix<4,4,T>& m)
{
    // required det(2x2) submatrices of m
    T det_22_33 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
	T det_21_33 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
	T det_21_32 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
	T det_20_33 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
	T det_20_32 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
	T det_20_31 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

    // required det(3x3) submatrices of m
    T det3x3_0 = m[1][1] * det_22_33 - m[1][2] * det_21_33 + m[1][3] * det_21_32;
    T det3x3_1 = m[1][0] * det_22_33 - m[1][2] * det_20_33 + m[1][3] * det_20_32;
    T det3x3_2 = m[1][0] * det_21_33 - m[1][1] * det_20_33 + m[1][3] * det_20_31;
    T det3x3_3 = m[1][0] * det_21_32 - m[1][1] * det_20_32 + m[1][2] * det_20_31;

    return static_cast<T>(
        m[0][0] * det3x3_0 - m[0][1] * det3x3_1 + m[0][2] * det3x3_2 - m[0][3] * det3x3_3
    );
}

template<typename T>
matrix<2,2,T> inverse(const matrix<2,2,T>& m)
{
    matrix<2,2,T> inverse{ 
        vec<2,T>{ m[1][1], -m[0][1] }, 
        vec<2,T>{ -m[1][0], m[0][0] } 
    };
    T recipDet = 1 / (m[1][1] * m[0][0] - m[1][0] * m[0][1]);
    return recipDet * inverse;
}

// TODO: IMPLEMENT inverse(mat<3,3>), inverse(mat<4,4>)

// STREAM OPERATOR
template<unsigned Col, unsigned Row, typename T>
std::ostream& operator<<(std::ostream& out, const matrix<Col,Row,T>& mat)
{
    out << "[";
    for (unsigned i = 0; i < Col; ++i)
    {
        out << mat[i];
        if (i != Col-1) out << ",";
    }
    return out << "]";
}