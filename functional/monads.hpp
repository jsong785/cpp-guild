#pragma once

#include <optional>

template <typename T>
using Maybe = std::optional<T>;

template <typename T>
constexpr Maybe<T> Just(T t) {
    return std::move(t);
}

template <typename T>
constexpr Maybe<T> Nothing() {
    return {};
}

template <typename A, typename Func>
constexpr auto operator|(Maybe<A> ma, Func f) {
    if(ma) {
    }
    return {};
}

