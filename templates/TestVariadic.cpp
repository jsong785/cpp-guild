#include "catch.hpp"
#include "variadic.hpp"

TEST_CASE("variadic", "[variadic]")
{
    CHECK(ConcatStream(1, 1, 1, 1, 1).str() == "11111");
    CHECK(ConcatStream(1, "1", "one", 1.1).str() == "11one1.1");
    CHECK(ConcatDoubleStream(1, 1, 1).str() == "222");

    CHECK(Filter<int>({1, 2, 3, 4}, 0, 1) == std::vector<int>{1, 2});
    CHECK(Filter<int>({1, 2, 3, 4}, 3, 2) == std::vector<int>{4, 3});
}
