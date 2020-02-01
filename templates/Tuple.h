#pragma once

#include <tuple>
#include <type_traits>

template <std::size_t Index, typename Callable, typename ...Args>
std::enable_if_t<Index >= std::tuple_size<std::tuple<Args...>>::value, void> TransformTupleHelper(std::tuple<Args...> &tuple, Callable &&c)
{
}

template <std::size_t Index, typename Callable, typename ...Args>
std::enable_if_t<Index < std::tuple_size<std::tuple<Args...>>::value, void> TransformTupleHelper(std::tuple<Args...> &tuple, Callable &&c)
{
    std::get<Index>(tuple) = c(std::get<Index>(tuple));
    TransformTupleHelper<Index+1>(tuple, c);
}


template <typename Callable, typename ...Args>
void TransformTuple(std::tuple<Args...> &tuple, Callable &&c)
{
    TransformTupleHelper<0>(tuple, c);
}

