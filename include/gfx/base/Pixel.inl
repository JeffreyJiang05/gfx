#include "Pixel.hpp"

GFX_BEGIN
GFX_BASE_BEGIN

template<typename T>
template<typename U>
pixel<T>& pixel<T>::operator=(const pixel<U>& cpy)
{
    red = static_cast<T>(cpy.red);
    green = static_cast<T>(cpy.green);
    blue = static_cast<T>(cpy.blue);
    return *this;
}

template<typename T>
pixel<T>::operator unsigned int()
{
    return (red << 16) | (green << 8) | blue; 
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const pixel<T>& pixel)
{
    return std::cout << "(" << pixel.red << "," << pixel.green << "," << pixel.blue << ")";
}

GFX_BASE_END
GFX_END

template<typename T>
gfx::base::pixel<T> lerp(gfx::base::pixel<T> v0, gfx::base::pixel<T> v1, double t)
{
    return {
        lerp(v0.red, v1.red, t),
        lerp(v0.green, v1.green, t),
        lerp(v0.blue, v1.blue, t)
    };
}

template<typename T>
gfx::base::pixel<T> lerp(const gfx::base::pixel<T>& v0, const gfx::base::pixel<T>& v1, const gfx::base::pixel<T>& v2, vec2 bary)
{
    return { 
        lerp(v0.red, v1.red, v2.red, bary), 
        lerp(v0.green, v1.green, v2.green, bary), 
        lerp(v0.blue, v1.blue, v2.blue, bary) 
    };
}