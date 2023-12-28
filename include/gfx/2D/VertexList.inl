#include "VertexList.hpp"

#define GFX_BEGIN namespace gfx {
#define GFX_GFX2D_BEGIN namespace GFX2D {
#define GFX_END }
#define GFX_GFX2D_END }

GFX_BEGIN
GFX_GFX2D_BEGIN

template<typename Iter>
auto VertexList::add_vertices(Iter begin, Iter end) -> is_valid_iter<Iter>
{
    while (begin != end)
    {
        _vertices.push_back(*begin); // MOVE INSTEAD?
        ++begin;
    }
}

GFX_GFX2D_END
GFX_END

#undef GFX_GFX2D_BEGIN 
#undef GFX_END 
#undef GFX_GFX2D_END 
#undef GFX_GFX2D_END