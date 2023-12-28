#include "Image.hpp"

GFX_BEGIN
GFX_BASE_BEGIN

template<typename T>
image<T>::image() : _data{ new pixel<T>[DEFAULT_IMAGE_WIDTH * DEFAULT_IMAGE_HEIGHT] },
                    _width{ DEFAULT_IMAGE_WIDTH }, 
                    _height{ DEFAULT_IMAGE_HEIGHT } { }

template<typename T>
image<T>::image(unsigned int width, unsigned int height, pixel<T> p) : _data{ new pixel<T>[width * height] }, 
                                                                           _width{ width }, _height{ height } 
{
    std::fill_n(_data.get(), _width * _height, p);
}

template<typename T>
image<T>::image(const image<T>& cpy) : _data{ new pixel<T>[cpy._width * cpy._height] }, _width{ cpy._width }, _height{ cpy._height } 
{
    for (unsigned int i = 0; i < _width * _height; ++i)
    {
        _data[i] = cpy._data[i];
    }
}

template<typename T>
image<T>::image(image<T>&& mv) : _data{ std::move(mv._data) }, _width{ mv._width }, _height{ mv._height }
{
    mv._width = 0;
    mv._height = 0;
}

template<typename T>
image<T>& image<T>::operator=(const image& cpy)
{
    if (*this == &cpy) return *this;
    if (_width * _height != cpy._width * cpy._height)
    {
        _width = cpy._width;
        _height = cpy._height;
        _data = std::unique_ptr<pixel<T>[]>{new pixel<T>[width * height]};
        
    }
    for (unsigned i = 0; i < _width * _height; ++i)
    {
        _data[i] = cpy._data[i];
    }
    return *this;
}

template<typename T>
image<T>& image<T>::operator=(image&& mv)
{
    if (*this == &mv) return *this;
    _data = std::move(mv._data);
    width = mv._width;
    height = mv._height;
    mv._width = 0;
    mv._height = 0;
    return *this;
}

template<typename T>
unsigned int image<T>::width() const
{
    return _width;
}

template<typename T>
unsigned int image<T>::height() const
{
    return _height;
}


template<typename T>
std::unique_ptr<pixel<T>[]>& image<T>::data()
{
    return _data;
}

template<typename T>
const std::unique_ptr<pixel<T>[]>& image<T>::data() const
{
    return _data;
}

template<typename T>
pixel<T>& image<T>::at(unsigned x, unsigned y)
{
    return _data[y * width() + x];
}

template<typename T>
const pixel<T>& image<T>::at(unsigned x, unsigned y) const
{
    return _data[y * width() + x];
}

template<typename T>
bool image<T>::set(unsigned int x, unsigned int y, pixel<T> pix)
{
    if (x < width() && y < height()) at(x,y) = pix;
    return x < width() && y < height();
}

template<typename T>
void image<T>::fill(pixel<T> pix)
{
    std::fill_n(_data.get(), width() * height(), pix);
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const image<T>& img)
{
    std::cout << "[";
    for (unsigned int y = 0; y < img.height(); ++y)
    {
        for (unsigned int x = 0; x < img.width(); ++x)
        {
            out << img.at(x,y);
            if (x != img.width() - 1)
            {
                out << ",";
            }
        }
        if (y != img.height() - 1)
        {
            out << "\n";
        }
    }
    return std::cout << "]";
}

GFX_BASE_END
GFX_END