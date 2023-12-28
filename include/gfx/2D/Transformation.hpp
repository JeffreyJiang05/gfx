#ifndef JGRAPHICS_2D_TRANSFORMATION_HPP
#define JGRAPHICS_2D_TRANSFORMATION_HPP

#include "math/Matrix.hpp"

#define GFX_BEGIN namespace gfx {
#define GFX_GFX2D_TRANSFORM_BEGIN namespace GFX2D::transformation {
#define GFX_END }
#define GFX_GFX2D_TRANSFORM_END }

GFX_BEGIN
GFX_GFX2D_TRANSFORM_BEGIN 

mat3x3 scale(vec2 scale);

mat3x3 translate(vec2 translate);

mat3x3 rotate(double angle);

mat3x3 shear(vec2 shear_factor);

GFX_GFX2D_TRANSFORM_END
GFX_END

#undef GFX_BEGIN
#undef GFX_GFX2D_TRANSFORM_BEGIN 
#undef GFX_END
#undef GFX_GFX2D_TRANSFORM_END

#endif