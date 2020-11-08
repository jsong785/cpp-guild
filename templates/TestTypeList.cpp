#include "TypeList.hpp"
#include "catch.hpp"
#include <string>

static_assert(Contains<double, int, double, float, double>());
static_assert(Contains<std::string, double, float, std::string>());
static_assert(!Contains<int, double, float, std::string>());

template <typename... Args>
static constexpr auto UnpackIsOk = std::is_same_v<TypeList<Args...>, decltype(UnpackAndDo<TypeList>(TypeList<Args...>{}))>;

static_assert(UnpackIsOk<int, double>);
static_assert(UnpackIsOk<int, std::string>);

static_assert(UnpackIsOk<int, double>);
static_assert(UnpackIsOk<int, std::string>);

static_assert(std::is_same_v<TypeList<int, double>, decltype(Unique<int, double>())>);
static_assert(std::is_same_v<TypeList<int, double>, decltype(Unique<int, double, double>())>);
static_assert(std::is_same_v<TypeList<int, double>, decltype(Unique<int, int, double, double>())>);
static_assert(std::is_same_v<TypeList<double, int>, decltype(Unique<double, int, int, double, int>())>);

