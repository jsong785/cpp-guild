#include "catch.hpp"
#include <utility>
#include <assert.h>

#include "SelectionSort.hpp"
#include "StringUtils.hpp"

namespace {

template <typename T, unsigned N>
constexpr bool CopySortCompare(const T (&str)[N], const T (&expected)[N]) {
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
        CHECK(CopySortCompare("", ""));
        CHECK(CopySortCompare(u"", u""));
        CHECK(CopySortCompare(U"", U""));
    }

    SECTION("single letter")
    {
        CHECK(CopySortCompare("A", "A"));
        CHECK(CopySortCompare(u"A", u"A"));
        CHECK(CopySortCompare(U"A", U"A"));
    }

    SECTION("reverse")
    {
        CHECK(CopySortCompare("CBA", "ABC"));
        CHECK(CopySortCompare(u"CBA", u"ABC"));
        CHECK(CopySortCompare(U"CBA", U"ABC"));
    }
}
