#pragma once

#include <string>
#include <tuple>
#include <type_traits>

template <std::size_t N, typename T>
struct tuple_n {
    template <typename... Args>
    using type = typename tuple_n<N-1, T>::template type<T, Args...>;
};

template <typename T>
struct tuple_n<0, T> {
    template <typename... Args>
    using type = std::tuple<Args...>;
};

template <std::size_t N, typename T>
using CreateTupleN = typename tuple_n<N, T>::template type<>;

static_assert(std::is_same_v<CreateTupleN<3, double>, std::tuple<double, double, double>>);
static_assert(std::is_same_v<CreateTupleN<2, double>, std::tuple<double, double>>);
static_assert(std::is_same_v<CreateTupleN<1, double>, std::tuple<double>>);
static_assert(std::is_same_v<CreateTupleN<0, double>, std::tuple<>>);

template <std::size_t I, typename T, typename Tuple>
constexpr auto TokenizeHelper(T&& equation, Tuple&& data) {
    std::get<I>(data) = equation[I] - '0';
    if constexpr(I > 0) {
        TokenizeHelper<I-1>(std::forward<T>(equation), std::forward<Tuple>(data));
    }
}

template <std::size_t N>
constexpr auto Tokenize(const char(&equation)[N]) {
    CreateTupleN<N-1, int8_t> tuple{};
    TokenizeHelper<N-2>(equation, tuple);
    return tuple;
}
static_assert(Tokenize("981") == std::tuple<int8_t, int8_t, int8_t>{9, 8, 1});
static_assert(Tokenize("1010") == CreateTupleN<4, int8_t>{1, 0, 1, 0});

template <typename... Args>
constexpr auto Parse(const std::tuple<Args...>& data) {
    int64_t val{ 1 };
    for(std::size_t i{ 1 }; i < sizeof...(Args); ++i) {
    }
    return val;
}
static_assert(Parse(Tokenize("981")) == 1);

