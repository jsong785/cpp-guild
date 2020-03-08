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

