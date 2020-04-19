#include "catch.hpp"
#include "reverse_polish_notation.hpp"

TEST_CASE("tokenize", "[rpn]")
{
    CHECK(Tokenize("123")() == "123");
    CHECK(Tokenize("")().empty());

    {
        auto tok{ Tokenize("+++") };
        CHECK(tok() == "+++");
        CHECK(tok().empty());
        CHECK(tok().empty());
        CHECK(tok().empty());
        CHECK(tok().empty());
    }

    {
        auto tok{ Tokenize("34 1 + 100 -") };
        CHECK(tok() == "34");
        CHECK(tok() == "1");
        CHECK(tok() == "+");
        CHECK(tok() == "100");
        CHECK(tok() == "-");
        CHECK(tok().empty());
    }

    {
        auto tok{ Tokenize("34 1 + 100 -") };
        CHECK(tok() == "34");
        CHECK(tok() == "1");
        CHECK(tok() == "+");
        CHECK(tok() == "100");
        CHECK(tok() == "-");
        CHECK(tok().empty());
    }

    {
        const auto tokens{ GetTokens("34 1 + 100 -") };
        CHECK(tokens.size() == 5);
        CHECK(tokens[0] == "34");
        CHECK(tokens[1] == "1");
        CHECK(tokens[2] == "+");
        CHECK(tokens[3] == "100");
        CHECK(tokens[4] == "-");
    }
}

TEST_CASE("GetData", "[rpn]")
{
    SECTION("1")
    {
        const auto data{ GetData<int64_t>(GetTokens("34 1 + 100 -")) };
        CHECK(data.size() == 5);
        CHECK(std::get<int64_t>(data[0]) == 34);
        CHECK(std::get<int64_t>(data[1]) == 1);
        CHECK(std::get<Operation>(data[2]) == Operation::Add);
        CHECK(std::get<int64_t>(data[3]) == 100);
        CHECK(std::get<Operation>(data[4]) == Operation::Subtract);
    }
}

TEST_CASE("Do equation", "[rpn]")
{
    CHECK(DoEquation<int64_t>("1 2 *") == 2);
    CHECK(DoEquation<int64_t>("5 10 * 100 +") == 150);
    CHECK(DoEquation<int>("5 10 * 100 +") == 150);

    CHECK(DoEquation<double>("5 0.5 * 100 +") == 102.5);
    CHECK(DoEquation<double>("10 0.5 *") == 5.0);

    CHECK(DoEquation<double>("10 0.5 /") == 20.0);

    CHECK(DoEquation<double>("10      0.5    / ") == 20.0);
}

