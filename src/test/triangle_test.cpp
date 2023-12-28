#include "gfx/2D/VertexList.hpp"
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

    VertexList vertices{
        vec2{ 1, 1 },
        vec2{ 2, 2 },
        vec2{ 3, 3 },
        vec2{ 4, 4 }
    };
    unsigned int indices[]{ 
        1, 1, 2, 
        3, 3, 3,
        0, 1, 2
    };

    for (auto&& [v1, v2, v3] : Triangles{ vertices, indices })
    {
        std::cout << v1 << " / " << v2 << " / " << v3 << "\n";
    }

    return 0;

}