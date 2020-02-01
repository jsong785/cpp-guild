#include "catch.hpp"
#include "Tuple.h"

TEST_CASE("Transform Tuple" "[tuple]")
{
    SECTION("all ints")
    {
        auto data{ std::make_tuple(1, 2, 3, 4, 5) };
        TransformTuple(data, [](const auto i){
            return i + 1;
        });
        CHECK(std::get<0>(data) == 2);
        CHECK(std::get<1>(data) == 3);
        CHECK(std::get<2>(data) == 4);
        CHECK(std::get<3>(data) == 5);
        CHECK(std::get<4>(data) == 6);
    }

    SECTION("all strings")
    {
        auto data{ 
            std::make_tuple(
                std::string{"1"},
                std::string{"2"},
                std::string{"3"},
                std::string{"4"}
            )
        };
        TransformTuple(data, [](const auto str){
            auto copy{ str };
            copy += "1";
            return copy;
        });
        CHECK(std::get<0>(data) == "11");
        CHECK(std::get<1>(data) == "21");
        CHECK(std::get<2>(data) == "31");
        CHECK(std::get<3>(data) == "41");
    }

    SECTION("ints and strings")
    {
        // exploit method overloading
        class Callable {
            public:
                int operator()(const int val) {
                    return val+1; 
                }

                std::string operator()(const std::string &val) {
                    auto copy{ val };
                    copy += "1";
                    return copy;
                }
        };

        auto data{ 
            std::make_tuple(
                1,
                2,
                std::string{"3"},
                std::string{"4"}
            )
        };
        TransformTuple(data, Callable{});
        CHECK(std::get<0>(data) == 2);
        CHECK(std::get<1>(data) == 3);
        CHECK(std::get<2>(data) == "31");
        CHECK(std::get<3>(data) == "41");
    }

    SECTION("ints and doubles")
    {
        auto data{ std::make_tuple(1, 2, 3.3, 4.4) };
        // exploit auto
        TransformTuple(data, [](const auto val){
                return val + 1;
        });
        CHECK(std::get<0>(data) == 2);
        CHECK(std::get<1>(data) == 3);
        CHECK(std::get<2>(data) == 4.3);
        CHECK(std::get<3>(data) == 5.4);
    }
}
