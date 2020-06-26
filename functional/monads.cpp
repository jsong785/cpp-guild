#include "catch.hpp"
#include "monads.hpp"

#include <string>

template <typename AB, typename A>
static auto Applicative(Maybe<AB> fab, Maybe<A> fa) {
    using ResultType = Maybe<std::invoke_result_t<AB, A>>;
    if(!fab || !fa) {
        return ResultType{};
    }
    return ResultType{ std::invoke(*fab, *fa) };
}

template <typename AB, typename A>
static auto Applicative(List<AB> fab, List<A> fa) {
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
static auto operator>(FAB fab, FA fa) {
    return Applicative(std::move(fab), std::move(fa));
}


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
        CHECK((Just(11) >> addOne >> toString) == Just(std::string{ "12" }));
        CHECK((Just(100) >> addOne >> toString) == Just(std::string{ "101" }));

        CHECK((Nothing<int>() >> addOne >> toString) == Nothing<std::string>());
        static_assert((Nothing<int>() >> addOne) == Nothing<int>());
    }

    SECTION("Applicative")
    {
        constexpr auto AddOne = [](const int x) -> int {
            return x + 1;
        };
        using FuncType = std::function<int(const int)>;
        CHECK((Nothing<FuncType>() > Just(1)) == Nothing<int>());
        CHECK((Just<FuncType>(AddOne) > Nothing<int>()) == Nothing<int>());
        CHECK((Just<FuncType>(AddOne) > Just(1)) == Just(2));

        constexpr auto GetSomethingIfAboveThree = [AddOne](const auto x) -> Maybe<FuncType> {
            if(x > 3) {
                return AddOne;
            }
            return {};
        };
        CHECK((GetSomethingIfAboveThree(2) > Just(10)) == Nothing<int>());
        CHECK((GetSomethingIfAboveThree(4) > Just(10)) == Just(11));
    }
}

TEST_CASE("List", "[monads]")
{
    SECTION("Chaining")
    {
        const auto doubleEntry = [](const auto x) -> List<int> {
            return { x, x };
        };

        const auto toString = [](const auto x) -> List<std::string> {
            return { std::to_string(x) };
        };

        CHECK((List<int>{1, 2, 3} >> doubleEntry) == List<int>{ 1, 1, 2, 2, 3, 3 });
        CHECK((List<int>{1, 2, 3} >> doubleEntry >> toString) == 
                List<std::string>{ "1", "1", "2", "2", "3", "3" });

        CHECK((List<int>{} >> doubleEntry >> toString) == List<std::string>{});
    }

    SECTION("Applicative")
    {
        const auto doubleValue = [](const int x) -> int {
            return x*2;
        };
        using FuncType = std::function<int(int)>;
        CHECK((List<FuncType>{} > List<int>{ 1, 2, 3}) == List<int>{});
        CHECK((List<FuncType>{ doubleValue } > List<int>{ 1, 2, 3}) == List<int>{ 2, 4, 6 });

        constexpr auto GetSomethingIfAboveThree = [doubleValue](const auto x) -> List<FuncType> {
            if(x > 3) {
                return { doubleValue };
            }
            return {};
        };
        CHECK((GetSomethingIfAboveThree(2) > List<int>{ 1, 2, 3 }) == List<int>{});
        CHECK((GetSomethingIfAboveThree(4) > List<int>{ 1, 2, 3 }) == List<int>{ 2, 4, 6 });
    }
}

TEST_CASE("Continuation", "[monads]")
{
}

