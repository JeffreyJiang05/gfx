#ifndef JGRAPHICS_PIXEL_HPP
#define JGRAPHICS_PIXEL_HPP

#include <iostream>
#include <random>

#include "../../math/Operations.hpp"

#define GFX_BEGIN namespace gfx {
#define GFX_BASE_BEGIN namespace base {
#define GFX_END }
#define GFX_BASE_END }

GFX_BEGIN
GFX_BASE_BEGIN

template<typename T>
struct pixel
{
    using data_type = T;

    T red;
    T green;
    T blue;

    template<typename U>
    pixel& operator=(const pixel<U>& cpy);

    explicit operator unsigned int();

};

template<typename T>
std::ostream& operator<<(std::ostream& out, const pixel<T>& pixel);

template<>
std::ostream& operator<<(std::ostream& out, const pixel<unsigned char>& p);

GFX_BASE_END

using pix = base::pixel<unsigned char>;

class RandomPixelGenerator
{
private:
    std::random_device rd;
    std::seed_seq seq;
    std::mt19937 rng;
    std::uniform_int_distribution<> distrib;

    RandomPixelGenerator();
    ~RandomPixelGenerator() = default;
public:
    RandomPixelGenerator(const RandomPixelGenerator&) = delete;
    RandomPixelGenerator(RandomPixelGenerator&&) = delete;
    RandomPixelGenerator& operator=(const RandomPixelGenerator) = delete;
    RandomPixelGenerator& operator=(RandomPixelGenerator&&) = delete;

    static RandomPixelGenerator& instance();

    pix generate();
};

namespace literals {

    pix operator""_rgb(unsigned long long rgb_value);

}

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

#include "Pixel.inl"

#undef GFX_BEGIN
#undef GFX_BASE_BEGIN
#undef GFX_END
#undef GFX_BASE_END

#endif