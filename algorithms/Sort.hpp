#pragma once

#include <deque>
#include <iterator>
#include <vector>
#include <iostream>

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

/*template <typename T, template<typename> typename InputList>
constexpr auto InsertionSort(const InputList<T> &list) {
    std::vector<T> sorted;
    sorted.reserve(list.size());

    for(const auto &l : list) {
        for(auto i = std::begin(sorted); i != std::end(sorted); ++i) {
            if(l < i) {
                sorted.emplace(i, l);
            }
        }
    }

    return sorted;
}*/

template <typename Iter, typename IterType = typename Iter::value_type>
constexpr void Merge(Iter low, Iter mid, Iter high) {
    const auto populateDeque = [](const auto start, const auto end) {
        std::deque<IterType> deque;
        for(auto i = start; i != std::next(end); ++i) {
            deque.emplace_back(*i);
        }
        return deque;
    };

    auto lowList = populateDeque(low, mid);
    auto highList = populateDeque(std::next(mid), high);

    while(!lowList.empty() && !highList.empty()) {
        if(lowList.front() < highList.front()) {
            *low++ = lowList.front();
            lowList.pop_front();
        }
        else {
            *low++ = highList.front();
            highList.pop_front();
        }
    }

    while(!lowList.empty()) {
        *low++ = lowList.front();
        lowList.pop_front();
    }

    while(!highList.empty()) {
        *low++ = highList.front();
        highList.pop_front();
    }
}

template <typename Iter>
constexpr void MergeSort(Iter low, Iter high) {
    if(low < high) {
        const auto mid = low + static_cast<unsigned>(std::distance(low, high) * 0.5); // floor
        MergeSort(low, mid);
        MergeSort(mid+1, high);
        Merge(low, mid, high);
    }
}

template <typename T>
constexpr T MergeSort(T &&list) {
    if(!list.empty()) {
        auto copy = std::forward<T>(list);
        MergeSort(copy.begin(), std::prev(copy.end()));
        return copy;
    }
    return list;
}

} // namespace Sort
