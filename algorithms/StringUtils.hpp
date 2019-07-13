#pragma once

namespace StringUtils {

template <typename T>
constexpr unsigned StrLen(const T *str) {
    unsigned sz{ 0 };
    for(; *str != 0; ++str, ++sz);
    return sz;
}

template <typename T>
constexpr bool StrIsEqual(const T* one, const T *two) {
    for(; *one != 0; ++one, ++two) {
        if(*one != *two) {
            return false;
        }
    }
    return *one == *two;
}

template <typename T>
constexpr void StrCpy(T* dest, const T *src) {
    // not safe
    while(*src != 0) {
        *dest++ = *src++;
    }
    *dest = *src; // copy nul
}

} // namespace StringUtils
