#include "Draw.hpp"

#define GFX_BEGIN namespace gfx {
#define GFX_GFX2D_BEGIN namespace GFX2D {
#define GFX_END }
#define GFX_GFX2D_END }

GFX_BEGIN
GFX_GFX2D_BEGIN

namespace _details
{
    template<unsigned N, typename T>
    void frame_vector(const img& img, vec<N, T>& data)
    {
        data[X] += (static_cast<int>(img.width()) >> 1);
        data[Y] = (static_cast<int>(img.height()) >> 1) - data[Y];
    }
}

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

template<typename Func, unsigned N, typename... Ts>
void draw_triangle_filled(img& image, std::tuple<vec<N, double>, Ts...> d0, std::tuple<vec<N, double>, Ts...> d1, std::tuple<vec<N, double>, Ts...> d2, Func&& func)
{
    using vec_type = vec<N, double>;
    _details::frame_vector(image, get_vertex(d0));
    _details::frame_vector(image, get_vertex(d1));
    _details::frame_vector(image, get_vertex(d2)); 

    // v0 < v1 < v2
    if (get_vertex(d1).y() < get_vertex(d0).y()) std::swap(d1, d0);
    if (get_vertex(d2).y() < get_vertex(d0).y()) std::swap(d2, d0);
    if (get_vertex(d2).y() < get_vertex(d1).y()) std::swap(d2, d1); 

    vec_type& v0 = get_vertex(d0);
    vec_type& v1 = get_vertex(d1);
    vec_type& v2 = get_vertex(d2);

    std::cout << std::get<1>(d0) << "\n";
    std::cout << std::get<1>(d1) << "\n";
    std::cout << std::get<1>(d2) << "\n";

    double dx0, dx1, temp, xbegin, xend;
    dx0 = (v2.x() - v0.x()) / (v2.y() - v0.y() + 0.1);
    dx1 = (v1.x() - v0.x()) / (v1.y() - v0.y() + 0.1);
    temp = (v2.x() - v1.x()) / (v2.y() - v1.y() + 0.1);

    xbegin = v0.x();
    xend = v0.x();

    std::cout << dx0 << " / " << dx1 << " / " << temp << " / " << xbegin << " / " << xend << "\n";

    // barycentric calculations
    double x21, y12, x02, y20, inv_det, xx2, yy2, bary0, bary1;
    x21 = v2.x() - v1.x();
    y12 = v1.y() - v2.y();
    x02 = v0.x() - v2.x();
    y20 = v2.y() - v0.y();
    inv_det = 1 / (y12 * (v0.x() - v2.x()) + x21 * (v0.y() - v2.y()));

    for (int y = static_cast<int>(v0.y()); y <= static_cast<int>(v2.y()); ++y, xbegin += dx0, xend += dx1)
    {
        if (y == static_cast<int>(v1.y()))
        {
            dx1 = temp;
            xend = v1.x();
        }
        auto [xmin, xmax] = std::minmax(xbegin, xend);
        for (int x = static_cast<int>(xmin); x < static_cast<int>(xmax); ++x)
        {

            xx2 = x - v2.x();
            yy2 = y - v2.y();

            bary0 = (y12 * xx2 + x21 * yy2) * inv_det;
            bary1 = (y20 * xx2 + x02 * yy2) * inv_det;

            if ((unsigned) x <= image.width() && (unsigned) y <= image.height() && bary0 >= 0 && bary1 >= 0 && bary0 + bary1 <= 1)
            {
                image.set(x, y, std::forward<Func>(func)(vec2{ bary0, bary1 }, d0, d1, d2) );
            }
        }
    }
}

GFX_GFX2D_END
GFX_END

#undef GFX_GFX2D_BEGIN 
#undef GFX_END 
#undef GFX_GFX2D_END 
#undef GFX_GFX2D_END