#pragma once

#include <optional>
#include <vector>

template <typename A, typename Func>
constexpr auto operator|(A, Func);

template <typename T>
using Maybe = std::optional<T>;

template <typename T>
constexpr Maybe<T> Just(T t) {
    return { std::move(t) };
}

template <typename T>
constexpr Maybe<T> Nothing() {
    return {};
}

template <typename A, typename Func>
constexpr auto Mbind(Maybe<A> ma, Func f) -> std::invoke_result_t<Func, A> {
    using ReturnType = std::invoke_result_t<Func, A>;
    static_assert(std::is_same_v<ReturnType, Maybe<typename ReturnType::value_type>>);
    if(ma) {
        return std::invoke(f, std::move(*ma));
    }
    return {};
}

template <typename T>
using List = std::vector<T>;

template <typename A, typename Func>
constexpr auto Mbind(List<A> ma, Func f) -> std::invoke_result_t<Func, A> {
    using ReturnType = std::invoke_result_t<Func, A>;
    static_assert(std::is_same_v<ReturnType, List<typename ReturnType::value_type>>);

    ReturnType other;
    if(!ma.empty()) {
        other.reserve(ma.size());

        for(auto&& m : ma) {
            auto res = std::invoke(f, decltype(m)(m));
            other.insert(other.end(), std::make_move_iterator(res.begin()), std::make_move_iterator(res.end()));
        }
    }
    return other;
}

template <typename A, typename Func>
constexpr auto operator|(A ma, Func f) {
    return Mbind(std::move(ma), std::move(f));
}

