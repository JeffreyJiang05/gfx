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
        3, 4, 5,
        6, 7, 8
    };

    DataList<3, img::pix> data{
        { vec3{ -100, -100, 1 }, 0xff0000_rgb },
        { vec3{ -100, -50, 1 }, 0x00ff00_rgb },
        { vec3{ 0, -75, 1 }, 0x0000ff_rgb }
    };

    for (auto&& [v0, color] : data)
    {
        std::cout << v0 << " - " << color << "\n";
    }

    // VertexList res = vertices | scale(vec2{ 2, 2 });
    for (auto&& [v0, v1, v2] : Triangles{ vertices, indices })
    {
        // draw_triangle_wireframe(image, static_cast<ivec3>(v0), static_cast<ivec3>(v1), static_cast<ivec3>(v2),  RandomPixelGenerator::instance().generate());
        // draw_triangle_antialias_wireframe(image, static_cast<ivec3>(v0), static_cast<ivec3>(v1), static_cast<ivec3>(v2), RandomPixelGenerator::instance().generate());
        draw_triangle_filled(image, static_cast<ivec3>(v0), static_cast<ivec3>(v1), static_cast<ivec3>(v2), RandomPixelGenerator::instance().generate());
    }

    save_image(image, "img/triangle_test.png");

    return 0;

}