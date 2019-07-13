#include "catch.hpp"
#include "MostOccuringItem.hpp"
#include <list>
#include <vector>

TEST_CASE("most occuring", "[count]")
{
    CHECK(count::MostOccuringItem(std::vector<int>{ 1 }) == 1);
    CHECK(count::MostOccuringItem(std::vector<int>{ 0, 1 }) == 1);
    CHECK(count::MostOccuringItem(std::vector<int>{ 0, 1, 1, 3, 5 }) == 1);
    CHECK(count::MostOccuringItem(std::vector<int>{ 0, 1, 1, 3, 5, 5 }) == 5);
    CHECK(count::MostOccuringItem(std::vector<int>{ 0, 1, 1, 3, 5, 5, 1 }) == 1);

    CHECK(count::MostOccuringItem(std::list<int>{ 1 }) == 1);
    CHECK(count::MostOccuringItem(std::list<int>{ 0, 1 }) == 1);
    CHECK(count::MostOccuringItem(std::list<int>{ 0, 1, 1, 3, 5 }) == 1);
    CHECK(count::MostOccuringItem(std::list<int>{ 0, 1, 1, 3, 5, 5 }) == 5);
    CHECK(count::MostOccuringItem(std::list<int>{ 0, 1, 1, 3, 5, 5, 1 }) == 1);
}
