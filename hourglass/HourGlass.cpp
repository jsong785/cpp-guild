#include "catch.hpp"
#include <assert.h>

template
<typename T, int N>
int GetHourglassMaxSum(T (&&matrix)[N][N])
{
    static_assert(N >= 3, "Matrix must be at least 3x3");
    const auto getVal = [](const auto matrix[N][N], const auto originRow, const auto originCol, const auto i) {
        switch(i) {
            case 0:
                return matrix[originRow][originCol];
            case 1:
                return matrix[originRow][originCol+1];
            case 2:
                return matrix[originRow][originCol+2];
            case 3:
                return matrix[originRow+1][originCol+1];
            case 4:
                return matrix[originRow+2][originCol];
            case 5:
                return matrix[originRow+2][originCol+1];
            case 6:
                return matrix[originRow+2][originCol+2];
            default: break;
       }
        assert(false);
        return 0;
    };

    const auto canDoHourglass = [](const auto x, const auto y) {
        return x + 2 < N && y + 2 < N;
    };

    const auto getMaxSumOfHourglass = [&canDoHourglass, &getVal](const auto matrix[N][N]){
        bool init{ false };
        int max{ 0 };

        for(auto row{ 0 }; row < N; ++row) {
            if(!canDoHourglass(row, 0)) { break; } // this row is invalid, reached the end!

            for(auto col{ 0 }; col < N; ++col) {
                if(!canDoHourglass(0, col)) { break; } // this col is invalid, reached the end!

                const auto sum{ getVal(matrix, row, col, 0) + getVal(matrix, row, col, 1) + getVal(matrix, row, col, 2) + 
                                                              getVal(matrix, row, col, 3) + 
                                getVal(matrix, row, col, 4) + getVal(matrix, row, col, 5) + getVal(matrix, row, col, 6) };
                if(!init || sum > max) {
                    init = true;
                    max = sum;
                }
            }
        }
        assert(init);
        return max;
    };

    return getMaxSumOfHourglass(matrix);
}

TEST_CASE("Hourglass", "")
{
    // won't compile (templates!) (not a square matrix)
    /*CHECK(GetHourglassMaxSum({ { 9, 9, 4},
                               { 9, 4, 1},
                               { 9, 9, 4},
                               { 0, 0, 0} }) == 63);*/
    // won't compile, minimum is 3x3 matrix
    /*CHECK(GetHourglassMaxSum({ { 9, 9 },
                               { 0, 0 } }) == 63);*/

    SECTION("3x3")
    {
        CHECK(GetHourglassMaxSum({ { 9, 9, 9 },
                                   { 1, 9, 4 },
                                   { 9, 9, 9 } }) == 63);
    }

    SECTION("4x4")
    {
        // upper left
        CHECK(GetHourglassMaxSum({ { 9, 9, 9, 4},
                                   { 1, 9, 4, 1},
                                   { 9, 9, 9, 4},
                                   { 1, 0, 0, 0} }) == 63);

        // upper right
        CHECK(GetHourglassMaxSum({ { 1, 4, 4, 4},
                                   { 1, 1, 4, 1},
                                   { 1, 4, 4, 4},
                                   { 1, 0, 0, 0} }) == 28);

        // lower left
        CHECK(GetHourglassMaxSum({ { 1, 4, 4, 4},
                                   { 5, 5, 5, 1},
                                   { 1, 5, 4, 4},
                                   { 5, 5, 5, 0} }) == 35);

        // lower right
        CHECK(GetHourglassMaxSum({ { 1, 4, 4, 4},
                                   { 5, 8, 8, 8},
                                   { 1, 5, 8, 4},
                                   { 5, 8, 8, 8} }) == 56);
    }

    SECTION("10x10")
    {
        CHECK(GetHourglassMaxSum({ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }) == 0);

        // in the middle somewhere
        CHECK(GetHourglassMaxSum({ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 9, 9, 9, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 9, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 9, 9, 9, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }) == 63);
    }
}
