#include "catch.hpp"
#include <algorithm>
#include <cctype>
#include <functional>

static bool isspacebool(const int c);
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

bool isspacebool(const int c) {
    return isspace(c) != 0;
}

std::string TrimLeft(std::string val) {
    return { 
        std::make_move_iterator(std::find_if(val.begin(), val.end(), [](const auto c){ 
            return std::logical_not<bool>()(isspacebool(c)); 
        })),
        std::make_move_iterator(val.end())
    }; 
}

std::string TrimRight(std::string val) {
    return { 
        std::make_move_iterator(val.begin()),
        std::make_move_iterator(std::find_if(val.rbegin(), val.rend(), [](const auto c){
            return std::logical_not<bool>()(isspacebool(c));
        }).base())
    }; 
}

std::string Trim(std::string val) {
    return TrimLeft(TrimRight(std::move(val)));
}


