#include "VertexAdapter.hpp"

#define GFX_BEGIN namespace gfx {
#define GFX_GFX2D_BEGIN namespace GFX2D {
#define GFX_END }
#define GFX_GFX2D_END }

GFX_BEGIN
GFX_GFX2D_BEGIN

// DEFINE ITERATOR WRAPPER

template<template<typename> typename EdgeIterator>
Edges<EdgeIterator>::Edges(VertexList& vertices) : _vertices{ vertices } {}

template<template<typename> typename EdgeIterator>
auto Edges<EdgeIterator>::begin() -> iterator
{
    return EdgeIterator{ _vertices.begin(), _vertices.begin(), _vertices.end() };
}

template<template<typename> typename EdgeIterator>
auto Edges<EdgeIterator>::cbegin() const -> const_iterator
{
    return EdgeIterator{ _vertices.cbegin(), _vertices.cbegin(), _vertices.cend() };
}

template<template<typename> typename EdgeIterator>
auto Edges<EdgeIterator>::end() -> iterator
{
    return EdgeIterator{ _vertices.end(), _vertices.begin(), _vertices.end() };
}

template<template<typename> typename EdgeIterator>
auto Edges<EdgeIterator>::cend() const -> const_iterator
{
    return EdgeIterator{ _vertices.cend(), _vertices.cbegin(), _vertices.cend() };
}


// DEFINE ITERATORS

// DEFINE POLYGON EDGE ITERATOR

template<typename Iter>
Polygon<Iter>::Polygon(Iter iter, Iter begin, Iter end) 
        : _iter{ iter }, _begin{ begin }, _end{ end } {}

template<typename Iter>
auto Polygon<Iter>::operator*() const -> reference
{
    Iter _second = _iter;
    if (++_second == _end) _second = _begin;
    return { *_iter, *_second };
}

template<typename Iter>
auto Polygon<Iter>::operator->() const -> pointer
{
    return **this;
}

template<typename Iter>
auto Polygon<Iter>::operator++() -> Polygon&
{
    ++_iter;
    return *this;
}

template<typename Iter>
auto Polygon<Iter>::operator++(int) -> Polygon
{
    Polygon<Iter> cp = *this;
    ++_iter;
    return cp;
}

template<typename Iter>
auto Polygon<Iter>::operator--() -> Polygon&
{
    --_iter;
    return *this;
}

template<typename Iter>
auto Polygon<Iter>::operator--(int) -> Polygon
{
    Polygon<Iter> cp = *this;
    --_iter;
    return cp;
}

template<typename I>
bool operator==(const Polygon<I>& a, const Polygon<I>& b)
{
    return a._iter == b._iter;
}

template<typename I>
bool operator!=(const Polygon<I>& a, const Polygon<I>& b)
{
    return a._iter != b._iter;
}

// DEFINE CURVE EDGE ITERATOR

template<typename Iter>
Curve<Iter>::Curve(Iter first, Iter begin, Iter end) 
        : _first{ first }, _second{ first }, _begin{ begin }, _end{ end }
{
    if (_first == _end)
    {
        --_first;
        --_end;
    }
    ++_second;
}

template<typename Iter>
auto Curve<Iter>::operator*() const -> reference
{
    return { *_first, *_second };
}

template<typename Iter>
auto Curve<Iter>::operator->() const -> pointer
{
    return **this;
}

template<typename Iter>
auto Curve<Iter>::operator++() -> Curve&
{
    ++_first;
    ++_second;
    return *this;
}

template<typename Iter>
auto Curve<Iter>::operator++(int) -> Curve
{
    Polygon<Iter> cp = *this;
    ++_first;
    ++_second;
    return cp;
}

template<typename Iter>
auto Curve<Iter>::operator--() -> Curve&
{
    --_first;
    --_second;
    return *this;
}

template<typename Iter>
auto Curve<Iter>::operator--(int) -> Curve
{
    Polygon<Iter> cp = *this;
    --_first;
    --_second;
    return cp;
}

template<typename I>
bool operator==(const Curve<I>& a, const Curve<I>& b)
{
    return a._first == b._first;
}

template<typename I>
bool operator!=(const Curve<I>& a, const Curve<I>& b)
{
    return a._first != b._first;
}

GFX_GFX2D_END
GFX_END

#undef GFX_GFX2D_BEGIN 
#undef GFX_END 
#undef GFX_GFX2D_END 
#undef GFX_GFX2D_END