#ifndef JGRAPHICS_2D_VERTEX_LIST_HPP
#define JGRAPHICS_2D_VERTEX_LIST_HPP

#include <vector>
#include <ostream>
#include <initializer_list>
#include <iterator>

#include "math/Vec.hpp"
#include "math/Matrix.hpp"

#define GFX_BEGIN namespace gfx {
#define GFX_GFX2D_BEGIN namespace GFX2D {
#define GFX_END }
#define GFX_GFX2D_END }

GFX_BEGIN
GFX_GFX2D_BEGIN

class VertexList
{
public:
    using vertex_type = vec3;
    using list_type = std::vector<vertex_type>;
private:
    list_type _vertices;
    
    template<typename Iter>
    using is_valid_iter = std::enable_if_t<std::is_same_v<typename std::iterator_traits<Iter>::value_type,vec2>>;
public:
    using iterator = VertexList::list_type::iterator;
    using const_iterator = VertexList::list_type::const_iterator;

    VertexList() = default;
    VertexList(const VertexList&)  = default;
    VertexList(VertexList&&) = default;
    VertexList& operator=(const VertexList&) = default;
    VertexList& operator=(VertexList&&) = default;
    ~VertexList() = default;

    VertexList(std::initializer_list<vec2> vertices);

    void reserve_vertices(list_type::size_type n);
    list_type::size_type size() const;
    list_type& vertices();
    const list_type& vertices() const;

    void add_vertex(vec2 vertex);

    template<typename Iter>
    is_valid_iter<Iter> add_vertices(Iter begin, Iter end);

    list_type::reference operator[](list_type::size_type idx);
    list_type::const_reference operator[](list_type::size_type idx) const;

    iterator begin();
    const_iterator cbegin() const;
    iterator end();
    const_iterator cend() const;

    VertexList& operator*=(mat3x3 mat);

};

VertexList operator*(mat3x3 mat, const VertexList& poly);

std::ostream& operator<<(std::ostream& out, const VertexList& vertices);

// Lazy evaluated composition.
namespace _details
{

    class VertexRange
    {
    private:
        const VertexList& _vertex_list;
        mat3x3 _transformation;
    public:
        VertexRange(const VertexList& list, mat3x3 transformation);

        operator VertexList();

        friend VertexRange operator|(VertexRange range, mat3x3 transformation);

        inline const VertexList& get_list() const { return _vertex_list; }
        inline mat3x3 get_transformation() { return _transformation; }
    };

}

_details::VertexRange operator|(const VertexList& list, mat3x3 transformation);

GFX_GFX2D_END
GFX_END

#undef GFX_GFX2D_BEGIN 
#undef GFX_END 
#undef GFX_GFX2D_END 
#undef GFX_GFX2D_END

#include "VertexList.inl"

#endif