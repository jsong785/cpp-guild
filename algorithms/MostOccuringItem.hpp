#pragma once
#include <algorithm>
#include <unordered_map>

namespace count {

// assuming not empty
template <typename List> 
constexpr typename List::value_type MostOccuringItem(List &&list) {
    std::unordered_map<typename List::value_type, unsigned> count;
    for(const auto &l : list) {
        auto found = count.find(l);
        if(found != count.end()) {
            ++found->second;
        }
        else {
            count.insert(std::make_pair(l, 0));
        }
    }

    typename List::value_type currentVal{ std::begin(count)->first };
    unsigned currentCount{ std::begin(count)->second };
    for(const auto &c : count) {
        const auto newVal{ (c.second > currentCount) || (c.second == currentCount && c.first > currentVal) };
        if(newVal) {
            currentVal = c.first;
        }
    }

    return currentVal;
}

// assuming not empty
template <typename List> 
constexpr typename List::value_type MostOccuringItemSort(List &&list) {
    std::sort(std::begin(list), std::end(list));

    auto listIter{ std::begin(list) };
    auto candidate{ *listIter };
    auto candidateCount{ 1 };
    ++listIter;
    while(listIter != std::end(list) && *listIter == candidate) {
        ++candidateCount;
        ++listIter;
    }

    if(listIter == std::end(list)) {
        return candidate;
    }

    auto current{ *listIter };
    auto currentCount{ 1 };
    ++listIter;
    for(; listIter != std::end(list); ++listIter) {
        if(*listIter == current) { 
            ++currentCount;
        }
        else {
            if(currentCount > candidateCount || (currentCount == candidateCount && current > candidate)){ 
                candidate = current;
                candidateCount = currentCount;
            }
            current = *listIter;
            currentCount = 1;
        }
    }

    if(currentCount > candidateCount || (currentCount == candidateCount && current > candidate)){ 
        candidate = current;
        candidateCount = currentCount;
    }

    return candidate;
}

}
