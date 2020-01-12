#include "catch.hpp"
#include <algorithm>
#include <cctype>
#include <functional>

static bool IsSpacebool(const int c);
static std::string TrimLeft(std::string val);
static std::string TrimRight(std::string val);
static std::string Trim(std::string val);

TEST_CASE("Trim left")
{
    CHECK(TrimLeft("abc") == "abc");
    CHECK(TrimLeft("abc  ") == "abc  ");
    CHECK(TrimLeft("  ").empty());
    CHECK(TrimLeft("  abc") == "abc");
}

TEST_CASE("Trim right")
{
    CHECK(TrimRight("abc") == "abc");
    CHECK(TrimRight("abc  ") == "abc");
    CHECK(TrimRight("  ").empty());
    CHECK(TrimRight("  abc") == "  abc");
}

TEST_CASE("Trim")
{
    CHECK(Trim("abc") == "abc");
    CHECK(Trim("abc  ") == "abc");
    CHECK(Trim("  ").empty());
    CHECK(Trim("  abc") == "abc");
}

bool IsNotSpaceBool(const int c)
{
    return isspace(c) == 0;
}

std::string TrimLeft(std::string val) {
    const auto eraseEnd{ std::find_if(val.cbegin(), val.cend(), IsNotSpaceBool) };
    if(val.begin() != eraseEnd) {
        val.erase(val.begin(), eraseEnd);
    }
    return val;
}

std::string TrimRight(std::string val) {
    const auto eraseStart{ std::find_if(val.crbegin(), val.crend(), IsNotSpaceBool).base() };
    if(eraseStart != val.cend()) {
        val.erase(eraseStart, val.cend());
    }
    return val;
}

std::string Trim(std::string val) {
    return TrimLeft(TrimRight(std::move(val)));
}


