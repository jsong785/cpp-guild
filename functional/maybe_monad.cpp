#include "catch.hpp"
#include "maybe_monad.hpp"

TEST_CASE("Maybe Monad", "[monad]")
{
    CHECK_FALSE(MaybeMonad<int>::Construct());
    CHECK(MaybeMonad<int>::Unit(4));
    CHECK(*MaybeMonad<int>::Unit(4) == 4);
}
