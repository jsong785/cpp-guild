#include "catch.hpp"

TEST_CASE("Reverse String")
{
    CHECK(ReverseString(nullptr).empty());
    CHECK(ReverseString("").empty());
    CHECK(ReverseString(" ") == " ");
    CHECK(ReverseString("  ") == "  ");

    CHECK(ReverseString("abc") == "cba");
    CHECK(ReverseString("ABC") == "CBA");
    CHECK(ReverseString("aBc") == "cBa");
    CHECK(ReverseString("AbC") == "CbA");

    CHECK(ReverseString("SomethiNg") == "gNihtemoS");
}
