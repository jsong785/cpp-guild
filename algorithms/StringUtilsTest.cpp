#include "catch.hpp"
#include "StringUtils.hpp"

TEST_CASE("StrLen", "[StringUtils]")
{
    static_assert((StringUtils::StrLen("") == 0), "");
    static_assert((StringUtils::StrLen("A") == 1), "");
    static_assert((StringUtils::StrLen("ABC") == 3), "");

    static_assert((StringUtils::StrLen(L"") == 0), "");
    static_assert((StringUtils::StrLen(L"A") == 1), "");
    static_assert((StringUtils::StrLen(L"ABC") == 3), "");

    static_assert((StringUtils::StrLen(u"") == 0), "");
    static_assert((StringUtils::StrLen(u"A") == 1), "");
    static_assert((StringUtils::StrLen(u"ABC") == 3), "");

    static_assert((StringUtils::StrLen(U"") == 0), "");
    static_assert((StringUtils::StrLen(U"A") == 1), "");
    static_assert((StringUtils::StrLen(U"ABC") == 3), "");
}

TEST_CASE("StrIsEqual", "[StringUtils]")
{
    static_assert((StringUtils::StrIsEqual("", "")), "");
    static_assert((StringUtils::StrIsEqual("A", "A")), "");
    static_assert((StringUtils::StrIsEqual("ABC", "ABC")), "");

    static_assert((!StringUtils::StrIsEqual("A", "")), "");
    static_assert((!StringUtils::StrIsEqual("", "A")), "");
    static_assert((!StringUtils::StrIsEqual("ABC", "ABCDE")), "");
    static_assert((!StringUtils::StrIsEqual("ABCDE", "ABC")), "");

    static_assert((StringUtils::StrIsEqual(L"", L"")), "");
    static_assert((StringUtils::StrIsEqual(L"A", L"A")), "");
    static_assert((StringUtils::StrIsEqual(L"ABC", L"ABC")), "");

    static_assert((!StringUtils::StrIsEqual(L"A", L"")), "");
    static_assert((!StringUtils::StrIsEqual(L"", L"A")), "");
    static_assert((!StringUtils::StrIsEqual(L"ABC", L"ABCDE")), "");
    static_assert((!StringUtils::StrIsEqual(L"ABCDE", L"ABC")), "");

    static_assert((StringUtils::StrIsEqual(u"", u"")), "");
    static_assert((StringUtils::StrIsEqual(u"A", u"A")), "");
    static_assert((StringUtils::StrIsEqual(u"ABC", u"ABC")), "");

    static_assert((!StringUtils::StrIsEqual(u"A", u"")), "");
    static_assert((!StringUtils::StrIsEqual(u"", u"A")), "");
    static_assert((!StringUtils::StrIsEqual(u"ABC", u"ABCDE")), "");
    static_assert((!StringUtils::StrIsEqual(u"ABCDE", u"ABC")), "");

    static_assert((StringUtils::StrIsEqual(U"", U"")), "");
    static_assert((StringUtils::StrIsEqual(U"A", U"A")), "");
    static_assert((StringUtils::StrIsEqual(U"ABC", U"ABC")), "");

    static_assert((!StringUtils::StrIsEqual(U"A", U"")), "");
    static_assert((!StringUtils::StrIsEqual(U"", U"A")), "");
    static_assert((!StringUtils::StrIsEqual(U"ABC", U"ABCDE")), "");
    static_assert((!StringUtils::StrIsEqual(U"ABCDE", U"ABC")), "");
}

namespace {

template <typename T, unsigned N>
constexpr bool CopyCompare(const T (&str)[N], const T (&expected)[N]) {
    T copy[N]{ 0 };
    StringUtils::StrCpy(copy, str);
    return StringUtils::StrIsEqual(copy, expected);
}

}

TEST_CASE("StrCpy", "[StringUtils]")
{
    SECTION("empty")
    {
        CHECK(CopyCompare("", ""));
        CHECK(CopyCompare(u"", u""));
        CHECK(CopyCompare(U"", U""));
    }

    SECTION("single")
    {
        CHECK(CopyCompare("A", "A"));
        CHECK(CopyCompare(u"A", u"A"));
        CHECK(CopyCompare(U"A", U"A"));
    }

    SECTION("multiple")
    {
        CHECK(CopyCompare("ABC", "ABC"));
        CHECK(CopyCompare(u"ABC", u"ABC"));
        CHECK(CopyCompare(U"ABC", U"ABC"));
    }
}

