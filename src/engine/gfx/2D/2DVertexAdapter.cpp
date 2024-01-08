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
    }
}