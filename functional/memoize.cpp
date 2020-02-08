#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

#include <tuple>
#include <map>

static constexpr std::size_t FibonacciConstexpr(const std::size_t n) {
    if(n <= 1) {
        return n;
    }
    return FibonacciConstexpr(n-1) + FibonacciConstexpr(n-2);
}

// this can be constexpr, but keep it run time
static std::size_t Fibonacci(const std::size_t n) {
    return FibonacciConstexpr(n);
}

template <typename Result, typename ...Args>
static auto make_memoized(Result (*func)(Args...)) { // does not work for recursive
    std::map<std::tuple<Args...>, Result> cache;
    return [func, cache = std::move(cache)](Args... args) mutable {
        auto argsTuple{ std::make_tuple(args...) };
        const auto found{ cache.find(argsTuple) };
        if(found != cache.end()) {
            return found->second;
        }
        return cache.insert(std::make_pair(std::move(argsTuple), func(args...))).first->second;
    };
}

TEST_CASE("fibonacci", "[fibonacci]")
{
    CHECK(Fibonacci(0) == 0);
    CHECK(Fibonacci(1) == 1);
    CHECK(Fibonacci(2) == 1);
    CHECK(Fibonacci(3) == 2);
    CHECK(Fibonacci(4) == 3);
    CHECK(Fibonacci(5) == 5);
    CHECK(Fibonacci(6) == 8);
    CHECK(Fibonacci(7) == 13);
    CHECK(Fibonacci(25) == 75025);

    // doesn't resolve to a constant expression, this worked
    CHECK([](){ 
        constexpr auto val{ FibonacciConstexpr(50) }; 
        return val; 
    }() == 12586269025);
}

TEST_CASE("memoize", "[.][memoize]")
{
    BENCHMARK("Constexpr") // fastest
    {
        constexpr auto val{ FibonacciConstexpr(25) };
        constexpr auto val2{ FibonacciConstexpr(25) };
        constexpr auto val3{ FibonacciConstexpr(25) };
    };

    BENCHMARK("Recursive Memoization")
    {
    };

    BENCHMARK("Naive memoization (non recursive)")
    {
        auto fib{ make_memoized(Fibonacci) };
        fib(25);
        fib(25);
        fib(25);
    };

    BENCHMARK("Regular") // slowest
    {
        Fibonacci(25);
        Fibonacci(25);
        Fibonacci(25);
    };

}
