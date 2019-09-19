#include "catch.hpp"
#include "CsvWriter.h"

#include <sstream>

TEST_CASE("CsvWriter NumFields", "")
{
    std::stringstream stream;

    SECTION("1")
    {
        CsvWriter csv{stream, ',', 1};
        csv.PushEmpty();
        csv.Write();
        csv.Flush();
        REQUIRE(stream.str() == "\n");
    }

    SECTION("1, more tokens than usual")
    {
        CsvWriter csv{stream, ',', 1};
        csv.PushEmpty();
        csv.PushEmpty();
        csv.Write();
        csv.Flush();
        REQUIRE(stream.str() == "\n");
    }

    SECTION("1, less tokens than usual")
    {
        CsvWriter csv{stream, ',', 1};
        csv.Write();
        csv.Flush();
        REQUIRE(stream.str() == "\n");
    }

    SECTION("2")
    {
        CsvWriter csv{stream, ',', 2};
        csv.PushEmpty();
        csv.PushEmpty();
        csv.Write();
        csv.Flush();
        REQUIRE(stream.str() == ",\n");
    }

    SECTION("2, more tokens than usual")
    {
        CsvWriter csv{stream, ',', 2};
        csv.PushEmpty();
        csv.PushEmpty();
        csv.PushEmpty();
        csv.Write();
        csv.Flush();
        REQUIRE(stream.str() == ",\n");
    }

    SECTION("2, less tokens than usual")
    {
        CsvWriter csv{stream, ',', 2};
        csv.Write();
        csv.Flush();
        REQUIRE(stream.str() == ",\n");
    }

    SECTION("3")
    {
        CsvWriter csv{stream, ',', 3};
        csv.PushEmpty();
        csv.PushEmpty();
        csv.PushEmpty();
        csv.Write();
        csv.Flush();
        REQUIRE(stream.str() == ",,\n");
    }

    SECTION("3, more tokens than usual")
    {
        CsvWriter csv{stream, ',', 3};
        csv.PushEmpty();
        csv.PushEmpty();
        csv.PushEmpty();
        csv.PushEmpty();
        csv.Write();
        csv.Flush();
        REQUIRE(stream.str() == ",,\n");
    }

    SECTION("3, less tokens than usual")
    {
        CsvWriter csv{stream, ',', 3};
        csv.Write();
        csv.Flush();
        REQUIRE(stream.str() == ",,\n");
    }
}

TEST_CASE("CsvWriter char", "")
{
    std::stringstream stream;
    
    CsvWriter csv{stream, ',', 3};
    csv.Push('a');
    csv.Push('b');
    csv.Push('c');
    csv.Write();
    REQUIRE(stream.str() == "a,b,c\n");
}

TEST_CASE("CsvWriter int", "")
{
    std::stringstream stream;
    
    CsvWriter csv{stream, ',', 3};
    csv.Push(10);
    csv.Push(100);
    csv.Push(200);
    csv.Write();
    REQUIRE(stream.str() == "10,100,200\n");
}

TEST_CASE("CsvWriter int64_t", "")
{
    std::stringstream stream;
    
    CsvWriter csv{stream, ',', 3};
    csv.Push(static_cast<int64_t>(10));
    csv.Push(static_cast<int64_t>(100));
    csv.Push(static_cast<int64_t>(200));
    csv.Write();
    csv.Flush();
    REQUIRE(stream.str() == "10,100,200\n");
}

TEST_CASE("CsvWriter float", "")
{
    std::stringstream stream;
    
    CsvWriter csv{stream, ',', 3};
    csv.Push(1.0f);
    csv.Push(2.1234567f);
    csv.Push(3.12345678f);
    csv.Write();
    csv.Flush();
    REQUIRE(stream.str() == "1.000000,2.123457,3.123457\n");
}

TEST_CASE("CsvWriter double", "")
{
    std::stringstream stream;
    
    CsvWriter csv{stream, ',', 3};
    csv.Push(1.0);
    csv.Push(2.1234567);
    csv.Push(3.12345678);
    csv.Write();
    csv.Flush();
    REQUIRE(stream.str() == "1.000000,2.123457,3.123457\n");
}

TEST_CASE("CsvWriter string", "")
{
    std::stringstream stream;

    SECTION("regular strings")
    {
        CsvWriter csv{stream, ',', 3};
        csv.Push("hello");
        csv.Push("world");
        csv.Push("csv");
        csv.Write();
        csv.Flush();
        REQUIRE(stream.str() == R"("hello","world","csv")""\n");
    }

    SECTION("escaped strings double quote")
    {
        CsvWriter csv{stream, ',', 3};
        csv.Push("hello");
        csv.Push("world");
        csv.Push("\"csv\"");
        csv.Write();
        csv.Flush();
        REQUIRE(stream.str() == R"("hello","world","\"csv\"")""\n");
    }

    SECTION("escaped strings single quote")
    {
        CsvWriter csv{stream, ',', 3};
        csv.Push("h'e'llo");
        csv.Push("world");
        csv.Push("\"csv\"");
        csv.Write();
        csv.Flush();
        REQUIRE(stream.str() == R"("h\'e\'llo","world","\"csv\"")""\n");
    }
}

