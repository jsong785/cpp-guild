#pragma once

#include <functional>
#include <type_traits>
#include <utility>

template <typename... T>
using TypeList = std::tuple<T...>;

template <typename T>
constexpr bool Contains()
{
    return false;
}

template <typename T, typename Type, typename... Types>
constexpr bool Contains()
{ return std::is_same_v<T, Type> || Contains<T, Types...>();
}

template <template <typename...> typename Object, typename... Args>
constexpr auto UnpackAndDo(const TypeList<Args...>&) noexcept
{
    return Object<Args...>();
}

template <typename T>
constexpr auto Unique(T&& t) noexcept
{
    return t;
}

template <typename Arg, typename... Args, typename... Internal>
constexpr auto Unique(TypeList<Internal...>&& types) noexcept
{
    if constexpr (Contains<Arg, Args...>()) {
        return Unique<Args...>(std::move(types));
    }
    else {
        return Unique<Args...>(TypeList<Internal..., Arg>{});
    }
}

template <typename Arg, typename... Args>
constexpr auto Unique() noexcept
{
    if constexpr (Contains<Arg, Args...>()) {
        return Unique<Args...>(TypeList<>());
    }
    else {
        return Unique<Args...>(TypeList<Arg>{});
    }
}

