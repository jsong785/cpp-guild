#include "LRUCache.h"
#include "catch.hpp"

TEST_CASE("LRUCache", "first")
{
    LRUCache c{3};

    c.Set(1, 1);
    c.Set(2, 2);
    c.Set(3, 3);

    CHECK(c.Get(1) == 1);
    CHECK(c.Get(2) == 2);
    CHECK(c.Get(3) == 3);

    CHECK(c.Get(0) == -1);
    CHECK(c.Get(4) == -1);

    c.Set(4, 4);
    CHECK(c.Get(2) == 2);
    CHECK(c.Get(3) == 3);
    CHECK(c.Get(4) == 4);

    CHECK(c.Get(1) == -1);

    c.Set(3, 33);
    CHECK(c.Get(2) == 2);
    CHECK(c.Get(4) == 4);
    CHECK(c.Get(3) == 33);

    c.Set(5, 55);
    CHECK(c.Get(4) == 4);
    CHECK(c.Get(3) == 33);
    CHECK(c.Get(5) == 55);
}
