#include "nested.hpp"
#include "catch.hpp"
#include <algorithm>

// specialization
template <>
    template<>
std::size_t Nested<std::vector<int>>::IncreaseAndGet() const {
    return 100;
}

TEST_CASE("nested", "[nested]")
{
    CHECK(Nested<int>{}.IncreaseAndGet<double>() == 0.0);
    CHECK(Nested<int>{}.IncreaseAndGet<double>() == 1.0);
    CHECK(Nested<int>{}.IncreaseAndGet<double>() == 2.0);

    // Nested<double> is a different, type, so static int count is 0
    CHECK(Nested<double>{}.IncreaseAndGet<int>() == 0);
    CHECK(Nested<double>{}.IncreaseAndGet<int>() == 1);
    CHECK(Nested<double>{}.IncreaseAndGet<int>() == 2);

    CHECK(Nested<double>{}.IncreaseAndGet<double>() == 3.0);

    CHECK(Nested<std::vector<int>>{}.IncreaseAndGet<std::size_t>() == 100);
    CHECK(Nested<std::vector<int>>{}.IncreaseAndGet<std::size_t>() == 100);
}
