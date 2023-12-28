#ifndef JGRAPHICS_2D_CONSTRUCT_HPP
#define JGRAPHICS_2D_CONSTRUCT_HPP

#include "math/Vec.hpp"
#include "math/Matrix.hpp"
#include "VertexList.hpp"

#define GFX_BEGIN namespace gfx {
#define GFX_GFX2D_BEGIN namespace GFX2D {
#define GFX_END }
#define GFX_GFX2D_END }

GFX_BEGIN
GFX_GFX2D_BEGIN

constexpr static inline unsigned int DEFAULT_CIRCLE_STEPS = 100;
constexpr static inline unsigned int DEFAULT_HERMITE_STEPS = 100;
constexpr static inline unsigned int DEFAULT_BEZIER_STEPS = 100;

// CIRCLE

VertexList make_circle(double radius, int steps);

VertexList make_circle(double radius);

// REGULAR POLYGON

VertexList make_regular_polygon(int sides, double radius);

// HERMITE

namespace _details
{
    inline const mat4x4 hermite_coefficient_matrix{ vec4{ 2, -3, 0, 1 }, vec4{ -2, 3, 0, 0 }, vec4{ 1, -2, 1, 0 }, vec4{ 1, -1, 0, 0 } }; 

    inline const mat4x4 bezier_coefficient_matrix{ vec4{ -1, 3, -3, 1 }, vec4{ 3, -6, 3, 0 }, vec4{ -3, 3, 0, 0 }, vec4{ 1, 0, 0, 0 } }; 

    VertexList make_curve(vec2 p0, vec2 p1, vec2 p2, vec2 p3, const mat4x4& transform, int steps);
}

VertexList make_hermite(vec2 p0, vec2 p1, vec2 r0, vec2 r1, int steps);

VertexList make_hermite(vec2 p0, vec2 p1, vec2 r0, vec2 r1);

// BEZIER

VertexList make_bezier(vec2 p0, vec2 p1, vec2 p2, vec2 p3, int steps);

VertexList make_bezier(vec2 p0, vec2 p1, vec2 p2, vec2 p3);

GFX_GFX2D_END
GFX_END

#undef GFX_GFX2D_BEGIN 
#undef GFX_END 
#undef GFX_GFX2D_END 
#undef GFX_GFX2D_END

#endif