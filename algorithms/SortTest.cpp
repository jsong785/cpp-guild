#include "catch.hpp"
#include <utility>
#include <assert.h>

#include "Sort.hpp"
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

TEST_CASE("InsertionSort", "[sort]")
{
    using namespace Sort;
    SECTION("empty")
    {
        CHECK(InsertionSort(std::vector<int>{}).empty());
    }

    SECTION("single item")
    {
        CHECK(operator==(InsertionSort(std::vector<int>{0}), {0}));
        CHECK(operator==(InsertionSort(std::vector<int>{1}), {1}));
    }

    SECTION("multiple items")
    {
        CHECK(operator==(InsertionSort(std::vector<int>{5, 10, 9, -1, 0, 4}), {-1, 0, 4, 5, 9, 10}));
    }
}

TEST_CASE("MergeSort", "[sort]")
{
    using namespace Sort;
    SECTION("empty")
    {
        CHECK(MergeSort(std::vector<int>{}).empty());
    }

    SECTION("single item")
    {
        CHECK(operator==(MergeSort(std::vector<int>{0}), {0}));
        CHECK(operator==(MergeSort(std::vector<int>{1}), {1}));
    }

    SECTION("multiple items")
    {
        CHECK(operator==(MergeSort(std::vector<int>{0, 5, 4, 2, 3, 9, 10}), {0, 2, 3, 4, 5, 9, 10}));
    }
}
