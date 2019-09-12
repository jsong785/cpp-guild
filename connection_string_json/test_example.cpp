#include "catch2.hpp"
#include "example.h"

using namespace example;

TEST_CASE("connection string") 
{
    ...
}

TEST_CASE("Test GetSchema")
{
    SECTION("JSON")
    {
        REQUIRE(GetSchema(JSON_SCHEMA).is_initialized());
    }

    SECTION("ODBC")
    {
        REQUIRE(GetSchema(ODBC_SCHEMA).is_initialized());
    }

    SECTION("JSON FAIL")
    {
        auto jsonModified{ JSON_SCHEMA };
        jsonModified += "parse_fail";
        REQUIRE(!GetSchema(jsonModified).is_initialized());
    }

    SECTION("ODBC FAIL")
    {
        auto odbcModified{ odbc_SCHEMA };
        odbcModified += "parse_fail";
        REQUIRE(!GetSchema(odbcModified).is_initialized());
    }

    SECTION("misc")
    {
        REQUIRE(!GetSchema("dslkfjas;ldfjksf").is_initialized());
    }
}

TEST_CASE("Test Get json Schema") 
{
    // set up some document that passes
    REQUIRE(GetJsonSchema(doc).Length() > 0);

    // this fails
    REQUIRE(GetJsonSchema(invaliddoc).Length() == 0);
}

TEST_CASE("Test Get odbc Schema") 
{
    // set up some document that passes
    REQUIRE(GetodbcSchema(doc).Length() > 0);

    // this fails
    REQUIRE(GetodbcSchema(invaliddoc).Length() == 0);
}
