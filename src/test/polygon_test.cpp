#include "gfx/2D/VertexList.hpp"
#include "gfx/2D/Draw.hpp"
#include "gfx/base/Pixel.hpp"
#include "gfx/2D/Transformation.hpp"
#include "gfx/2D/Construct.hpp"

#include "math/Constants.hpp"

#include <iostream>
#include <thread>

int main()
{
    using namespace gfx;
    using namespace gfx::GFX2D;
    using namespace gfx::literals;
    using namespace gfx::GFX2D::transformation;

    VertexList square{ vec2{ -25, -25 }, vec2{ -25, 25 }, vec2{ 25, 25 }, vec2{ 25, -25 } };

    img image{ 500, 500, 0xffffff_rgb };
    draw_line(image, ivec2{ -250, 0 }, ivec2{ 250, 0 }, 0x00ffff_rgb);
    draw_line(image, ivec2{ 0, -250 }, ivec2{ 0, 250 }, 0x00ffff_rgb);

    VertexList res;
    int total_squares = 20;
    for (int i = 0; i < total_squares; ++i)
    {   
        res = square | scale(vec2{ sin(i * TAU / total_squares), sin(i * TAU / total_squares) })
                     | translate(vec2{ 150, 0 })
                     | rotate(i * TAU / total_squares);
                
        draw_construct(image, Edges<Polygon>{ res }, RandomPixelGenerator::instance().generate(), draw_antialias_line);
    }
    draw_construct(image, Edges<Polygon>{ square }, 0xff00ff_rgb, draw_antialias_line);

    VertexList circle{ make_circle(50) };
    draw_construct(image, Edges<Polygon>{ circle }, RandomPixelGenerator::instance().generate(), draw_antialias_line);

    VertexList list{ vec2{ -50, -50 }, vec2{ 50, -50 }, vec2{ 50, 50 } };
    draw_construct(image, Edges<Curve>{ list }, RandomPixelGenerator::instance().generate(), draw_antialias_line);

    save_image(image, "img/polytest.png");
}