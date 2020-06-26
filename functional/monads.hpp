#pragma once

#include <optional>
#include <vector>

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
constexpr auto operator>>(A ma, Func f) {
    return Mbind(std::move(ma), std::move(f));
}

template <typename AB, typename A>
static constexpr auto Applicative(Maybe<AB> fab, Maybe<A> fa) {
    using ResultType = Maybe<std::invoke_result_t<AB, A>>;
    if(!fab || !fa) {
        return ResultType{};
    }
    return ResultType{ std::invoke(*fab, *fa) };
}

template <typename AB, typename A>
static constexpr auto Applicative(List<AB> fab, List<A> fa) {
    using ResultType = std::invoke_result_t<AB, A>;
    using ResultTypeList = List<ResultType>;
    if(fab.empty() || fa.empty()) {
        return ResultTypeList{};
    }

    ResultTypeList result;
    assert(fa.size() * fab.size() <= std::numeric_limits<typename List<ResultType>::size_type>::max());
    result.reserve(fa.size()*fab.size()); // possibly out of bounds
    for(auto&& f : fab) {
        std::transform(fa.begin(), fa.end(), std::back_inserter(result), f);
    }
    return result;
}

template <typename FAB, typename FA>
static constexpr auto operator>(FAB fab, FA fa) {
    return Applicative(std::move(fab), std::move(fa));
}


