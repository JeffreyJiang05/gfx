#include "DataList.hpp"

#define GFX_BEGIN namespace gfx {
#define GFX_GFX2D_BEGIN namespace GFX2D {
#define GFX_END }
#define GFX_GFX2D_END }

GFX_BEGIN
GFX_GFX2D_BEGIN

template<unsigned N, typename... Ts>
DataList<N, Ts...>::DataList(std::initializer_list<value_type> data) : _data{}
{
    _data.reserve(data.size());
    for (auto&& vertex : data)
    {
        _data.push_back(std::move(vertex));
    }
}

template<unsigned N, typename... Ts>
void DataList<N, Ts...>::reserve_data(typename list_type::size_type n)
{
    _data.reserve(n);
}

template<unsigned N, typename... Ts>
auto DataList<N, Ts...>::size() const -> typename list_type::size_type
{
    return _data.size();
}

template<unsigned N, typename... Ts>
auto DataList<N, Ts...>::data() -> list_type&
{
    return _data;
}

template<unsigned N, typename... Ts>
auto DataList<N, Ts...>::data() const -> const list_type&
{
    return _data;
}

template<unsigned N, typename... Ts>
void DataList<N, Ts...>::push_datum(value_type&& datum)
{
    _data.push_back(std::move(datum));
}

template<unsigned N, typename... Ts>
template<typename Iter>
auto DataList<N, Ts...>::push_data(Iter begin, Iter end) -> is_valid_iter<Iter>
{
    while (begin != end)
    {
        _data.push_back(*begin);
        ++begin;
    }
}

template<unsigned N, typename... Ts>
auto DataList<N, Ts...>::operator[](typename list_type::size_type idx) -> typename list_type::reference
{
    return _data[idx];
}

template<unsigned N, typename... Ts>
auto DataList<N, Ts...>::operator[](typename list_type::size_type idx) const -> typename list_type::const_reference
{
    return _data[idx];
}

template<unsigned N, typename... Ts>
auto DataList<N, Ts...>::begin() -> iterator
{
    return std::begin(_data);
}

template<unsigned N, typename... Ts>
auto DataList<N, Ts...>::end() -> iterator
{
    return std::end(_data);
}

template<unsigned N, typename... Ts>
auto DataList<N, Ts...>::cbegin() const -> const_iterator
{
    return std::cbegin(_data);
}

template<unsigned N, typename... Ts>
auto DataList<N, Ts...>::cend() const -> const_iterator
{
    return std::cend(_data);
}

template<unsigned N, typename... Ts>
DataList<N, Ts...>& DataList<N, Ts...>::operator*=(matrix<N, N, double> mat)
{
    for (auto&& datum : _data)
    {
        std::get<0>(datum) = mat * std::get<0>(datum);
    }
    return *this;
}

template<unsigned N, typename... Ts>
DataList<N, Ts...> operator*(matrix<N, N, double> mat, const DataList<N, Ts...>& data)
{
    DataList<N, Ts...> res;
    res.reserve_data(data.size());
    for (auto&& datum : data)
    {
        typename DataList<N, Ts...>::value_type cpy{ datum };
        std::get<0>(cpy) = mat * std::get<0>(cpy);
        res.push_datum(std::move(cpy));
    }
    return res;
}

template<unsigned N, typename... Ts>
vec<N, double>& get_vertex(std::tuple<vec<N, double>, Ts...>& datum)
{
    return std::get<0>(datum);
}

GFX_GFX2D_END
GFX_END

#undef GFX_GFX2D_BEGIN 
#undef GFX_END 
#undef GFX_GFX2D_END 
#undef GFX_GFX2D_END