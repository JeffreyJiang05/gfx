#ifndef JGRAPHICS_2D_VERTEX_ADAPTER_HPP
#define JGRAPHICS_2D_VERTEX_ADAPTER_HPP

#include <tuple>
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

namespace _details
{
    template<typename T>
    using iterator_t = decltype(std::begin(std::declval<T&>()));

    template<typename Container>
    constexpr inline bool is_index_container_v = std::is_unsigned_v<typename std::iterator_traits<iterator_t<Container>>::value_type> 
            && std::is_same_v<typename std::iterator_traits<iterator_t<Container>>::iterator_category, std::random_access_iterator_tag>;

    template<typename Container>
    struct is_index_container : std::bool_constant<is_index_container_v<Container>> {};

    template<typename ListType>
    class triangle_wrapper
    {
    private:
        using triangle_vertices = std::tuple<typename ListType::value_type, typename ListType::value_type, typename ListType::value_type>;
        triangle_vertices _vertices;
    public:
        triangle_wrapper(triangle_vertices points);
        const triangle_vertices* operator->() const;  
    };

}

// Triangle Adapter Iterator
template<typename IdxContainer, typename ListType>
class triangle_iterator
{
private:
    const IdxContainer& _indices;
    const ListType& _vertices;
    unsigned int _pos;
public:
    using vertices = std::tuple<typename ListType::value_type, typename ListType::value_type, typename ListType::value_type>;

    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = vertices;
    using pointer = _details::triangle_wrapper<ListType>;
    using reference = vertices;

    triangle_iterator(const IdxContainer& indices, const ListType& vertices, unsigned int pos);

    reference operator*() const;
    pointer operator->() const;
    triangle_iterator& operator++();
    triangle_iterator operator++(int);
    triangle_iterator& operator--();
    triangle_iterator operator--(int);

    template<typename Container, typename List>
    friend bool operator==(const triangle_iterator<Container, List>& a, const triangle_iterator<Container, List>& b);
    template<typename Container, typename List>
    friend bool operator!=(const triangle_iterator<Container, List>& a, const triangle_iterator<Container, List>& b);
};

// Triangle Adapter to wrap VertexList and an index list. 
template<typename ListType, typename IdxContainer, typename Enable = std::enable_if<_details::is_index_container_v<IdxContainer>>>
class Triangles
{
private:
    const ListType& _vertices;
    const IdxContainer& _indices;
public:
    using iterator = triangle_iterator<IdxContainer, ListType>;
    using const_iterator = iterator; // since these iterators are read-only

    Triangles(const ListType& vertices, const IdxContainer& indices);

    iterator begin();
    const_iterator cbegin() const;
    iterator end();
    const_iterator cend() const;

};

GFX_GFX2D_END
GFX_END

#undef GFX_GFX2D_BEGIN 
#undef GFX_END 
#undef GFX_GFX2D_END 
#undef GFX_GFX2D_END

#include "VertexAdapter.inl"

#endif