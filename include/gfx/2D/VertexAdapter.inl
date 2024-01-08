#include "VertexAdapter.hpp"

#define GFX_BEGIN namespace gfx {
#define GFX_GFX2D_BEGIN namespace GFX2D {
#define GFX_END }
#define GFX_GFX2D_END }

GFX_BEGIN
GFX_GFX2D_BEGIN

// These are read-only iterators. They copy the data into a container which
// can be accessed. May be more cache-friendly as it avoid pointer indirection.

// DEFINE CONTAINER WRAPPER

// EDGE CONTAINER

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

// TRIANGLE CONTAINER

template<typename ListType, typename IdxContainer, typename Enable>
Triangles<ListType, IdxContainer, Enable>::Triangles(const ListType& vertices, const IdxContainer& indices)
        : _vertices{ vertices }, _indices{ indices } {}

template<typename ListType, typename IdxContainer, typename Enable>
auto Triangles<ListType, IdxContainer, Enable>::begin() -> iterator
{
    return { _indices, _vertices, 0 };
}

template<typename ListType, typename IdxContainer, typename Enable>
auto Triangles<ListType, IdxContainer, Enable>::cbegin() const -> const_iterator
{
    return { _indices, _vertices, 0 };
}

template<typename ListType, typename IdxContainer, typename Enable>
auto Triangles<ListType, IdxContainer, Enable>::end() -> iterator
{
    return { _indices, _vertices, static_cast<unsigned>(std::size(_indices)) };
}

template<typename ListType, typename IdxContainer, typename Enable>
auto Triangles<ListType, IdxContainer, Enable>::cend() const -> const_iterator
{
    return { _indices, _vertices, static_cast<unsigned>(std::size(_indices)) };
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

// DEFINE TRIANGLE ITERATOR

namespace _details
{
    template<typename ListType>
    triangle_wrapper<ListType>::triangle_wrapper(triangle_vertices points) : _vertices{ points } {}

    template<typename ListType>
    auto triangle_wrapper<ListType>::operator->() const -> const triangle_vertices*
    {
        return &_vertices;
    }
}

template<typename IdxContainer, typename ListType>
triangle_iterator<IdxContainer, ListType>::triangle_iterator(const IdxContainer& indices, const ListType& vertices, unsigned int pos)
        : _indices{ indices }, _vertices{ vertices }, _pos{ pos } {}

template<typename IdxContainer, typename ListType>
auto triangle_iterator<IdxContainer, ListType>::operator*() const -> reference
{
    return { 
        _vertices[_indices[_pos + 0]],
        _vertices[_indices[_pos + 1]],
        _vertices[_indices[_pos + 2]]
    };
}

template<typename IdxContainer, typename ListType>
auto triangle_iterator<IdxContainer, ListType>::operator->() const -> pointer
{
    return **this;
}

template<typename IdxContainer, typename ListType>
auto triangle_iterator<IdxContainer, ListType>::operator++() -> triangle_iterator&
{
    _pos += 3;
    return *this;
}

template<typename IdxContainer, typename ListType>
auto triangle_iterator<IdxContainer, ListType>::operator++(int) -> triangle_iterator
{
    triangle_iterator<IdxContainer, ListType> res{ *this };
    _pos += 3;
    return res;
}

template<typename IdxContainer, typename ListType>
auto triangle_iterator<IdxContainer, ListType>::operator--() -> triangle_iterator&
{
    _pos -= 3;
    return *this;
}

template<typename IdxContainer, typename ListType>
auto triangle_iterator<IdxContainer, ListType>::operator--(int) -> triangle_iterator
{
    triangle_iterator<IdxContainer, ListType> res{ *this };
    _pos -= 3;
    return res;
}

template<typename Container, typename List>
bool operator==(const triangle_iterator<Container, List>& a, const triangle_iterator<Container, List>& b)
{
    return (&(a._indices) == &(b._indices)) 
            && (&(a._vertices) == &(b._vertices)) 
            && (a._pos == b._pos);
}

template<typename Container, typename List>
bool operator!=(const triangle_iterator<Container, List>& a, const triangle_iterator<Container, List>& b)
{
    return !(a == b);
}

GFX_GFX2D_END
GFX_END

#undef GFX_GFX2D_BEGIN 
#undef GFX_END 
#undef GFX_GFX2D_END 
#undef GFX_GFX2D_END