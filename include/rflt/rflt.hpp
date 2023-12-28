#ifndef RFLT_HPP
#define RFLT_HPP

/**
 * rudimentary reflection implemented in c++ for basic aggregate structs.
 * 
 * defined functions, metafunctions, alias templates, value templates, etc.
 * 
 * FUNCTIONS:
 * 
 * get<N>(s) -> the `N`th field of instance `s` of struct `decltype(s)`.
 * 
 * tupify(s) -> the tuple containing the data of the fields in instance `s` of struct `decltype(s)`.
 * 				if `s` is a lvalue, the tuple elements are references to the fields of `s`.
 * 				if `s` is a rvalue, the tuple elements are values of the fields of `s`.
 * 			
 * to_string(s) -> string representing all the data in instance `s` of struct `decltype(s)` that 
 * 				   has an overloaded `std::ostream& operator<<(std::ostream&, const T&)`
 * 
 * for_each(s, func) -> void. Performs function on each of the fields of instance `s` of struct
 * 						`decltype(s)`. Note: only has observable effect if `s` is an lvalue.
 * 
 * accumulate<R>(s, init, bifunc) -> decltype(init). Accumulates each field of the instance `s`
 * 									 of the struct `decltype(s)` based on `bifunc`. `bifunc` 
 * 									 accepts `decltype(init)` and the data in the field of instance
 * 									 `s`. It returns `decltype(init)`. `init` is the initial value
 * 									 of the accumulation. 
 * 
 * visit_all<T>(s, func) -> void. Performs `func` only on data with fields in instance `s` of struct
 * 							`decltype(s)` that has base type `T`. `func` accepts `T&` to modify.
 * 
 * visit_first<T>(s, func) -> void. Performs `func` only on the first datum with field in instance `s`
 * 							  of struct `decltype(s)` that has base type `T`. `func` accepts `T&` to
 * 							  modify
 * 
 * ALIAS:
 * 
 * nth_field<S, N> -> the type of the `N`th field of struct `S`
 * 
 * CONSTANTS:
 * 
 * total_fields<S> -> the total number of fields of struct `S`
 * 
*/


#include <type_traits>
#include <tuple>
#include <utility>
#include <cmath>
#include <sstream>

#define RFLT_NAMESPACE_BEGIN namespace rflt {
#define RFLT_NAMESPACE_END }

RFLT_NAMESPACE_BEGIN

constexpr std::size_t MAX_FIELDS = 100;

namespace _details
{

	template<std::size_t Index>
	struct Any
	{
		template<typename T> constexpr operator T&() const;
	};

	template<typename T>
	constexpr std::size_t calculate_max_size()
	{
		return std::min(sizeof(T) * sizeof(char) * 8, MAX_FIELDS);
	}

	template<typename T, std::size_t... Indices, typename Enable = decltype(T{ Any<Indices>{}... })>
	std::true_type is_constructible_with_helper(std::index_sequence<Indices...> indices, int);

	template<typename T, std::size_t... Indices>
	std::false_type is_constructible_with_helper(std::index_sequence<Indices...> indices, ...);

	template<typename T, std::size_t Elements>
	using is_constructible_with = decltype(is_constructible_with_helper<T>(std::make_index_sequence<Elements>{}, 0));

	template<typename T, std::size_t Elements>
	constexpr inline bool is_constructible_with_v = is_constructible_with<T, Elements>::value;

	/* <-----| Lazy binary search (For when T can be default initialized) |-----> */

	template<typename T, std::size_t Begin, std::size_t End>
	constexpr std::size_t lazy_binary_search()
	{
		constexpr std::size_t Mid = (Begin + End) / 2;
		if constexpr(Begin == End - 1)
		{
			return Begin;
		}
		else if constexpr(is_constructible_with_v<T, Mid>)
		{
			return lazy_binary_search<T, Mid, End>();
		}
		else
		{
			return lazy_binary_search<T, Begin, Mid>();
		}
	}

	/* <-----| Eager binary search (For when T cannot be default initialized) |------> */

	template<typename T, std::size_t N>
	constexpr std::enable_if_t<is_constructible_with_v<T, N>, std::size_t> check_valid_index(int)
	{
		return N;
	}

	template<typename T, std::size_t N>
	constexpr std::size_t check_valid_index(...)
	{
		return 0;
	}

	template<typename T, std::size_t Begin, std::size_t End>
	constexpr std::size_t greedy_binary_search()
	{
		if constexpr(Begin == End - 1)
		{
			return check_valid_index<T, Begin>(0);
		}
		constexpr std::size_t Mid = (Begin + End) / 2;
		return std::max(greedy_binary_search<T, Begin, Mid>(), greedy_binary_search<T, Mid, End>());
	}

	/* Determine whether to use lazy or greedy */

	// can employ lazy binary search (aka can be default constructed)
	template<typename T>
	constexpr std::enable_if_t<std::is_default_constructible_v<T>, std::size_t> count_fields_helper(int)
	{
		if constexpr(!std::is_aggregate_v<T>) return 0;
		return lazy_binary_search<T, 0, calculate_max_size<T>()>();
	}

	// otherwise employ greedy binary search
	template<typename T>
	constexpr std::size_t count_fields_helper(...)
	{
		return greedy_binary_search<T, 0, calculate_max_size<T>()>();
	}

	/* Turn references into tuple */
	template<typename T, typename... Ts>
	auto make_tuple_from_args(Ts&&... refs) -> std::enable_if_t<std::is_lvalue_reference_v<T>, std::tuple<Ts...>>
	{
		return { std::forward<Ts>(refs)... };
	}

	template<typename T, typename... Ts>
	auto make_tuple_from_args(Ts&&... args) -> std::enable_if_t<!std::is_lvalue_reference_v<T>, std::tuple<std::remove_reference_t<Ts>...>>
	{
		return { args... };
	}

	template<typename T>
	constexpr std::enable_if_t<std::is_aggregate_v<T>, std::size_t> count_fields()
	{
		return _details::count_fields_helper<T>(0);
	}

	/* Turns structs to tuples */
	template<typename T>
	constexpr auto make_tuple_from_struct(T&& val);

}

#include "tuple_generated.inl"

template<typename T, std::size_t N>
using nth_field = std::tuple_element_t<N, decltype(_details::make_tuple_from_struct(std::declval<std::remove_reference_t<T>>()))>;

template<typename T>
constexpr inline std::size_t total_fields = _details::count_fields<std::remove_reference_t<T>>();

template<std::size_t N, typename T, typename Enable = std::enable_if<std::is_aggregate_v<std::remove_reference_t<T>>>>
decltype(auto) get(T&& t)
{
	return std::get<N>(_details::make_tuple_from_struct(std::forward<T>(t)));
}

namespace _details
{
	template<typename T, typename Enable = std::void_t<>>
	struct is_ostream_defined : public std::false_type {};

	template<typename T>
	struct is_ostream_defined<T, std::void_t<decltype(std::declval<std::ostream>() << std::declval<T>())>> : public std::true_type {};

	template<typename T>
	constexpr inline bool is_ostream_defined_v = is_ostream_defined<T>::value;  

	template<typename T, std::size_t... Indices>
	std::enable_if_t<std::is_aggregate_v<std::remove_reference_t<T>>> print_aggregate_with_tuple(T&& val, std::stringstream& ss, std::index_sequence<Indices...>);

	template<typename T>
	std::enable_if_t<is_ostream_defined_v<std::remove_reference_t<T>>> print_printable(T&& val, std::stringstream& ss)
	{
		ss << val;
	}

	template<typename T>
	std::enable_if_t<!is_ostream_defined_v<std::remove_reference_t<T>> && !std::is_aggregate_v<T>> print_null(T&& val, std::stringstream& ss)
	{
		ss << " ";
	}

	template<typename T>
	void print_value(T&& value, std::stringstream& ss)
	{
		if constexpr(is_ostream_defined_v<std::remove_reference_t<T>>)
		{
			print_printable<T>(std::forward<T>(value), ss);
		}
		else if constexpr(std::is_aggregate_v<std::remove_reference_t<T>>)
		{
			print_aggregate_with_tuple<T>(std::forward<T>(value), ss, std::make_index_sequence<total_fields<T>>{});
		}
		else
		{
			print_null<T>(std::forward<T>(value), ss);
		}
	}

	template<typename T, std::size_t... Indices>
	std::enable_if_t<std::is_aggregate_v<std::remove_reference_t<T>>> print_aggregate_with_tuple(T&& val, std::stringstream& ss, std::index_sequence<Indices...>)
	{
		auto tup = make_tuple_from_struct<T>(std::forward<T>(val));
		using tuple_t = decltype(tup);

		ss << "{";
		using sink = int[];
		(void) sink{ 0, ( void(ss << (Indices == 0 ? "" : ", ")), print_value<std::tuple_element_t<Indices, tuple_t>>(
			std::forward<std::tuple_element_t<Indices, tuple_t>>(std::get<Indices>(tup)),
			ss
		), 0 )... };
		ss << "}";
	}

	template<typename T, typename Func, std::size_t... Indices>
	void for_each_helper(T&& value, Func&& func, std::index_sequence<Indices...>)
	{
		auto tup = make_tuple_from_struct<T>(std::forward<T>(value));
		using sink = int[];
		(void) sink{ 0, ( std::forward<Func>(func)(std::get<Indices>(tup)), 0 )... };
	}

	template<typename R, typename T, typename BiFunc, std::size_t... Indices>
	R accumulate_helper(T&& value, R init, BiFunc&& func, std::index_sequence<Indices...>)
	{
		R val{ init };
		auto tup = make_tuple_from_struct<T>(std::forward<T>(value));
		using sink = int[];
		(void) sink{ 0, ( void( val = std::forward<BiFunc>(func)( val, std::get<Indices>(tup) ) ), 0)... };
		return val;
	}

	template<typename Target, typename Select, typename Vis>
	std::enable_if_t<std::is_same_v<Target, std::remove_reference_t<Select>>> attempt_visit(Select&& selected, Vis&& vis)
	{
		std::forward<Vis>(vis)(std::forward<Select>(selected));
	}

	// do nothing
	template<typename Target, typename Select, typename Vis>
	std::enable_if_t<!std::is_same_v<Target, std::remove_reference_t<Select>>> attempt_visit(Select&& selected, Vis&& vis) {}

	template<typename Target, typename T, typename Vis, std::size_t... Indices>
	void visit_all_helper(T&& t, Vis&& vis, std::index_sequence<Indices...>)
	{
		auto tup = make_tuple_from_struct<T>(std::forward<T>(t));
		using sink = int[];
		(void) sink{ 0, ( attempt_visit<Target>(std::get<Indices>(tup), std::forward<Vis>(vis)) , 0 )... };
	}

	template<typename TupleT, typename T, std::size_t Index = 0, bool SizeCheck = (Index < std::tuple_size_v<TupleT>), bool Test = std::is_same_v< std::remove_reference_t<T>, std::remove_reference_t<std::tuple_element_t<Index, TupleT>>>>
	struct get_index_of_T : get_index_of_T<TupleT, T, Index + 1> {};

	template<typename TupleT, typename T, std::size_t Index>
	struct get_index_of_T<TupleT, T, Index, true, true>
	{
		constexpr static std::size_t value = Index;
		constexpr static bool exist = true;
	};

	template<typename TupleT, typename T, std::size_t Index, bool Test>
	struct get_index_of_T<TupleT, T, Index, false, Test>
	{
		constexpr static bool exist = false;
	};

	template<typename Tuple, typename T>
	constexpr inline bool tuple_contains_T = get_index_of_T<Tuple, T>::exist;

	template<typename Tuple, typename T>
	constexpr inline std::size_t get_index_of_T_v = get_index_of_T<Tuple, T>::value;

}

template<typename T>
std::string to_string(T&& t)
{
	std::stringstream sstream;
	_details::print_aggregate_with_tuple<T>(std::forward<T>(t), sstream, std::make_index_sequence<total_fields<T>>{});
	return sstream.str();
}

template<typename T, typename Func>
void for_each(T&& t, Func&& func)
{
	constexpr std::size_t size = total_fields<std::remove_reference_t<T>>;
	using indices = std::make_index_sequence<size>;

	_details::for_each_helper<T, Func>(std::forward<T>(t), std::forward<Func>(func), indices{});
}

template<typename R, typename T, typename BiFunc>
R accumulate(T&& t, R init, BiFunc&& func)
{
	constexpr std::size_t size = total_fields<std::remove_reference_t<T>>;
	using indices = std::make_index_sequence<size>;

	return _details::accumulate_helper<R, T, BiFunc>(std::forward<T>(t), init, std::forward<BiFunc>(func), indices{});
}

template<typename Target, typename T, typename Vis>
std::enable_if_t<std::is_invocable_v<Vis, Target&>> visit_all(T&& t, Vis&& vis)
{
	constexpr std::size_t size = total_fields<std::remove_reference_t<T>>;
	using indices = std::make_index_sequence<size>;

	_details::visit_all_helper<Target, T, Vis>(std::forward<T>(t), std::forward<Vis>(vis), indices{});
}

template<typename Target, typename T, typename Vis>
std::enable_if_t<std::is_invocable_v<Vis, std::remove_reference_t<Target>&> && _details::tuple_contains_T<decltype(_details::make_tuple_from_struct(std::declval<T>())), Target>> visit_first(T&& t, Vis&& vis)
{
	auto tup = _details::make_tuple_from_struct(std::forward<T>(t));
	constexpr std::size_t idx = _details::get_index_of_T_v<decltype(tup), Target>;
	vis(std::get<idx>(tup));
}

template<typename T, typename Enable = std::enable_if_t<std::is_aggregate_v<std::remove_reference_t<T>>>>
auto tupify(T&& t)
{
	return _details::make_tuple_from_struct(std::forward<T>(t));
}

/* template<typename Condition, typename T, typename Vis>
void visit_all_if(T&& t, Vis&& vis)
{

} */

RFLT_NAMESPACE_END

#undef RFLT_NAMESPACE_BEGIN
#undef RFLT_NAMESPACE_END

#endif	