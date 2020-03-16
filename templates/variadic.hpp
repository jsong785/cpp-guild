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
