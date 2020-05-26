#include "catch.hpp"
#include "fmap.hpp"

// identity law for fmap
static_assert(id(1) == 1);
static_assert(id(2.0) == 2.0);

constexpr auto func = [](){};
static_assert(id(func) == func);

constexpr auto func2 = [](){ return 1; };
static_assert(id(func2) == func2);

TEST_CASE("fmap optional", "[fmap]")
{
    SECTION("identity")
    {
        CHECK(fmap<int, int, Maybe<int, int>>(id<int>)(std::optional<int>{1}) == std::optional<int>{1});
        CHECK(fmap<int, int, Maybe<int, int>>(id<int>)(std::optional<int>{}) == std::optional<int>{});
    }

    SECTION("associative")
    {
        constexpr auto charToStringThree = [](const auto c){ return std::string{c, c, c}; };
        constexpr auto stringToLen = [](const auto &s){ return s.size(); };
        CHECK(fmap<char, std::size_t, Maybe<char, std::size_t>>([stringToLen, charToStringThree](const auto c){
            return stringToLen(charToStringThree(c));
        })(std::optional<char>{'a'}) == 3);
        CHECK_FALSE(fmap<char, std::size_t, Maybe<char, std::size_t>>([stringToLen, charToStringThree](const auto c){
            return stringToLen(charToStringThree(c));
        })(std::optional<char>{}));

        auto first = fmap<char, std::string, Maybe<char, std::string>>(charToStringThree)(std::optional{'w'});
        auto second = fmap<std::string, std::size_t, Maybe<std::string, std::size_t>>(stringToLen)(first);
        CHECK(*second == 3);

        first = fmap<char, std::string, Maybe<char, std::string>>(charToStringThree)(std::optional<char>{});
        second = fmap<std::string, std::size_t, Maybe<std::string, std::size_t>>(stringToLen)(first);
        CHECK_FALSE(second);
    }

    SECTION("regular testing")
    {
        constexpr auto doubleVal = [](const auto n){ return n * 2; };
        CHECK(*fmap<int, int, Maybe<int, int>>(doubleVal)(std::optional<int>{1}) == 2);
        CHECK_FALSE(fmap<int, int, Maybe<int, int>>(doubleVal)(std::optional<int>{}));

        constexpr auto charToStringThree = [](const auto c){ return std::string{c, c, c}; };
        CHECK(*fmap<char, std::string, Maybe<char, std::string>>(charToStringThree)(std::optional<char>{'c'}) == "ccc");
        CHECK_FALSE(fmap<char, std::string, Maybe<char, std::string>>(charToStringThree)(std::optional<char>{}));
    }
}

