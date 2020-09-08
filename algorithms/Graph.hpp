#pragma once

#include <stack>
#include <queue>
#include <vector>

using Results = std::vector<std::size_t>;
using AdjList = std::vector<std::vector<std::size_t>>;

Results Dfs(const AdjList& graph, const std::size_t node) {
    Results results;
    results.reserve(graph.size());

    std::vector<bool> cache(graph.size(), false);

    std::vector<std::size_t> processQueue;
    processQueue.reserve(graph.size());
    processQueue.emplace_back(node);

    while(!processQueue.empty()) {
        const auto v = processQueue.back();
        processQueue.pop_back();

        cache[v] = true;
        results.emplace_back(v);
        for(auto n = graph[v].rbegin(); n != graph[v].rend(); ++n) {
            if(!cache[*n]) {
                processQueue.emplace_back(*n);
            }
        }
    }
    return results;
}

Results Bfs(const AdjList& graph, const std::size_t node) {
    Results results;
    results.reserve(graph.size());

    std::vector<bool> cache(graph.size(), false);

    std::queue<std::size_t> processQueue;
    processQueue.push(node);
    results.emplace_back(node);
    cache[node] = true;

    while(!processQueue.empty()) {
        const auto v = processQueue.front();
        processQueue.pop();

        for(const auto n : graph[v]) {
            if(!cache[n]) {
                cache[n] = true;
                results.emplace_back(n);
                processQueue.push(n);
            }
        }
    }

    return results;
}
