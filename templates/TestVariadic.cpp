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

namespace {
    class InverseBool{
        public:
            bool operator()(const bool val) const {
                return !val;
            }
    };

    class IsEqual {
        public:
            template <typename T>
            bool operator()(const T& a, const T& b) const {
                return a == b;
            }
    };
}

TEST_CASE("variadic overload", "[variadic]")
{
    Overloader<InverseBool, IsEqual> test;
    CHECK(test(false));
    CHECK_FALSE(test(true));

    CHECK(test(std::string{"abc"}, std::string{"abc"}));
    CHECK_FALSE(test(std::string{"abc"}, std::string{"cba"}));
}
