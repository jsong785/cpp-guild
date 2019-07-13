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

TEST_CASE("StrCpy", "[StringUtils]")
{
    char buf[16];

    SECTION("empty")
    {
        StringUtils::StrCpy(buf, "");
        CHECK(StringUtils::StrIsEqual(buf, ""));
    }

    SECTION("single")
    {
        StringUtils::StrCpy(buf, "A");
        CHECK(StringUtils::StrIsEqual(buf, "A"));
    }

    SECTION("multiple")
    {
        StringUtils::StrCpy(buf, "ABC");
        CHECK(StringUtils::StrIsEqual(buf, "ABC"));
    }
}

