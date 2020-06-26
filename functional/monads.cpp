#include "catch.hpp"
#include "monads.hpp"

#include <string>

TEST_CASE("Maybe", "[monads]")
{
    SECTION("Just")
    {
        static_assert(Just(1) == Maybe<int>{ 1 });
        CHECK(Just(std::string{ "something" }) == Maybe<std::string>{ "something" });
    }

    SECTION("Nothing")
    {
        static_assert(Nothing<int>() == Maybe<int>{});
        CHECK(Nothing<std::string>() == Maybe<std::string>{});
    }

    constexpr auto addOne = [](const int x) -> Maybe<int> {
        return x + 1;
    };
    const auto toString = [](const auto x) -> Maybe<std::string> {
        return std::to_string(x);
    };

    SECTION("MBind")
    {
        CHECK(Mbind(Just(10), addOne) == Just(11));
        CHECK(Mbind(Nothing<int>(), addOne) == Nothing<int>());

        CHECK(Mbind(Just(123), toString) == Just(std::string{ "123" }));
        CHECK(Mbind(Nothing<int>(), toString) == Nothing<std::string>());
        static_assert(Mbind(Nothing<int>(), addOne) == Nothing<int>());
    }

    SECTION("Chaining")
    {
        CHECK((Just(11) | addOne | toString) == Just(std::string{ "12" }));
        CHECK((Just(100) | addOne | toString) == Just(std::string{ "101" }));

        CHECK((Nothing<int>() | addOne | toString) == Nothing<std::string>());
        static_assert((Nothing<int>() | addOne) == Nothing<int>());
    }
}

TEST_CASE("List", "[monads]")
{
    const auto doubleEntry = [](const auto x) -> List<int> {
        return { x, x };
    };

    const auto toString = [](const auto x) -> List<std::string> {
        return { std::to_string(x) };
    };

    CHECK((List<int>{1, 2, 3} | doubleEntry) == List<int>{ 1, 1, 2, 2, 3, 3 });
    CHECK((List<int>{1, 2, 3} | doubleEntry | toString) == 
            List<std::string>{ "1", "1", "2", "2", "3", "3" });

    CHECK((List<int>{} | doubleEntry | toString) == List<std::string>{});
}

TEST_CASE("Continuation", "[monads]")
{
}

