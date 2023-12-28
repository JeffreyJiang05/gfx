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