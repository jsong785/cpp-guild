#pragma once

#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace Matrix {

template <typename T, unsigned N, typename SumFunc, typename AoiFunc, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
constexpr T GetGenericShapeMaxSum(T (&&matrix)[N][N], SumFunc &&sumFunc, AoiFunc &&aoiFunc) {
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

template <typename T, unsigned N, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
constexpr T GetHourglassMaxSum(T (&&matrix)[N][N]) {
    const auto aoi = []() {
        return std::make_tuple(3, 3);
    };

    const auto sum = [](const auto matrix, const auto row, const auto col) {
        return matrix[row][col] + matrix[row][col+1] + matrix[row][col+2] +
                                  matrix[row+1][col+1] +
               matrix[row+2][col] + matrix[row+2][col+1] + matrix[row+2][col+2];
    };

    return GetGenericShapeMaxSum(std::forward<T[N][N]>(matrix), sum, aoi);
}

template <typename T, unsigned N>
constexpr std::vector<T> TraverseMatrixSpiral(T (&&matrix)[N][N]) {
    std::vector<T> traverse;
    traverse.reserve(N*N);

    unsigned row0{ 0 };
    unsigned col0{ 0 };

    unsigned row1{ N-1 };
    unsigned col1{ N-1 };

    unsigned currentRow{ 0 };
    unsigned currentCol{ 0 };

    enum class Direction{ Right, Down, Left, Up };
    auto dir{ Direction::Right };
    for(unsigned i{ 0 }; i < N*N; ++i) {
        traverse.emplace_back(matrix[currentRow][currentCol]);

        switch(dir) {
            case Direction::Right:
            {
                if(currentCol != col1) {
                    ++currentCol;
                }
                else {
                    ++row0;
                    ++currentRow;
                    dir = Direction::Down;
                }
            }
            break;
            case Direction::Down:
            {
                if(currentRow != row1) {
                    ++currentRow;
                }
                else {
                    --col1;
                    --currentCol;
                    dir = Direction::Left;
                }
            }
            break;
            case Direction::Left:
            {
                if(currentCol != col0) {
                    --currentCol;
                }
                else {
                    --row1;
                    --currentRow;
                    dir = Direction::Up;
                }
            }
            break;
            case Direction::Up:
            {
                if(currentRow != row0) {
                    --currentRow;
                }
                else {
                    ++row0;
                    ++currentCol;
                    dir = Direction::Right;
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
