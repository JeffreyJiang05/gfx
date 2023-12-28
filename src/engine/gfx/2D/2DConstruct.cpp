#include "gfx/2D/Construct.hpp"

namespace gfx::GFX2D
{

    // CIRCLE

    VertexList make_circle(double radius, int steps)
    {
        VertexList vertices;

        for (int i = 0; i < steps; ++i)
        {
            vertices.add_vertex(
                vec2{ radius * cos(i * 2 * M_PI / steps),
                      radius * sin(i * 2 * M_PI / steps) }
            );
        }

        return vertices;
    }

    VertexList make_circle(double radius)
    {
        return make_circle(radius, DEFAULT_CIRCLE_STEPS);
    }

    // REGULAR POLYGON

    VertexList make_regular_polygon(int sides, double radius)
    {
        return make_circle(radius, sides);
    }

    namespace _details
    {
        VertexList make_curve(vec2 p0, vec2 p1, vec2 p2, vec2 p3, const mat4x4& transform, int steps)
        {
            vec4 x_coefficient{ transform * vec4{ p0.x(), p1.x(), p2.x(), p3.x() } };
            vec4 y_coefficient{ transform * vec4{ p0.y(), p1.y(), p2.y(), p3.y() } };
        
            VertexList vertices;
            vertices.reserve_vertices(steps + 1);
            for (int i = 0; i <= steps; ++i)
            {
                double t = i / static_cast<double>(steps);
                vertices.add_vertex(vec2{ 
                    t * (t * (t * x_coefficient[0] + x_coefficient[1]) + x_coefficient[2]) + x_coefficient[3],
                    t * (t * (t * y_coefficient[0] + y_coefficient[1]) + y_coefficient[2]) + y_coefficient[3]
                });
            }
            return vertices;
        }
    }

    // HERMITE

    VertexList make_hermite(vec2 p0, vec2 p1, vec2 r0, vec2 r1, int steps)
    {
        return _details::make_curve(p0, p1, r0, r1, _details::hermite_coefficient_matrix, steps);
    }

    VertexList make_hermite(vec2 p0, vec2 p1, vec2 r0, vec2 r1)
    {
        constexpr int STEPS = 0x40;
        return make_hermite(p0, p1, r0, r1, STEPS);
    }

    // BEZIER

    VertexList make_bezier(vec2 p0, vec2 p1, vec2 p2, vec2 p3, int steps)
    {
        return _details::make_curve(p0, p1, p2, p3, _details::bezier_coefficient_matrix, steps);
    }

    VertexList make_bezier(vec2 p0, vec2 p1, vec2 p2, vec2 p3)
    {
        constexpr int STEPS = 0x40;
        return make_bezier(p0, p1, p2, p3, STEPS);
    }

}