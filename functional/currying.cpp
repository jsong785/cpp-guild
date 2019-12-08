#include "catch.hpp"

int original(const int x, const int y, const int z) {
    return x + y + z;
}

auto currying(const int x) {
    return [x](const int y){
        return[x, y](const int z){
            return x + y + z;
        };
    };
}

TEST_CASE("currying", "")
{
    CHECK(original(1, 2, 3) == currying(1)(2)(3));
    CHECK(original(1, 1, 1) == currying(1)(1)(1));
}

