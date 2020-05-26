#include "catch.hpp"
#include "fmap.hpp"

static_assert(id(1) == 1);
static_assert(id(2.0) == 2.0);

constexpr auto func = [](){};
static_assert(id(func) == func);

constexpr auto func2 = [](){ return 1; };
static_assert(id(func2) == func2);

TEST_CASE("fmap optional", "[fmap]")
{
    constexpr auto doubleVal = [](const auto n){ return n * 2; };
    CHECK(*fmap<int, int, Maybe<int, int>>(doubleVal)(std::optional<int>{1}) == 2);
    CHECK_FALSE(fmap<int, int, Maybe<int, int>>(doubleVal)(std::optional<int>{}));

    constexpr auto charToStringThree = [](const auto c){ return std::string{c, c, c}; };
    CHECK(*fmap<char, std::string, Maybe<char, std::string>>(charToStringThree)(std::optional<char>{'c'}) == "ccc");
    CHECK_FALSE(fmap<char, std::string, Maybe<char, std::string>>(charToStringThree)(std::optional<char>{}));
}

