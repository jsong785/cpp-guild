#include "catch.hpp"
#include <utility>
#include <assert.h>

#include "SelectionSort.hpp"
#include "StringUtils.hpp"

namespace {
    template <typename T, unsigned N>
    constexpr bool SortAndCompare(const T (&str)[N], const T (&expected)[N]) {
        T copy[N]{ 0 };
        StringUtils::StrCpy(copy, str);

        Sort::SelectionSort(copy, N-1); // removing nul
        return StringUtils::StrIsEqual(copy, expected);
    }
}

TEST_CASE("SelectionSort", "[sort]")
{
    SECTION("empty")
    {
        char str[]{ "" };
        CHECK(SortAndCompare(str, ""));
    }

    SECTION("single letter")
    {
        char str[]{ "A" };
        CHECK(SortAndCompare(str, "A"));
    }

    SECTION("reverse")
    {
        char str[]{ "CBA" };
        CHECK(SortAndCompare(str, "ABC"));
    }
}
