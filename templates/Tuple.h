#pragma once

#include <tuple>
#include <type_traits>

namespace details {

template <std::size_t Index, typename Callable, typename ...Args>
void TransformTupleHelper(std::tuple<Args...> &tuple, Callable c)
{
    if constexpr(Index < std::tuple_size<std::decay_t<decltype(tuple)>>::value) {
	std::get<Index>(tuple) = c(std::get<Index>(tuple));
	TransformTupleHelper<Index+1>(tuple, std::forward<Callable>(c));
    }
}

}


template <typename Callable, typename ...Args>
void TransformTuple(std::tuple<Args...> &tuple, Callable c)
{
	details::TransformTupleHelper<0>(tuple, std::move(c));
}

