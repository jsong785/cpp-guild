#pragma once

#include <functional>
#include <optional>
#include <type_traits>

template <typename T>
constexpr T id(T&& arg) {
    return std::forward<T>(arg);
}

namespace details {

template <typename A, typename B>
using AtoBFunc = std::function<B(A)>;

}

template <typename A, typename B>
struct Maybe {
    using MaybeA = std::optional<A>;
    using MaybeB = std::optional<B>;
};

template <typename A, typename B, typename F>
constexpr auto fmap(details::AtoBFunc<A, B> func) 
{
    return [f = std::move(func)](typename Maybe<A, B>::MaybeA val) -> typename Maybe<A, B>::MaybeB {
        if(val) {
            return f(*val);
        }
        return {};
    };
}

template <typename A, typename B, Maybe<A, B>>
constexpr auto fmap(details::AtoBFunc<A, B> func) 
{
    return [f = std::move(func)](typename Maybe<A, B>::MaybeA val) -> typename Maybe<A, B>::MaybeB {
        if(val) {
            return f(*val);
        }
        return {};
    };
}

