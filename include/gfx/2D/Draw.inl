#include "Draw.hpp"

#define GFX_BEGIN namespace gfx {
#define GFX_GFX2D_BEGIN namespace GFX2D {
#define GFX_END }
#define GFX_GFX2D_END }

GFX_BEGIN
GFX_GFX2D_BEGIN

template<template<typename> class EdgeIterator, typename LineFunc>
std::enable_if_t<_details::is_valid_line_algo<LineFunc>> draw_construct(img& image, Edges<EdgeIterator> edges, img::pix pixel, LineFunc line_algo)
{
    for (auto&& edge : edges)
    {
        line_algo(image, 
            ivec2{ static_cast<int>(edge.first.x()), static_cast<int>(edge.first.y()) }, 
            ivec2{ static_cast<int>(edge.second.x()), static_cast<int>(edge.second.y()) }, 
        pixel);
    }
}

template<template<typename> class EdgeIterator>
void draw_construct(img& image, Edges<EdgeIterator> edges, img::pix pixel)
{
    for (auto&& edge : edges)
    {
        draw_line(image, 
            ivec2{ static_cast<int>(edge.first.x()), static_cast<int>(edge.first.y()) }, 
            ivec2{ static_cast<int>(edge.second.x()), static_cast<int>(edge.second.y()) }, 
        pixel);
    }
}

GFX_GFX2D_END
GFX_END

#undef GFX_GFX2D_BEGIN 
#undef GFX_END 
#undef GFX_GFX2D_END 
#undef GFX_GFX2D_END