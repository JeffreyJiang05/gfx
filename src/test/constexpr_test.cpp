#include <iostream>

#include "math/Matrix.hpp"
#include "math/Constants.hpp"
#include "math/Operations.hpp"

int main()
{
    constexpr mat2x2 mat2_default{};
    constexpr mat2x2 mat2_ctor{vec2{ 2, 3 }, vec2{ 4, 5 }};

    constexpr mat3x3 mat3_default{};
    constexpr mat3x3 mat3_ctor{ vec3{ 1, 2, 3 }, vec3{ 4, 5, 6 }, vec3{ 7, 8, 10 } };

    constexpr mat4x4 mat4_default{};
    constexpr mat4x4 mat4_ctor{ 
        vec4{ 1, 2, 3, 4 }, 
        vec4{ 5, 6, 7, 8 }, 
        vec4{ 9, 10, 11, 12 },
        vec4{ 13, 14, 15, 16 }
    };

    constexpr mat4x4 add_res{ mat4_default + mat4_ctor };

    constexpr mat4x4 prod_res{ add_res * mat4_ctor };
    constexpr mat4x4 transposed{ transpose(prod_res) };

    constexpr vec4 vec_res{ 1, 2, 3, 4 };
    constexpr vec4 vec_mult{ add_res * mat4_ctor[1] };

    constexpr double det{ determinant(add_res) };
    constexpr mat4x4 inv{ inverse(add_res) };

    std::cout << mat2_default << "\n";
    std::cout << mat2_ctor << "\n";

    std::cout << mat3_default << "\n";
    std::cout << mat3_ctor << "\n";

    std::cout << mat4_default << "\n";
    std::cout << mat4_ctor << "\n";

    std::cout << add_res << "\n";
    std::cout << prod_res << "\n";
    std::cout << transposed << "\n";

    std::cout << vec_mult << "\n";
    std::cout << det << "\n";

    std::cout << inv * add_res << "\n";

    return 0;
}