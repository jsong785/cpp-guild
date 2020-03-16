#pragma once
#include <vector>
#include <sstream>

template <typename... T>
std::stringstream ConcatStream(T... args) {
    std::stringstream stream;
    (stream << ... << args);
    return stream;
}

template <typename... T>
std::stringstream ConcatDoubleStream(T... args) {
    return ConcatStream((args+args)...);
}

namespace details {

template <typename A, typename Item, typename... Items>
void FilterHelper(A& retVector, Item item, Items... items) {
    retVector.emplace_back(std::move(item));
    if constexpr(sizeof...(items) > 0) {
        FilterHelper(retVector, items...);
    }
}

}

template <typename T, typename... Indices>
std::vector<T> Filter(const std::vector<T> &list, Indices... indices) {
    std::vector<T> ret;
    ret.reserve( sizeof...(indices) );
    details::FilterHelper(ret, list[indices]...);
    return ret;
}
