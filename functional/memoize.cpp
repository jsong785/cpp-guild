#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

#include "memoize.hpp"

static constexpr std::size_t FibonacciConstexpr(const std::size_t n) {
    if(n <= 1) {
        return n;
    }
    return FibonacciConstexpr(n-1) + FibonacciConstexpr(n-2);
}

// non constexpr version
static std::size_t Fibonacci(const std::size_t n) {
    return FibonacciConstexpr(n);
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

    BENCHMARK("Naive memoization (non recursive, with lambdas)")
    {
        auto fib{ 
            make_memoized<std::size_t(const std::size_t)>([](const std::size_t val){
                return Fibonacci(val);
            }) 
        };
        fib(25);
        fib(25);
        fib(25);
    };

    BENCHMARK("Naive memoization (non recursive)")
    {
        auto fib{ make_memoized<std::size_t(const std::size_t)>(Fibonacci) };
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
