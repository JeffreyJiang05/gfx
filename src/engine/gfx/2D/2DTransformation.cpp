#include "gfx/2D/Transformation.hpp"

#include <cmath>

namespace gfx::GFX2D::transformation
{

    mat3x3 scale(vec2 scale)
    {
        return mat3x3{ vec3{ scale[0], 0, 0 }, vec3{ 0, scale[1], 0 }, vec3{ 0, 0, 1 } };
    }

    mat3x3 translate(vec2 translate)
    {
        return mat3x3{ vec3{ 1, 0, 0 }, vec3{ 0, 1, 0 }, vec3{ translate[0], translate[1], 1 } };
    }

    mat3x3 rotate(double angle)
    {
        return mat3x3{ 
            vec3{ std::cos(angle), std::sin(angle), 0 },
            vec3{ -std::sin(angle), std::cos(angle), 0 },
            vec3{ 0, 0, 1 }
        };
    }

    mat3x3 shear(vec2 shear_factor)
    {
        return mat3x3{ 
            vec3{ 1, shear_factor[1], 0 },
            vec3{ shear_factor[0], 1, 0 },
            vec3{ 0, 0, 1 }
        };
    }

}