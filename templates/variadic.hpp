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

template <typename T, typename Item, typename... Items>
void FilterHelper(std::vector<T>& vector, Item item0, Items... items) {
    vector.emplace_back(std::move(item0));
    if constexpr(sizeof...(items) > 0) {
        FilterHelper(vector, items...);
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
