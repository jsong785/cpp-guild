#pragma once

#include <deque>
#include <iterator>
#include <vector>

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

template <typename InputList, typename InputListType = typename InputList::value_type>
constexpr auto InsertionSort(InputList &&list) {
    std::vector<InputListType> sorted;
    sorted.reserve(list.size());

    for(const auto &l : list) {
        auto sortedIter = std::begin(sorted);
        for(; sortedIter != std::end(sorted); ++sortedIter) {
            if(l < *sortedIter) {
                sorted.emplace(sortedIter, l);
                break;
            }
        }
        if(sortedIter == std::end(sorted)) {
            sorted.emplace_back(l);
        }
    }

    return sorted;
}

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

template <typename Iter>
constexpr Iter Partition(Iter low, Iter high) {
    auto pivot = high;
    auto firstHigh = low;
    for(auto i = low; i != pivot; ++i) {
        if(*i < *pivot) {
            std::swap(*i, *firstHigh++);
        }
    }
    std::swap(*firstHigh, *pivot);
    return firstHigh;
}

template <typename Iter>
constexpr void QuickSort(Iter low, Iter high) {
    if(low < high) {
        auto partition = Partition(low, high);
        QuickSort(low, std::prev(partition));
        QuickSort(std::next(partition), high);
    }
}

template <typename T>
constexpr T QuickSort(T &&list) {
    if(!list.empty()) {
        auto copy = std::forward<T>(list);
        QuickSort(copy.begin(), std::prev(copy.end()));
        return copy;
    }
    return list;
}

} // namespace Sort
