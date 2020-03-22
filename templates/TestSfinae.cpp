#include "catch.hpp"
#include "sfinae.hpp"
#include <vector>

namespace {

template <typename T>
struct Mock {
    T operator-(const Mock &other) const {
        return this->val - other.val;
    };

    T val{};
};

}

TEST_CASE("sfinae", "[sfinae]")
{
    CHECK(Add(1) == 1);
    CHECK(Add(1, 2) == 3);
    CHECK(Add(1, -2) == -1);

    CHECK(Subtract(2, 1) == 1);
    CHECK(Subtract(std::vector<int>{1, 2}, std::vector<int>{1}) == 1);

    CHECK(Subtract(Mock<int>{1}, Mock<int>{2}) == -1);
    CHECK(Subtract(Mock<int>{10}, Mock<int>{2}) == 8);
}

