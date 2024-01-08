#ifndef JGRAPHICS_OPERATIONS_HPP
#define JGRAPHICS_OPERATIONS_HPP

#include <numeric>

#include "Vec.hpp"
#include "Constants.hpp"

namespace trig
{

    constexpr double radians(double degrees);

    constexpr double degrees(double radians);

    constexpr double sin(double theta);

    constexpr double cos(double theta);

    constexpr double tan(double theta);

    constexpr double csc(double theta);

    constexpr double sec(double theta);

    constexpr double cot(double theta);

}

template<typename T>
constexpr T absolute_value(T x);

template<typename T>
T lerp(T v0, T v1, double t);

template<typename T>
T lerp(const T& v0, const T& v1, const T& v2, vec2 bary);

#include "Operations.inl"

#endif