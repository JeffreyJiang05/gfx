#include "math/Vec.hpp"

#include <iostream>

int main()
{
    vec2 v_default;
    std::cout << "default ctor: " << v_default << "\n";
    vec2 v0{ 1, 2 };
    const vec2 v1{ 4, 5 };
    std::cout << "explicit data: " << v0 << " " << v1 << "\n";
    vec2 cpy{ v0 };
    std::cout << "copy ctor: " << cpy << "\n";
    vec2 mv{ std::move(v1) };
    std::cout << "move ctor: " << mv << "\n";
    
    vec<2,unsigned> vec_unsigned{ 4, 2 };
    std::cout << "unsigned vec: " << vec_unsigned << "\n";

    vec2 vec_unsigned2double{ vec_unsigned };
    std::cout << "unsigned to double ctor: " << vec_unsigned2double << "\n";

    vec2 vec_char2double{ 'a', 'b' };
    std::cout << "explicit char to double ctor: " << vec_char2double << "\n";

    std::cout << "access subscript: v0[0]=" << v0[0] << "\n";
    v0[0] = 2;
    std::cout << "modify subscript: v0[0]=" << v0[0] << "\n";

    std::cout << "access thru at: v0.at(1)=" << v0.at(1) << "\n";
    v0.at(1) = 12;
    std::cout << "moddify thru at: v0.at(1)=" << v0.at(1) << "\n";

    std::cout << "access through x,y: v0.x=" << v0.x() << " v0.y=" << v0.y() << "\n";

    v0 = vec_unsigned;
    std::cout << "assignment unsigned2double: " << v0 << "\n"; 

    v0 += v1;
    std::cout << "+= vec operator: " << v0 << "\n";

    v0 -= v1;
    std::cout << "-= vec operator: " << v0 << "\n";

    v0 *= v1;
    std::cout << "*= vec operator: " << v0 << "\n";

    v0 /= v1;
    std::cout << "/= vec operator: " << v0 << "\n";

    v0 += 2;
    std::cout << "+= scalar operator: " << v0 << "\n";

    v0 -= 2;
    std::cout << "-= scalar operator: " << v0 << "\n";

    v0 *= 2;
    std::cout << "*= scalar operator: " << v0 << "\n";

    v0 /= 2;
    std::cout << "/= scalar operator: " << v0 << "\n";

    std::cout << "prefix increment: " << ++v0 << "\n";
    v0++;
    std::cout << "postfix increment: " << v0 << "\n"; 

    std::cout << "prefix increment: " << --v0 << "\n";
    v0--;
    std::cout << "postfix increment: " << v0 << "\n"; 

    vec3 vec3_0{ 1, 1, 0 };
    std::cout << vec3_0 << "\n";
    vec3 vec3_1{ v0, -1 };
    std::cout << vec3_1 << "\n";
    
    vec4 vec4_0{ 1,2,3,4 };
    std::cout << vec4_0 << "\n";
    vec4 vec4_1{ vec3_0, 4 };
    std::cout << vec4_1 << "\n";
    vec4 vec4_2{ v0, -1, -2 };
    std::cout << vec4_2 << "\n";

    std::cout << "cross: " << cross(vec3_0, vec3_1) << "\n";
    std::cout << "dot: " << dot(vec3_0, vec3_1) << "\n";

    std::cout << "magnitude: " << magnitude(vec3_0) << "\n";
}