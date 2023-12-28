#include "Operations.hpp"

template<typename T>
T lerp(T v0, T v1, double t)
{
    return v0 + t * (v1 - v0);
}