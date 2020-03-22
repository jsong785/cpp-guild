#pragma once

template <typename... T>
auto Add(T... t) {
    return (t + ...);
}

template <typename T,
    typename = std::enable_if_t<std::is_integral_v<T>>>
auto Subtract(T a, T b) {
    return a-b;
}

template <typename T>
auto Subtract(T a, T b)
    -> decltype((void)(a.size()), std::size_t{})
{
    return a.size() - b.size();
}

template <typename T>
auto Subtract(T a, T b) ->
    decltype((void)(a.val), decltype(std::declval<T>().val){})
{
    return a - b;
}

