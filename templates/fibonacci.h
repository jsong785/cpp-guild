#pragma once

#include <assert.h>
#include <cstdint>

constexpr int64_t CalculateFibonacci(const int64_t sequence) {
    assert(sequence >= 0);
    if (sequence == 0 || sequence == 1) {
        return sequence;
    }
    return CalculateFibonacci(sequence-1) + CalculateFibonacci(sequence-2);
}

template <std::size_t N>
struct FibonacciStruct {
    static const std::size_t value_type{ FibonacciStruct<N-1>::value_type + FibonacciStruct<N-2>::value_type };
};

template <>
struct FibonacciStruct<0> {
    static const std::size_t value_type{ 0 };
};

template <>
struct FibonacciStruct<1> {
    static const std::size_t value_type{ 1 };
};

