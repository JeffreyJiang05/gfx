#include <iostream>

#include "gfx/2D/Draw.hpp"

int main()
{
    using namespace gfx;
    using namespace gfx::GFX2D;
    using namespace gfx::literals;

    img image{ 200, 200, 0xffffff_rgb };
    draw_line(image, ivec2{ 100, 100 }, ivec2{ 125, 100 }, 0xff0000_rgb);
    draw_line(image, ivec2{ 100, 100 }, ivec2{ 125, 150 }, 0xff00ff_rgb);
    draw_line(image, ivec2{ 100, 100 }, ivec2{ 125, 112 }, 0xffff00_rgb);
    draw_line(image, ivec2{ 100, 100 }, ivec2{ 100, 150 }, 0x00ff00_rgb);
    draw_line(image, ivec2{ 100, 100 }, ivec2{ 100, 50},   0x0000ff_rgb);
    draw_line(image, ivec2{ 100, 100 }, ivec2{ 125, 88 },  0x00ffff_rgb);
    draw_line(image, ivec2{ 100, 100 }, ivec2{ 125, 50 },  0x80ff00_rgb);
    draw_line(image, ivec2{ 100, 100 }, ivec2{ 75, 150 },  0x808000_rgb);
    draw_line(image, ivec2{ 100, 100 }, ivec2{ 75, 112 },  0x800080_rgb);
    draw_line(image, ivec2{ 100, 100 }, ivec2{ 75, 100 },  0x000000_rgb);
    draw_line(image, ivec2{ 100, 100 }, ivec2{ 75, 88 },   0x008080_rgb);
    draw_line(image, ivec2{ 100, 100 }, ivec2{ 75, 50 },   0x000080_rgb);

    draw_line(image, ivec2{ 75, 50 }, ivec2{ 75, 150 },    0x000000_rgb);
    draw_line(image, ivec2{ 125, 50 }, ivec2{ 125, 150 },  0x000000_rgb);
    draw_line(image, ivec2{ 75, 50 }, ivec2{ 125, 50 },    0x000000_rgb);
    draw_line(image, ivec2{ 75, 150 }, ivec2{ 125, 150 },  0x000000_rgb);
    save_image(image, "img/F1.png");
}