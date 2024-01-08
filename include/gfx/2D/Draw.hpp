#ifndef JGRAPHICS_2D_DRAW_HPP
#define JGRAPHICS_2D_DRAW_HPP

#include "gfx/base/Image.hpp"
#include "gfx/2D/VertexList.hpp"
#include "gfx/2D/VertexAdapter.hpp"
#include "math/Vec.hpp"

#define GFX_BEGIN namespace gfx {
#define GFX_GFX2D_BEGIN namespace GFX2D {
#define GFX_END }
#define GFX_GFX2D_END }

GFX_BEGIN
GFX_GFX2D_BEGIN

namespace _details
{
    constexpr static inline unsigned int X = 0;
    constexpr static inline unsigned int Y = 1;

    template<unsigned N, typename T>
    void frame_vector(const img& img, vec<N, T>& data);
}

// Uses Bresenham's algorithm
void draw_line(img& image, ivec2 p0, ivec2 p1, img::pix pixel);

void draw_antialias_line(img& img, ivec2 p0, ivec2 p1, img::pix pixel);

namespace _details
{
    template<typename LineFunc>
    constexpr inline bool is_valid_line_algo = std::is_invocable_v<LineFunc, img&, ivec2, ivec2, img::pix>;
}

template<template<typename> class EdgeIterator, typename LineFunc>
std::enable_if_t<_details::is_valid_line_algo<LineFunc>> draw_construct(img& image, Edges<EdgeIterator> edges, img::pix pixel, LineFunc line_algo);

template<template<typename> class EdgeIterator>
void draw_construct(img& image, Edges<EdgeIterator> edges, img::pix pixel);

void draw_triangle_wireframe(img& image, ivec3 v0, ivec3 v1, ivec3 v2, img::pix pixel);

void draw_triangle_antialias_wireframe(img& image, ivec3 v0, ivec3 v1, ivec3 v2, img::pix pixel);

void draw_triangle_filled(img& image, ivec3 v0, ivec3 v1, ivec3 v2, img::pix pixel);

template<typename Func, unsigned N, typename... Ts>
void draw_triangle_filled(img& image, std::tuple<vec<N, double>, Ts...> d0, std::tuple<vec<N, double>, Ts...> d1, std::tuple<vec<N, double>, Ts...> d2, Func&& func);

GFX_GFX2D_END
GFX_END

#undef GFX_GFX2D_BEGIN 
#undef GFX_END 
#undef GFX_GFX2D_END 
#undef GFX_GFX2D_END

#include "Draw.inl"

#endif