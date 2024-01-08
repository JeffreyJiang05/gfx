#include "Operations.hpp"

template<typename T>
constexpr T absolute_value(T x)
{
    return x < 0 ? -x : x;
}

namespace trig
{

    namespace _details
    {
        constexpr double trig_helper(double theta, double sin_res, double prev_term, int step)
        {
            if (absolute_value(prev_term) <= std::numeric_limits<double>::epsilon())
                return sin_res;
            double term = prev_term * -( (theta / (step + 1)) * (theta / (step + 2)) );
            return trig_helper(
                theta,
                sin_res + term,
                term,
                step + 2
            );
        }
    }

    constexpr double radians(double degrees) 
    {
        return degrees * PI * (1 / 180.0);
    } 

    constexpr double degrees(double radians)
    {
        return radians * 180 * INV_PI;
    }

    constexpr double sin(double theta)
    {
        return _details::trig_helper(theta, theta, theta, 1);
    }

    constexpr double cos(double theta)
    {
        return _details::trig_helper(theta, 1, 1, 0);
    }

    constexpr double tan(double theta)
    {
        return sin(theta) / cos(theta);
    }

    constexpr double csc(double theta)
    {
        return 1 / sin(theta);
    }

    constexpr double sec(double theta)
    {
        return 1 / cos(theta);
    }

    constexpr double cot(double theta)
    {
        return cos(theta) / sin(theta);
    }

}

template<typename T>
T lerp(T v0, T v1, double t)
{
    return v0 + t * (v1 - v0);
}

template<typename T>
T lerp(const T& v0, const T& v1, const T& v2, vec2 bary)
{
    return { T(bary[0] * v0 + bary[1] * v1 + (1 - bary[0] - bary[1]) * v2) };
}