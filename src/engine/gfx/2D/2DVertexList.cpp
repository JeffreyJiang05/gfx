#include "gfx/2D/VertexList.hpp"

#include <algorithm>

namespace gfx::GFX2D {

    VertexList::VertexList(std::initializer_list<vec2> vertices) : _vertices{} 
    {
        _vertices.reserve(vertices.size());
        for (auto&& vertex : vertices)
        {
            _vertices.push_back(vec3{ vertex, 1 });
        }
    }

    void VertexList::reserve_vertices(list_type::size_type n)
    {
        _vertices.reserve(n);
    }

    auto VertexList::size() const -> list_type::size_type
    {
        return _vertices.size();
    }

    auto VertexList::vertices() -> list_type&
    {
        return _vertices;
    }

    auto VertexList::vertices() const -> const list_type&
    {
        return _vertices;
    }

    void VertexList::add_vertex(vec2 vertex)
    {
        _vertices.push_back(vec3{ vertex, 1 });
    }

    auto VertexList::operator[](list_type::size_type idx) -> list_type::reference
    {
        return _vertices[idx];
    }

    auto VertexList::operator[](list_type::size_type idx) const -> list_type::const_reference
    {
        return _vertices[idx];
    }

    auto VertexList::begin() -> iterator
    {
        return std::begin(_vertices);
    }

    auto VertexList::cbegin() const -> const_iterator
    {
        return std::cbegin(_vertices);
    }

    auto VertexList::end() -> iterator
    {
        return std::end(_vertices);
    }

    auto VertexList::cend() const -> const_iterator
    {
        return std::cend(_vertices);
    }

    VertexList& VertexList::operator*=(mat3x3 mat)
    {
        for (auto&& vertex : _vertices)
        {
            vertex = mat * vertex;
        }
        return *this;
    }

    VertexList operator*(mat3x3 mat, const VertexList& poly)
    {
        VertexList res;
        res.reserve_vertices(poly.size());
        for (auto&& vertex : poly.vertices())
        {
            res.vertices().push_back(mat * vertex);
        }
        return res;
    }

    std::ostream& operator<<(std::ostream& out, const VertexList& vertices)
    {
        out << "[";
        for (VertexList::list_type::size_type i = 0; i < vertices.size(); ++i)
        {
            out << vertices[i];
            if (i != vertices.size() - 1)
            {
                out << ",";
            }             
        }
        return out << "]";
    }

    namespace _details
    {
        VertexRange::VertexRange(const VertexList& list, mat3x3 transformation) : _vertex_list{ list }, _transformation{ transformation } { }

        VertexRange::operator VertexList()
        {
            VertexList res;
            res.reserve_vertices(_vertex_list.size());
            for (auto&& vertex : _vertex_list.vertices())
            {
                res.vertices().push_back(_transformation * vertex);
            }
            return res;
        }

        VertexRange operator|(VertexRange range, mat3x3 transformation)
        {
            return { range._vertex_list, transformation * range._transformation };
        }

    }

    _details::VertexRange operator|(const VertexList& list, mat3x3 transformation)
    {
        return { list, transformation };
    }

}