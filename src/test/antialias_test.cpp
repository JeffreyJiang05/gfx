#include "gfx/2D/VertexList.hpp"
#include "gfx/2D/Draw.hpp"
#include "gfx/base/Pixel.hpp"
#include "gfx/2D/Transformation.hpp"

#include <iostream>
#include <thread>

int main()
{
    using namespace gfx;
    using namespace gfx::GFX2D;
    using namespace gfx::literals;
    using namespace gfx::GFX2D::transformation;

    VertexList square{ vec2{ -25, -25 }, vec2{ -25, 25 }, vec2{ 25, 25 }, vec2{ 25, -25 } };

    gfx::img image{ 500, 500, 0xffffff_rgb };
    draw_antialias_line(image, ivec2{ -250, 0 }, ivec2{ 100, 100 }, 0x00ffff_rgb);
    draw_antialias_line(image, ivec2{ 0, -250 }, ivec2{ 20, -150 }, 0x00ffff_rgb);

    save_image(image, "img/alias_test.png");
}