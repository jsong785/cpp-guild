#include "catch.hpp"
#include <utility>
#include <assert.h>

namespace {
    template <typename T>
    unsigned GetStrLen(const T *str) {
        unsigned sz{ 0 };
        for(; *str != 0; ++str, ++sz);
        return sz;
    }

    template <typename T>
    bool IsStrEqual(const T* one, const T *two) {
        for(; *one != 0; ++one, ++two) {
            if(*one != *two) {
                return false;
            }
        }
        return *one == *two;
    }

    template <typename T>
    void InsertionSort(T *str, const unsigned len) {
        for(unsigned i{ 0 }; i < len; ++i) {
            unsigned min{ i };
            for(unsigned j{ i+1 }; j < len; ++j) {
                if(str[j] < str[min]) {
                    min = j;
                }
            }
            std::swap(str[i], str[min]);
        }
    }
}
TEST_CASE("strlen", "")
{
    CHECK(GetStrLen("") == 0);
    CHECK(GetStrLen("A") == 1);
    CHECK(GetStrLen("ABC") == 3);

    CHECK(GetStrLen(L"") == 0);
    CHECK(GetStrLen(L"A") == 1);
    CHECK(GetStrLen(L"ABC") == 3);

    CHECK(GetStrLen(u"") == 0);
    CHECK(GetStrLen(u"A") == 1);
    CHECK(GetStrLen(u"ABC") == 3);

    CHECK(GetStrLen(U"") == 0);
    CHECK(GetStrLen(U"A") == 1);
    CHECK(GetStrLen(U"ABC") == 3);
}

TEST_CASE("isstrequal", "")
{
    CHECK(IsStrEqual("", ""));
    CHECK(IsStrEqual("A", "A"));
    CHECK(IsStrEqual("ABC", "ABC"));

    CHECK(!IsStrEqual("A", ""));
    CHECK(!IsStrEqual("", "A"));
    CHECK(!IsStrEqual("ABC", "ABCDE"));
    CHECK(!IsStrEqual("ABCDE", "ABC"));

    CHECK(IsStrEqual(L"", L""));
    CHECK(IsStrEqual(L"A", L"A"));
    CHECK(IsStrEqual(L"ABC", L"ABC"));

    CHECK(!IsStrEqual(L"A", L""));
    CHECK(!IsStrEqual(L"", L"A"));
    CHECK(!IsStrEqual(L"ABC", L"ABCDE"));
    CHECK(!IsStrEqual(L"ABCDE", L"ABC"));

    CHECK(IsStrEqual(u"", u""));
    CHECK(IsStrEqual(u"A", u"A"));
    CHECK(IsStrEqual(u"ABC", u"ABC"));

    CHECK(!IsStrEqual(u"A", u""));
    CHECK(!IsStrEqual(u"", u"A"));
    CHECK(!IsStrEqual(u"ABC", u"ABCDE"));
    CHECK(!IsStrEqual(u"ABCDE", u"ABC"));

    CHECK(IsStrEqual(U"", U""));
    CHECK(IsStrEqual(U"A", U"A"));
    CHECK(IsStrEqual(U"ABC", U"ABC"));

    CHECK(!IsStrEqual(U"A", U""));
    CHECK(!IsStrEqual(U"", U"A"));
    CHECK(!IsStrEqual(U"ABC", U"ABCDE"));
    CHECK(!IsStrEqual(U"ABCDE", U"ABC"));
}

TEST_CASE("sort", "")
{
    const auto sortAndCompare = [](auto str, const auto expected) {
        InsertionSort(str, GetStrLen(str));
        return IsStrEqual(str, expected);
    };

    SECTION("empty")
    {
        char str[]{ "" };
        CHECK(sortAndCompare(str, ""));
    }

    SECTION("single letter")
    {
        char str[]{ "A" };
        CHECK(sortAndCompare(str, "A"));
    }

    SECTION("reverse")
    {
        char str[]{ "CBA" };
        CHECK(sortAndCompare(str, "ABC"));
    }
}
