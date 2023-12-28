#include "math/Matrix.hpp"

#include <iostream>

int main()
{
    mat2x2 mat_ident;
    std::cout << "identity: " << mat_ident << "\n";
    mat2x2 mat_fill{ 2 };
    std::cout << "identity: " << mat_fill << "\n";
}