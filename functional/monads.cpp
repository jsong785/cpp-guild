#include "catch.hpp"
#include "monads.hpp"

#include <utility>
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

    SECTION("Applicative")
    {
        constexpr auto AddOneConcrete = [](const int x) -> int {
            return x + 1;
        };
        using FuncType = std::function<int(const int)>;
        CHECK((Nothing<FuncType>() >> Just(1)) == Nothing<int>());
        CHECK((Just<FuncType>(AddOneConcrete) >> Nothing<int>()) == Nothing<int>());
        CHECK((Just<FuncType>(AddOneConcrete) >> Just(1)) == Just(2));

        constexpr auto GetSomethingIfAboveThree = [AddOneConcrete](const auto x) -> Maybe<FuncType> {
            if(x > 3) {
                return AddOneConcrete;
            }
            return {};
        };
        CHECK((GetSomethingIfAboveThree(2) >> Just(10)) == Nothing<int>());
        CHECK((GetSomethingIfAboveThree(4) >> Just(10)) == Just(11));

        // including mbind
        CHECK((GetSomethingIfAboveThree(2) >> Just(10) | addOne | toString) == Nothing<std::string>());
        CHECK((GetSomethingIfAboveThree(4) >> Just(10) | addOne | toString) == Just(std::string{ "12" }));
    }
}

TEST_CASE("List", "[monads]")
{
    const auto doubleValue = [](const auto x) -> List<int> {
        return { x, x };
    };

    const auto toString = [](const auto x) -> List<std::string> {
        return { std::to_string(x) };
    };

    SECTION("Chaining")
    {
        CHECK((List<int>{1, 2, 3} | doubleValue) == List<int>{ 1, 1, 2, 2, 3, 3 });
        CHECK((List<int>{1, 2, 3} | doubleValue | toString) == 
                List<std::string>{ "1", "1", "2", "2", "3", "3" });

        CHECK((List<int>{} | doubleValue | toString) == List<std::string>{});
    }

    SECTION("Applicative")
    {
        const auto doubleValueConcrete = [](const int x) -> int {
            return x*2;
        };
        using FuncType = std::function<int(int)>;
        CHECK((List<FuncType>{} >> List<int>{ 1, 2, 3}) == List<int>{});
        CHECK((List<FuncType>{ doubleValueConcrete } >> List<int>{ 1, 2, 3}) == List<int>{ 2, 4, 6 });

        constexpr auto GetSomethingIfAboveThree = [doubleValueConcrete](const auto x) -> List<FuncType> {
            if(x > 3) {
                return { doubleValueConcrete };
            }
            return {};
        };
        CHECK((GetSomethingIfAboveThree(2) >> List<int>{ 1, 2, 3 }) == List<int>{});
        CHECK((GetSomethingIfAboveThree(4) >> List<int>{ 1, 2, 3 }) == List<int>{ 2, 4, 6 });

        // including mbind
        CHECK((GetSomethingIfAboveThree(2) >> List<int>{ 1, 2, 3 } | doubleValue | toString) == List<std::string>{});
        CHECK((GetSomethingIfAboveThree(4) >> List<int>{ 1, 2, 3 } | doubleValue | toString) == List<std::string>{ "2", "2", "4", "4", "6", "6" });
    }
}

namespace TestSomeMonadLaws { 
using ResultPair = std::pair<int64_t, std::string>;

template <typename Func>
auto Bind(ResultPair result, Func f) {
    auto res = std::invoke(f, result.first);
    if(!res.second.empty()) {
        return decltype(result)(res);
    }
    return decltype(result){ res.first, std::move(result.second) };
}

template <typename Func>
auto operator|(ResultPair res, Func f) {
    return Bind(std::move(res), std::move(f));
}

ResultPair Just(const int64_t val) { return { val, {}}; }

ResultPair TestFunc1(const int64_t val) {
    if(val < 0) {
        return { 0, "negative" };
    }
    return { val, {} };
}

ResultPair TestFunc2(const int64_t val) {
    if(val < 0) {
        return { 0, {} };
    }
    return { val, "duper" };
}

TEST_CASE("Bleh", "[testme]") 
{
    // law 1
    CHECK((Just(int64_t{-1}) | TestFunc1) == TestFunc1(-1));
    CHECK((Just(int64_t{2}) | TestFunc1) == TestFunc1(2));

    CHECK((Just(int64_t{-1}) | TestFunc2) == TestFunc2(-1));
    CHECK((Just(int64_t{2}) | TestFunc2) == TestFunc2(2));

    // law 2
    CHECK((ResultPair{-1, {}} | Just) == ResultPair{-1, {}});
    CHECK((ResultPair{1, {}} | Just) == ResultPair{1, {}});
    CHECK((ResultPair{1, "something"} | Just) == ResultPair{1, "something"});
    CHECK((ResultPair{-1, "something"} | Just) == ResultPair{-1, "something"});

    auto res = (ResultPair{-1, {}} | TestFunc1) | TestFunc2;
    auto res2 = ResultPair{-1, {}} | [](const int64_t x){ return TestFunc1(x) | TestFunc2; };
    CHECK(res == res2);

    res = (ResultPair{-1, "whatever"} | TestFunc1) | TestFunc2;
    res2 = ResultPair{-1, "whatever"} | [](const int64_t x){ return TestFunc1(x) | TestFunc2; };
    CHECK(res == res2);

    res = (ResultPair{1, "whatever"} | TestFunc1) | TestFunc2;
    res2 = ResultPair{1, "whatever"} | [](const int64_t x){ return TestFunc1(x) | TestFunc2; };
    CHECK(res == res2);
}

}


