//#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"
#include <algorithm>
#include <chrono>
#include <iterator>
#include <vector>

template <typename FilterFunc, typename Iterator>
std::vector<int> FilterTailRecursionHelper(Iterator &&begin, Iterator &&end, FilterFunc &&func, std::vector<int> results) {
    if(begin == end) {
        return results;
    }
    if(!func(*begin)) {
        results.emplace_back(*begin);
    }
    return FilterTailRecursionHelper(std::forward<Iterator>(std::next(begin)), std::forward<Iterator>(end), func, std::move(results));
}

template <typename FilterFunc>
std::vector<int> FilterTailRecursion(std::vector<int> list, FilterFunc &&func) {
    return FilterTailRecursionHelper(std::begin(list), std::end(list), func, {});
}


template <typename FilterFunc>
std::vector<int> Filter(std::vector<int> list, FilterFunc &&func) {
    list.erase(
        std::remove_if(list.begin(), list.end(), func),
        list.end()
    );
    return list;
}

static bool IsEvenNumber(const int num) {
    return num % 2 == 0;
}

TEST_CASE("Filter")
{
    CHECK(Filter({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, IsEvenNumber) == std::vector<int>{1, 3, 5, 7, 9});
    CHECK(FilterTailRecursion({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, IsEvenNumber) == std::vector<int>{1, 3, 5, 7, 9});

    // I'd use BENCHMARK(), but I'm having trouble getting that to compile
    WARN("Starting filter benchmark");
    auto start{ std::chrono::steady_clock::now() };
    for(int i{ 0 }; i < 10000; ++i) {
        Filter({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, IsEvenNumber);
    }
    auto end{ std::chrono::steady_clock::now() };
    WARN("filter benchmark ran in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    WARN("Starting filter tail recursion benchmark");

    start = std::chrono::steady_clock::now();
    for(int i{ 0 }; i < 10000; ++i) {
        FilterTailRecursion({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, IsEvenNumber);
    }
    end = std::chrono::steady_clock::now();
    
    WARN("filter tail recursion benchmark ran in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}

