#pragma once

#include <optional>

template <typename T>
struct MaybeMonad
{
    static std::optional<T> Construct() {
        return {};
    }

    static std::optional<T> Unit(T &&t) {
        return std::optional<T>{ std::forward<decltype(t)>(t) };
    }

};

