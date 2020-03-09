#include "fibonacci.h"

static_assert(CalculateFibonacci(0) == 0);
static_assert(CalculateFibonacci(1) == 1);
static_assert(CalculateFibonacci(2) == 1);
static_assert(CalculateFibonacci(3) == 2);
static_assert(CalculateFibonacci(4) == 3);
static_assert(CalculateFibonacci(5) == 5);
static_assert(CalculateFibonacci(6) == 8);
static_assert(CalculateFibonacci(7) == 13);
static_assert(CalculateFibonacci(8) == 21);


static_assert(FibonacciStruct<0>::value_type == 0);
static_assert(FibonacciStruct<1>::value_type == 1);
static_assert(FibonacciStruct<2>::value_type == 1);
static_assert(FibonacciStruct<3>::value_type == 2);
static_assert(FibonacciStruct<4>::value_type == 3);
static_assert(FibonacciStruct<5>::value_type == 5);
static_assert(FibonacciStruct<6>::value_type == 8);
static_assert(FibonacciStruct<7>::value_type == 13);
static_assert(FibonacciStruct<8>::value_type == 21);

