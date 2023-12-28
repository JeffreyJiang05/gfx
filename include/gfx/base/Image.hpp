#ifndef JGRAPHICS_IMAGE_HPP
#define JGRAPHICS_IMAGE_HPP

#include <vector>
#include <memory>
#include <string>

#include "Pixel.hpp"

#define GFX_BEGIN namespace gfx {
#define GFX_END }
#define GFX_BASE_BEGIN namespace base {
#define GFX_BASE_END }

GFX_BEGIN
GFX_BASE_BEGIN

constexpr inline static unsigned int DEFAULT_IMAGE_WIDTH = 500;
constexpr inline static unsigned int DEFAULT_IMAGE_HEIGHT = 500;

template<typename T>
class image
{
private:
    std::unique_ptr<pixel<T>[]> _data;
    unsigned int _width;
    unsigned int _height;
public:
    using pix = pixel<T>;

    image();
    image(unsigned int width, unsigned int height, pixel<T> p);
    image(const image& cpy);
    image(image&& mv);
    image& operator=(const image& cpy);
    image& operator=(image&& mv);
    ~image() = default;

    unsigned int width() const;
    unsigned int height() const;
    std::unique_ptr<pixel<T>[]>& data();
    const std::unique_ptr<pixel<T>[]>& data() const;

    pixel<T>& at(unsigned int x, unsigned int y);
    const pixel<T>& at(unsigned int x, unsigned int y) const;

    bool set(unsigned int x, unsigned int y, pixel<T> pix);
    void fill(pixel<T> pix);
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const image<T>& img);

GFX_BASE_END

using img = base::image<unsigned char>;

void save_image(const img& im, std::string fn);

GFX_END

#include "Image.inl"

#undef GFX_BEGIN
#undef GFX_BASE_BEGIN
#undef GFX_END
#undef GFX_BASE_END

#endif