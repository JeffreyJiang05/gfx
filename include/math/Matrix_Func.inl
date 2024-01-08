#include "Matrix.hpp"

namespace _details
{

    template<unsigned N>
    struct mat_ops;

    template<>
    struct mat_ops<2>
    {
        static constexpr unsigned Dim = 2;

        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,+)> add(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2)
        {
            return matrix<Dim,Dim,RESULT(T,U,+)>{
                m1[0] + m2[0],
                m1[1] + m2[1]
            };
        }

        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,-)> sub(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2)
        {
            return matrix<Dim,Dim,RESULT(T,U,-)>{
                m1[0] - m2[0],
                m1[1] - m2[1]
            };
        }

        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,*)> prod(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2)
        {
            using result_t = RESULT(T,U,*);
            return matrix<Dim,Dim,result_t>{ 
                vec<Dim,result_t>{ (m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1]), (m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1]) },
                vec<Dim,result_t>{ (m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1]), (m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1]) } 
            };
        }

        template<typename T, typename U>
        constexpr static vec<Dim,RESULT(T,U,*)> vec_prod(const matrix<Dim,Dim,T>& m, const vec<Dim,U>& v)
        {
            using result_t = RESULT(T,U,*);
            return vec<Dim,result_t>{
                m[0][0] * v[0] + m[1][0] * v[1],
                m[0][1] * v[0] + m[1][1] * v[1]
            };
        }

        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,*)> scale_mult(const matrix<Dim,Dim,T>& m, U val)
        {
            return matrix<Dim,Dim,RESULT(T,U,*)>{
                m[0] * val,
                m[1] * val
            };
        }

        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,/)> scale_div(const matrix<Dim,Dim,T>& m, U val)
        {
            return matrix<Dim,Dim,RESULT(T,U,/)>{
                m[0] / val,
                m[1] / val
            };
        }

        template<typename T>
        constexpr static T det(const matrix<Dim,Dim,T>& m)
        {
            return static_cast<T>(m[0][0] * m[1][1] - m[0][1] * m[1][0]);
        }

        template<typename T>
        constexpr static matrix<Dim,Dim,T> transpose(const matrix<Dim,Dim,T>& m)
        {
            return matrix<Dim,Dim,T>{
                vec<Dim,T>{ m[0][0], m[1][0] },
                vec<Dim,T>{ m[0][1], m[1][1] }
            };
        }

        template<typename T>
        static constexpr matrix<Dim,Dim,T> inv(const matrix<Dim,Dim,T>& m)
        {
            matrix<Dim,Dim,T> inverse{ 
                vec<Dim,T>{ m[1][1], -m[0][1] }, 
                vec<Dim,T>{ -m[1][0], m[0][0] } 
            };
            T recipDet = 1 / (m[1][1] * m[0][0] - m[1][0] * m[0][1]);
            return recipDet * inverse;
        }

    };

    template<>
    struct mat_ops<3>
    {

        static constexpr unsigned Dim = 3;

        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,+)> add(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2)
        {
            return matrix<Dim,Dim,RESULT(T,U,+)>{
                m1[0] + m2[0],
                m1[1] + m2[1],
                m1[2] + m2[2]
            };
        }   
        
        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,-)> sub(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2)
        {
            return matrix<Dim,Dim,RESULT(T,U,-)>{
                m1[0] - m2[0],
                m1[1] - m2[1],
                m1[2] - m2[2]
            };
        }   

        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,*)> prod(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2)
        {
            using result_t = RESULT(T,U,*);
            return matrix<Dim,Dim,result_t>{
                vec<Dim,result_t>{ 
                    (m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2]),
                    (m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2]),
                    (m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2])
                },
                vec<Dim,result_t>{ 
                    (m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2]),
                    (m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2]),
                    (m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2])
                },
                vec<Dim,result_t>{ 
                    (m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2]),
                    (m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2]),
                    (m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2])
                }
            };
        }

        template<typename T, typename U>
        constexpr static vec<Dim,RESULT(T,U,*)> vec_prod(const matrix<Dim,Dim,T>& m, const vec<Dim,U>& v)
        {
            using result_t = RESULT(T,U,*);
            return vec<Dim,result_t>{
                m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2],
                m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2],
                m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2]
            };
        }

        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,*)> scale_mult(const matrix<Dim,Dim,T>& m, U val)
        {
            return matrix<Dim,Dim,RESULT(T,U,*)>{
                m[0] * val,
                m[1] * val,
                m[2] * val
            };
        }

        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,/)> scale_div(const matrix<Dim,Dim,T>& m, U val)
        {
            return matrix<Dim,Dim,RESULT(T,U,/)>{
                m[0] / val,
                m[1] / val,
                m[2] / val
            };
        }

        template<typename T>
        constexpr static T det(const matrix<Dim,Dim,T>& m)
        {
            return static_cast<T>(
                m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
                m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]) +
                m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1])
            );
        }

        template<typename T>
        constexpr static matrix<Dim,Dim,T> transpose(const matrix<Dim,Dim,T>& m)
        {
            return matrix<Dim,Dim,T>{
                vec<Dim,T>{ m[0][0], m[1][0], m[2][0] },
                vec<Dim,T>{ m[0][1], m[1][1], m[2][1] },
                vec<Dim,T>{ m[0][2], m[1][2], m[2][2] }
            };
        }

        template<typename T>
        static constexpr matrix<Dim,Dim,T> inv(const matrix<Dim,Dim,T>& m)
        {
            T cf_00, cf_01, cf_02, cf_10, cf_11, cf_12, cf_20, cf_21, cf_22, inv_det;

            cf_00 =  (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
            cf_01 = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]);
            cf_02 =  (m[1][0] * m[2][1] - m[2][0] * m[1][1]);

            cf_10 = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]);
            cf_11 =  (m[0][0] * m[2][2] - m[2][0] * m[0][2]);
            cf_12 = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]);

            cf_20 =  (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
            cf_21 = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]);
            cf_22 =  (m[0][0] * m[1][1] - m[1][0] * m[0][1]);

            inv_det = 1 / (m[0][0] * cf_00 + m[1][0] * cf_10 + m[2][0] * cf_20);

            matrix<Dim,Dim,T> inv{
                vec<Dim,T>{ cf_00, cf_10, cf_20 },
                vec<Dim,T>{ cf_01, cf_11, cf_21 },
                vec<Dim,T>{ cf_02, cf_12, cf_22 }
            };

            return inv * inv_det;
        }

    };

    template<>
    struct mat_ops<4>
    {

        static constexpr unsigned Dim = 4;

        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,+)> add(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2)
        {
            return matrix<Dim,Dim,RESULT(T,U,+)>{
                m1[0] + m2[0],
                m1[1] + m2[1],
                m1[2] + m2[2],
                m1[3] + m2[3]
            };
        }

        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,-)> sub(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2)
        {
            return matrix<Dim,Dim,RESULT(T,U,-)>{
                m1[0] - m2[0],
                m1[1] - m2[1],
                m1[2] - m2[2],
                m1[3] - m2[3]
            };
        }

        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,*)> prod(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2)
        {
            using result_t = RESULT(T,U,*);
            return matrix<Dim,Dim,result_t>{
                vec<Dim,result_t>{
                    (m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3]),
                    (m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3]),
                    (m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3]),
                    (m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3])
                },
                vec<4,result_t>{
                    (m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3]),
                    (m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3]),
                    (m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3]),
                    (m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3])
                },
                vec<4,result_t>{
                    (m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3]),
                    (m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3]),
                    (m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] + m1[3][2] * m2[2][3]),
                    (m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2] + m1[3][3] * m2[2][3])
                },
                vec<4,result_t>{
                    (m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2] + m1[3][0] * m2[3][3]),
                    (m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2] + m1[3][1] * m2[3][3]),
                    (m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1] + m1[2][2] * m2[3][2] + m1[3][2] * m2[3][3]),
                    (m1[0][3] * m2[3][0] + m1[1][3] * m2[3][1] + m1[2][3] * m2[3][2] + m1[3][3] * m2[3][3])
                }
            };
        }

        template<typename T, typename U>
        constexpr static vec<Dim,RESULT(T,U,*)> vec_prod(const matrix<Dim,Dim,T>& m, const vec<Dim,U>& v)
        {
            using result_t = RESULT(T,U,*);
            return vec<Dim,result_t>{
                m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
                m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
                m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
                m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]
            };
        }

        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,*)> scale_mult(const matrix<Dim,Dim,T>& m, U val)
        {
            return matrix<Dim,Dim,RESULT(T,U,*)>{
                m[0] * val,
                m[1] * val,
                m[2] * val,
                m[3] * val
            };
        }

        template<typename T, typename U>
        constexpr static matrix<Dim,Dim,RESULT(T,U,/)> scale_div(const matrix<Dim,Dim,T>& m, U val)
        {
            return matrix<Dim,Dim,RESULT(T,U,/)>{
                m[0] / val,
                m[1] / val,
                m[2] / val,
                m[3] / val
            };
        }

        template<typename T>
        constexpr static T det(const matrix<Dim,Dim,T>& m)
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
        constexpr static matrix<Dim,Dim,T> transpose(const matrix<Dim,Dim,T>& m)
        {
            return matrix<Dim,Dim,T>{
                vec<Dim,T>{ m[0][0], m[1][0], m[2][0], m[3][0] },
                vec<Dim,T>{ m[0][1], m[1][1], m[2][1], m[3][1] },
                vec<Dim,T>{ m[0][2], m[1][2], m[2][2], m[3][2] },
                vec<Dim,T>{ m[0][3], m[1][3], m[2][3], m[3][3] }
            };
        }

        template<typename T>
        static constexpr matrix<Dim,Dim,T> inv(const matrix<Dim,Dim,T>& m)
        {
            T cf_00, cf_01, cf_02, cf_03;
            T cf_10, cf_11, cf_12, cf_13;
            T cf_20, cf_21, cf_22, cf_23;
            T cf_30, cf_31, cf_32, cf_33;
            T inv_det;

            cf_00 = +( 
                  m[1][1] * (m[2][2] * m[3][3] - m[3][2] * m[2][3]) 
                - m[1][2] * (m[2][1] * m[3][3] - m[3][1] * m[2][3])
                + m[1][3] * (m[2][1] * m[3][2] - m[3][1] * m[2][2])
            );
            cf_01 = -(
                  m[1][0] * (m[2][2] * m[3][3] - m[3][2] * m[2][3])
                - m[1][2] * (m[2][0] * m[3][3] - m[3][0] * m[2][3])
                + m[1][3] * (m[2][0] * m[3][2] - m[3][0] * m[2][2])
            );
            cf_02 = +(
                  m[1][0] * (m[2][1] * m[3][3] - m[3][1] * m[2][3])
                - m[1][1] * (m[2][0] * m[3][3] - m[3][0] * m[2][3])
                + m[1][3] * (m[2][0] * m[3][1] - m[3][0] * m[2][1])
            );
            cf_03 = -(
                  m[1][0] * (m[2][1] * m[3][2] - m[3][1] * m[2][2])
                - m[1][1] * (m[2][0] * m[3][2] - m[3][0] * m[2][2])
                + m[1][2] * (m[2][0] * m[3][1] - m[3][0] * m[2][1])
            );
            cf_10 = -(
                  m[0][1] * (m[2][2] * m[3][3] - m[3][2] * m[2][3])
                - m[0][2] * (m[2][1] * m[3][3] - m[3][1] * m[2][3])
                + m[0][3] * (m[2][1] * m[3][2] - m[3][1] * m[2][2])
            );
            cf_11 = +(
                  m[0][0] * (m[2][2] * m[3][3] - m[3][2] * m[2][3])
                - m[0][2] * (m[2][0] * m[3][3] - m[3][0] * m[2][3])
                + m[0][3] * (m[2][0] * m[3][2] - m[3][0] * m[2][2])
            );
            cf_12 = -(
                  m[0][0] * (m[2][1] * m[3][3] - m[3][1] * m[2][3])
                - m[0][1] * (m[2][0] * m[3][3] - m[3][0] * m[2][3])
                + m[0][3] * (m[2][0] * m[3][1] - m[3][0] * m[2][1])
            );
            cf_13 = +(
                  m[0][0] * (m[2][1] * m[3][2] - m[3][1] * m[2][2])
                - m[0][1] * (m[2][0] * m[3][2] - m[3][0] * m[2][2])
                + m[0][2] * (m[2][0] * m[3][1] - m[3][0] * m[2][1])
            );
            cf_20 = +(
                  m[3][1] * (m[0][2] * m[1][3] - m[1][2] * m[0][3])
                - m[3][2] * (m[0][1] * m[1][3] - m[1][1] * m[0][3])
                + m[3][3] * (m[0][1] * m[1][2] - m[1][1] * m[0][2])
            );
            cf_21 = -(
                  m[3][0] * (m[0][2] * m[1][3] - m[1][2] * m[0][3])
                - m[3][2] * (m[0][0] * m[1][3] - m[1][0] * m[0][3])
                + m[3][3] * (m[0][0] * m[1][2] - m[1][0] * m[0][2])
            );
            cf_22 = +(
                  m[3][0] * (m[0][1] * m[1][3] - m[1][1] * m[0][3])
                - m[3][1] * (m[0][0] * m[1][3] - m[1][0] * m[0][3])
                + m[3][3] * (m[0][0] * m[1][1] - m[1][0] * m[0][1])
            );
            cf_23 = -(
                  m[3][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2])
                - m[3][1] * (m[0][0] * m[1][2] - m[1][0] * m[0][2])
                + m[3][2] * (m[0][0] * m[1][1] - m[1][0] * m[0][1])
            );
            cf_30 = -(
                  m[2][1] * (m[0][2] * m[1][3] - m[1][2] * m[0][3])
                - m[2][2] * (m[0][1] * m[1][3] - m[1][1] * m[0][3])
                + m[2][3] * (m[0][1] * m[1][2] - m[1][1] * m[0][2])
            );
            cf_31 = +(
                  m[2][0] * (m[0][2] * m[1][3] - m[1][2] * m[0][3])
                - m[2][2] * (m[0][0] * m[1][3] - m[1][0] * m[0][3])
                + m[2][3] * (m[0][0] * m[1][2] - m[1][0] * m[0][2])
            );
            cf_32 = -(
                  m[2][0] * (m[0][1] * m[1][3] - m[1][1] * m[0][3])
                - m[2][1] * (m[0][0] * m[1][3] - m[1][0] * m[0][3])
                + m[2][3] * (m[0][0] * m[1][1] - m[1][0] * m[0][1])
            );
            cf_33 = +(
                  m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2])
                - m[2][1] * (m[0][0] * m[1][2] - m[1][0] * m[0][2])
                + m[2][2] * (m[0][0] * m[1][1] - m[1][0] * m[0][1])
            );
            
            inv_det = 1 / (m[0][0] * cf_00 + m[0][1] * cf_01 + m[0][2] * cf_02 + m[0][3] * cf_03);
            
            matrix<Dim,Dim,T> inv{
                vec<Dim,T>{ cf_00, cf_10, cf_20, cf_30 },
                vec<Dim,T>{ cf_01, cf_11, cf_21, cf_31 },
                vec<Dim,T>{ cf_02, cf_12, cf_22, cf_32 },
                vec<Dim,T>{ cf_03, cf_13, cf_23, cf_33 }
            };

            return inv * inv_det;
        }

    };

}

// BINARY OPERATIONS
template<unsigned Dim, typename T, typename U>
constexpr matrix<Dim,Dim,RESULT(T,U,+)> operator+(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2)
{
    return _details::mat_ops<Dim>::add(m1, m2);
}

template<unsigned Dim, typename T, typename U>
constexpr matrix<Dim,Dim,RESULT(T,U,-)> operator-(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2)
{
    return _details::mat_ops<Dim>::sub(m1, m2);
}

template<unsigned Dim, typename T, typename U>
constexpr matrix<Dim,Dim,RESULT(T,U,*)> operator*(const matrix<Dim,Dim,T>& m1, const matrix<Dim,Dim,U>& m2)
{
    return _details::mat_ops<Dim>::prod(m1, m2);
}

template<unsigned Dim, typename T, typename U>
constexpr vec<Dim,RESULT(T,U,*)> operator*(const matrix<Dim,Dim,T>& m, const vec<Dim,U>& v)
{
    return _details::mat_ops<Dim>::vec_prod(m, v);
}

template<unsigned Dim, typename T, typename U>
constexpr matrix<Dim,Dim,RESULT(T,U,*)> operator*(const matrix<Dim,Dim,T>& m, U val)
{
    return _details::mat_ops<Dim>::scale_mult(m, val);
}

template<unsigned Dim, typename T, typename U>
constexpr matrix<Dim,Dim,RESULT(T,U,/)> operator/(const matrix<Dim,Dim,T>& m, U val)
{
    return _details::mat_ops<Dim>::scale_div(m, val);
}

// BASIC MATRIX OPERATIONS
template<unsigned N, typename T>
constexpr matrix<N,N,T> transpose(const matrix<N,N,T>& m)
{
    return _details::mat_ops<N>::transpose(m);
}

template<unsigned N, typename T>
constexpr T determinant(const matrix<N,N,T>& m)
{
    return _details::mat_ops<N>::det(m);
}

template<unsigned N, typename T>
constexpr matrix<N,N,T> inverse(const matrix<N,N,T>& m)
{
    return _details::mat_ops<N>::inv(m);
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