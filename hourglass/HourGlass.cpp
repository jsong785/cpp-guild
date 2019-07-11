#include "catch.hpp"
#include <assert.h>

template
<typename T, typename N>
int GetHourGlassMaxSum(T (&matrix)[N][N])
{
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

    const auto canDoHourGlass = [](const auto x, const auto y) {
        return x + 3 < N && y + 3 < N;
    };

    bool init{ false };
    int max{ 0 };

    for(auto row{ 0 }; row < N; ++row) {
        if(!canDoHourGlass(row, 0)) { break; } // this row is invalid, reached the end!

        for(auto col{ 0 }; col < N; ++col) {
            if(!canDoHourGlass(0, col)) { break; } // this col is invalid, reached the end!

            const auto sum{ getVal(matrix, row, col, 0) + getVal(matrix, row, col, 1) + getVal(matrix, row, col, 2) + 
                                                          getVal(matrix, row, col, 3) + 
                            getVal(matrix, row, col, 4) + getVal(matrix, row, col, 5) + getVal(matrix, row, col, 6) };
            if(!init || sum > max) {
                init = true;
                max = sum;
            }
        }
    }

    return max;
}

TEST_CASE("HourGlass", "")
{
    SECTION("1")
    {
        int matrix[4][4]{
            { 1, 4, 4, 4},
            { 1, 1, 4, 1},
            { 1, 4, 4, 4},
            { 1, 0, 0, 0}
        }
        CHECK(GetHourGlassMaxSum(matrix) == 24);
    }
}
