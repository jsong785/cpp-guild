#pragma once

#include <tuple>
#include <utility>


namespace details {
std::pair<Section, std::vector<int>::const_iterator>
CreateSectionAndIterate(std::vector<int>::const_iterator begin) {
    const auto a{ *begin++ };
    const auto b{ *begin++ };
    const auto c{ *begin++ };
    return { Section{ a, b, c }, begin };
}
}

using Section = std::tuple<int, int, int>;

Section CreateSection(const int a, const int b, const int c) {
    return Section{a, b, c};
}

std::vector<Section> Path(std::vector<int> numbers) {
    if(numbers.empty() || numbers.size() % 3 != 0) {
        return {};
    }
    std::vector<Section> sections;
    auto begin{ std::cbegin(numbers) };
    while(begin != std::cend(numbers)) {
        auto&& sectionAndIter{ details::CreateSectionAndIterate(begin) };
        sections.emplace_back(std::move(sectionAndIter.first));
        begin = std::move(sectionAndIter.second);
    }
    return sections;
}

enum class Path : std::size_t { A, B, C };

