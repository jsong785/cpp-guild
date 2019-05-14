#include "LRUCache.h"
#include "catch.hpp"

TEST_CASE("LRUCache", "first")
{
    LRUCache c{3};

    c.set(1, 1);
    c.set(2, 2);
    c.set(3, 3);

    CHECK(c.get(1) == 1);
    CHECK(c.get(2) == 2);
    CHECK(c.get(3) == 3);

    CHECK(c.get(0) == -1);
    CHECK(c.get(4) == -1);

    c.set(4, 4);
    CHECK(c.get(2) == 2);
    CHECK(c.get(3) == 3);
    CHECK(c.get(4) == 4);

    CHECK(c.get(1) == -1);

    c.set(3, 33);
    CHECK(c.get(2) == 2);
    CHECK(c.get(4) == 4);
    CHECK(c.get(3) == 33);

    c.set(5, 55);
    CHECK(c.get(4) == 4);
    CHECK(c.get(3) == 33);
    CHECK(c.get(5) == 55);
}
