#ifndef JGRAPHICS_2D_DATA_LIST_HPP
#define JGRAPHICS_2D_DATA_LIST_HPP

#include <vector>
#include <ostream>
#include <initializer_list>
#include <iterator>
#include <tuple>

#include "math/Vec.hpp"
#include "math/Matrix.hpp"

#define GFX_BEGIN namespace gfx {
#define GFX_GFX2D_BEGIN namespace GFX2D {
#define GFX_END }
#define GFX_GFX2D_END }

GFX_BEGIN
GFX_GFX2D_BEGIN

// An abstraction of the VectorList. Allows additional data to be appended.
template<unsigned N, typename... Ts>
class DataList
{
public:
    using value_type = std::tuple<vec<N, double>, Ts...>;
    using list_type = std::vector<value_type>;
private:
    list_type _data;

    template<typename Iter>
    using is_valid_iter = std::enable_if_t<std::is_same_v<typename std::iterator_traits<Iter>::value_type, value_type>>;
public:
    using iterator = list_type::iterator;
    using const_iterator = list_type::const_iterator;

    DataList() = default;
    DataList(const DataList&) = default;
    DataList(DataList&&) = default;
    DataList& operator=(const DataList&) = default;
    DataList& operator=(DataList&&) = default;
    ~DataList() = default;

    DataList(std::initializer_list<value_type> data);

    void reserve_data(typename list_type::size_type n);
    typename list_type::size_type size() const;
    list_type& data();
    const list_type& data() const;

    void push_datum(value_type&& datum);

    template<typename Iter>
    is_valid_iter<Iter> push_data(Iter begin, Iter end);

    typename list_type::reference operator[](typename list_type::size_type idx);
    typename list_type::const_reference operator[](typename list_type::size_type idx) const;

    iterator begin();
    const_iterator cbegin() const;
    iterator end();
    const_iterator cend() const;

    DataList& operator*=(matrix<N, N, double> mat);
};

// CTAD guide
template<unsigned N, typename... Ts>
DataList(std::initializer_list<std::tuple<vec<N, double>, Ts...>>) -> DataList<N, Ts...>;

template<unsigned N, typename... Ts>
DataList<N, Ts...>& operator*(matrix<N, N, double> mat, const DataList<N, Ts...>& data);

GFX_GFX2D_END
GFX_END

#undef GFX_GFX2D_BEGIN 
#undef GFX_END 
#undef GFX_GFX2D_END 
#undef GFX_GFX2D_END

#include "DataList.inl"

#endif