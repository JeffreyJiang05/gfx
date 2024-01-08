#include "gfx/2D/VertexList.hpp"
#include "gfx/2D/DataList.hpp"
#include "gfx/2D/Draw.hpp"
#include "gfx/base/Pixel.hpp"
#include "gfx/2D/Transformation.hpp"

#include "math/Constants.hpp"

#include <iostream>
#include <thread>

int main()
{
    using namespace gfx;
    using namespace gfx::GFX2D;
    using namespace gfx::literals;
    using namespace gfx::GFX2D::transformation;

    img image{ 500, 500, 0xffffff_rgb };

    VertexList vertices{
        vec2{ -100, -100 },
        vec2{ -100, -50 },
        vec2{ 0, -75 },
        vec2{ -100, 0 },
        vec2{ -50, 0 },
        vec2{ -75, 75 },
        vec2{ 50, -25 },
        vec2{ 100, 75 },
        vec2{ 125, 50 }
    };

    unsigned int indices[]{ 
        0, 1, 2,
        3, 4, 5
    };

    using Data = DataList<3, img::pix>;

    Data data{
        { vec3{ -100, -100, 1 }, 0xff0000_rgb },
        { vec3{ -100, -50, 1 }, 0x00ff00_rgb },
        { vec3{ 0, -75, 1 }, 0x0000ff_rgb },

        { vec3{ -300, -100, 1 }, 0xffff00_rgb },
        { vec3{ -100, 20, 1 }, 0x00ffff_rgb },
        { vec3{ -200, 75, 1 }, 0xff00ff_rgb }
    };

    draw_line(image, ivec2{ -100, -250 }, ivec2{ -100, 250 }, RandomPixelGenerator::instance().generate());
    draw_line(image, ivec2{ -250, 20 }, ivec2{ 250, 20 }, RandomPixelGenerator::instance().generate());

    // VertexList res = vertices | scale(vec2{ 2, 2 });
    for (auto&& [v0, v1, v2] : Triangles{ data, indices })
    {
        draw_triangle_filled(image, v0, v1, v2, 
            [](vec2 bary, const Data::value_type& d0, const Data::value_type& d1, const Data::value_type& d2)
            {
                return lerp(std::get<1>(d0), std::get<1>(d1), std::get<1>(d2), bary);
            }
        );
    }

    save_image(image, "img/triangle_test.png");

    return 0;

}