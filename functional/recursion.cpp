//#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"
#include <algorithm>
#include <chrono>
#include <iterator>
#include <vector>

template <typename ReturnValue, typename Iterator, typename AppendIfFunc>
static ReturnValue accumulate_fast(Iterator &&begin, Iterator &&end, ReturnValue val, AppendIfFunc &&func);

template <typename FilterFunc, typename Iterator>
static std::vector<int> FilterTailRecursionHelper(Iterator &&begin, Iterator &&end, FilterFunc &&func, std::vector<int> results);

template <typename FilterFunc>
static std::vector<int> FilterTailRecursion(std::vector<int> list, FilterFunc &&func);

template <typename FilterFunc>
static auto AppendIf(FilterFunc &&func);

template <typename FilterFunc>
static std::vector<int> FilterFolding(std::vector<int> list, FilterFunc &&func);

template <typename FilterFunc>
static std::vector<int> FilterFoldingFast(std::vector<int> list, FilterFunc &&func);

template <typename FilterFunc>
static std::vector<int> Filter(std::vector<int> list, FilterFunc &&func);

static bool IsEvenNumber(const int num);

TEST_CASE("Filter")
{
    CHECK(Filter({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, IsEvenNumber) == std::vector<int>{1, 3, 5, 7, 9});
    CHECK(FilterTailRecursion({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, IsEvenNumber) == std::vector<int>{1, 3, 5, 7, 9});
    CHECK(FilterFolding({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, IsEvenNumber) == std::vector<int>{1, 3, 5, 7, 9});
    CHECK(FilterFoldingFast({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, IsEvenNumber) == std::vector<int>{1, 3, 5, 7, 9});

    // I'd use BENCHMARK(), but I'm having trouble getting that to compile
    auto start{ std::chrono::steady_clock::now() };
    for(int i{ 0 }; i < 100000; ++i) {
        Filter({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, IsEvenNumber);
    }
    auto end{ std::chrono::steady_clock::now() };
    WARN("filter benchmark ran in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::steady_clock::now();
    for(int i{ 0 }; i < 100000; ++i) {
        FilterTailRecursion({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, IsEvenNumber);
    }
    end = std::chrono::steady_clock::now();
    
    WARN("filter tail recursion benchmark ran in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::steady_clock::now();
    for(int i{ 0 }; i < 100000; ++i) {
        FilterFolding({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, IsEvenNumber);
    }
    end = std::chrono::steady_clock::now();
    
    WARN("filter folding benchmark ran in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::steady_clock::now();
    for(int i{ 0 }; i < 100000; ++i) {
        FilterFoldingFast({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, IsEvenNumber);
    }
    end = std::chrono::steady_clock::now();
    
    WARN("filter folding FAST benchmark ran in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}

bool IsEvenNumber(const int num) {
    return num % 2 == 0;
}

template <typename FilterFunc>
auto AppendIf(FilterFunc &&func) {
    return [f = std::forward<FilterFunc>(func)](std::vector<int> list, const int val){
        if(!f(val)) {
            list.emplace_back(val);
        }
        return list;
    };
}

template <typename FilterFunc, typename Iterator>
std::vector<int> FilterTailRecursionHelper(Iterator &&begin, Iterator &&end, FilterFunc &&func, std::vector<int> results) {
    if(begin == end) {
        return results;
    }
    if(!func(*begin)) {
        results.emplace_back(*begin);
    }
    return FilterTailRecursionHelper(std::forward<Iterator>(std::next(begin)), std::forward<Iterator>(end), std::forward<FilterFunc>(func), std::move(results));
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

template <typename FilterFunc>
std::vector<int> FilterFolding(std::vector<int> list, FilterFunc &&func)
{
    return std::accumulate(list.cbegin(), list.cend(), std::vector<int>{}, AppendIf(func));
}

template <typename FilterFunc>
std::vector<int> FilterFoldingFast(std::vector<int> list, FilterFunc &&func)
{
    return accumulate_fast(list.cbegin(), list.cend(), std::vector<int>{}, AppendIf(func));
}

template <typename ReturnValue, typename Iterator, typename AppendIfFunc>
ReturnValue accumulate_fast(Iterator &&begin, Iterator &&end, ReturnValue val, AppendIfFunc &&func)
{
    ReturnValue ret{ std::move(val) };
    for(auto i{ begin}; i != end; ++i) {
        ret = func(std::move(ret), *i);
    }
    return ret;
}
