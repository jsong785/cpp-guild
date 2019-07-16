#pragma once

#include <vector>

namespace Matrix {

template <typename T, unsigned N>
constexpr std::vector<T> TraverseMatrixSpiral(const T (&matrix)[N][N]) {
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
