#ifndef JGRAPHICS_2D_VERTEX_ADAPTER_HPP
#define JGRAPHICS_2D_VERTEX_ADAPTER_HPP

#include <utility>

#include "VertexList.hpp"
#include "math/Vec.hpp"

#define GFX_BEGIN namespace gfx {
#define GFX_GFX2D_BEGIN namespace GFX2D {
#define GFX_END }
#define GFX_GFX2D_END }

GFX_BEGIN
GFX_GFX2D_BEGIN

namespace _details
{
    class pair_wrapper
    {
    private:
        using edge = std::pair<vec3, vec3>;
        edge _edge;
    public:
        pair_wrapper(edge e);
        const edge* operator->() const;
    };
}

// Edge Adapter to wrap VertexList that allows iterator access per edge.

template<template<typename> typename EdgeIterator>
class Edges
{
private:
    VertexList& _vertices;
public:
    using iterator = EdgeIterator<VertexList::list_type::iterator>;
    using const_iterator = EdgeIterator<VertexList::list_type::const_iterator>;

    explicit Edges(VertexList& vertices);

    iterator begin();
    const_iterator cbegin() const;
    iterator end();
    const_iterator cend() const;
};

template<typename Iter>
class Polygon
{
private:
    Iter _iter;
    Iter _begin;
    Iter _end;
public:
    using edge = std::pair<vec3, vec3>;

    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = edge;
    using pointer = _details::pair_wrapper;
    using reference = edge;

    Polygon(Iter iter, Iter begin, Iter end);

    reference operator*() const;
    pointer operator->() const;
    Polygon& operator++();
    Polygon operator++(int);
    Polygon& operator--();
    Polygon operator--(int);

    template<typename I>
    friend bool operator==(const Polygon<I>& a, const Polygon<I>& b);
    template<typename I>
    friend bool operator!=(const Polygon<I>& a, const Polygon<I>& b);
}; 

template<typename Iter>
class Curve
{
private:
    Iter _first;
    Iter _second;
    Iter _begin;
    Iter _end;
public:
    using edge = std::pair<vec3, vec3>;

    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = edge;
    using pointer = _details::pair_wrapper;
    using reference = edge;

    Curve(Iter first, Iter begin, Iter end);

    reference operator*() const;
    pointer operator->() const;
    Curve& operator++();
    Curve operator++(int);
    Curve& operator--();
    Curve operator--(int);

    template<typename I>
    friend bool operator==(const Curve<I>& a, const Curve<I>& b);
    template<typename I>
    friend bool operator!=(const Curve<I>& a, const Curve<I>& b);
}; 

// Triangle Adapter to wrap VertexList and an index list. 
class Triangles;

GFX_GFX2D_END
GFX_END

#undef GFX_GFX2D_BEGIN 
#undef GFX_END 
#undef GFX_GFX2D_END 
#undef GFX_GFX2D_END

#include "VertexAdapter.inl"

#endif