#include "gfx/2D/VertexList.hpp"
#include "gfx/2D/Draw.hpp"
#include "gfx/base/Pixel.hpp"
#include "gfx/2D/Transformation.hpp"
#include "gfx/2D/Construct.hpp"

int main()
{
    using namespace gfx;
    using namespace gfx::GFX2D;
    using namespace gfx::literals;
    using namespace gfx::GFX2D::transformation;

    VertexList square{ make_regular_polygon(4, 10) };
    std::cout << square.size() << "\n";

    return 0;    
}