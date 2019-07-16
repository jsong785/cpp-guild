#include "Matrix.hpp"
#include "catch.hpp"

using namespace Matrix;

TEST_CASE("Matrix", "[Spiral]")
{
    CHECK(TraverseMatrixSpiral({{ 0 }}) == std::vector<int>{ 0 });
    CHECK(TraverseMatrixSpiral({ { 0, 1 }, 
                                 { 2, 3 } }) == std::vector<int>{ 0, 1, 3, 2 });

    CHECK(TraverseMatrixSpiral({ { 0, 1, 2 }, 
                                 { 3, 4, 5 },
                                 { 6, 7, 8 } }) == std::vector<int>{ 0, 1, 2, 5, 8, 7, 6, 3, 4 });

    CHECK(TraverseMatrixSpiral({ { 0,  1,  2,  3  }, 
                                 { 4,  5,  6,  7  },
                                 { 8,  9,  10, 11 },
                                 { 12, 13, 14, 15 }}) == std::vector<int>{ 0, 1, 2, 3, 7, 11, 15, 14, 13, 12, 8, 4, 5, 6, 10, 9 });
}
