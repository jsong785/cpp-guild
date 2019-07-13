#pragma once
#include <unordered_map>

namespace count {

// assuming not empty
template <typename List> 
constexpr typename List::value_type MostOccuringItem(List &&list) {
    typename List::value_type ret{ 0 };

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

}
