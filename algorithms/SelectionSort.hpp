#pragma once

namespace Sort{

template <typename T>
constexpr void SelectionSort(T *str, const unsigned len) {
    for(unsigned i{ 0 }; i < len; ++i) {
        unsigned min{ i };
        for(unsigned j{ i+1 }; j < len; ++j) {
            if(str[j] < str[min]) {
                min = j;
            }
        }
        std::swap(str[i], str[min]);
    }
}

} // namespace Srt
