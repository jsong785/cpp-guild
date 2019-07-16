#pragma once

#include <tuple>
#include <vector>

namespace Matrix {

// to do: T is numeric
template <typename T, unsigned N, typename SumFunc, typename AoiFunc>
constexpr T GetGenericShapeMaxSum(T (&matrix)[N][N], SumFunc &&sumFunc, AoiFunc &&aoiFunc) {
    auto init{ false };
    T sum{};

    const auto aoi{ aoiFunc() };
    for(unsigned row{ 0 }; row < N; ++row) {
        if(N < row+std::get<0>(aoi)) { break; }

        for(unsigned col{ 0 }; col < N; ++col) {
            if(N < col+std::get<1>(aoi)) { break; }

            const auto currentSum{ sumFunc(matrix, row, col) };
            if(!init || currentSum > sum) {
                init = true;
                sum = currentSum;
            }
        }
    }

    return sum;
}

template <typename T, unsigned N>
constexpr T GetHourglassMaxSum(T (&&matrix)[N][N]) {
    const auto aoi = []() {
        return std::make_tuple(3, 3);
    };

    const auto sum = [](const auto matrix, const auto row, const auto col) {
        return matrix[row][col] + matrix[row][col+1] + matrix[row][col+2] +
                                  matrix[row+1][col+1] +
               matrix[row+2][col] + matrix[row+2][col+1] + matrix[row+2][col+2];
    };

    return GetGenericShapeMaxSum(matrix, sum, aoi);
}

template <typename T, unsigned N>
constexpr std::vector<T> TraverseMatrixSpiral(T (&&matrix)[N][N]) {
    std::vector<T> traverse;

    unsigned row0{ 0 };
    unsigned col0{ 0 };

    unsigned row1{ N-1 };
    unsigned col1{ N-1 };

    unsigned currentRow{ 0 };
    unsigned currentCol{ 0 };

    unsigned dir{ 0 };
    for(unsigned i{ 0 }; i < N*N; ++i) {
        traverse.emplace_back(matrix[currentRow][currentCol]);

        switch(dir) {
            case 0: // RIGHT
            {
                if(currentCol != col1) {
                    ++currentCol;
                }
                else {
                    ++row0;
                    ++currentRow;
                    dir = 1;
                }
            }
            break;
            case 1: // DOWN
            {
                if(currentRow != row1) {
                    ++currentRow;
                }
                else {
                    --col1;
                    --currentCol;
                    dir = 2;
                }
            }
            break;
            case 2: // LEFT
            {
                if(currentCol != col0) {
                    --currentCol;
                }
                else {
                    --row1;
                    --currentRow;
                    dir = 3;
                }
            }
            break;
            case 3: // UP
            {
                if(currentRow != row0) {
                    --currentRow;
                }
                else {
                    ++row0;
                    ++currentCol;
                    dir = 0;
                }

            }
            break;
            default:
            break;
        }
    }

    return traverse;
}

}
