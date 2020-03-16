#include "catch.hpp"
#include "variadic.hpp"

TEST_CASE("variadic", "[variadic]")
{
    CHECK(ConcatStream(1, 1, 1, 1, 1).str() == "11111");
    CHECK(ConcatStream(1, "1", "one", 1.1).str() == "11one1.1");
    CHECK(ConcatDoubleStream(1, 1, 1).str() == "222");
}
