#include "gfx/2D/VertexAdapter.hpp"

namespace gfx::GFX2D
{
    namespace _details
    {
        pair_wrapper::pair_wrapper(edge e) : _edge{ e } {}

        auto pair_wrapper::operator->() const -> const edge*
        {
            return &_edge;
        }

        triangle_wrapper::triangle_wrapper(triangle_vertices points) : _vertices{ points } {}

        auto triangle_wrapper::operator->() const -> const triangle_vertices*
        {
            return &_vertices;
        }
    }
}