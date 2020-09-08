#pragma once

#include <queue>
#include <vector>

using Results = std::vector<std::size_t>;
using AdjList = std::vector<std::vector<std::size_t>>;

Results Dfs(const AdjList& graph, const std::size_t node) {
    Results results;
    results.reserve(graph.size());

    std::queue<std::size_t> processQueue;
    processQueue.push(node);

    std::vector<bool> resultsCache(graph.size(), false);
    while(!processQueue.empty()) {
        const auto v = processQueue.front();
        processQueue.pop();
        if(resultsCache[v]) {
            continue;
        }
        resultsCache[v] = true;
        results.emplace_back(v);

        for(const auto n : graph[v]) {
            processQueue.push(n);
        }
    }
    return results;
}

Results Bfs(const AdjList& graph, const std::size_t node) {
    Results results;
    results.reserve(graph.size());

    std::vector<bool> cache(graph.size(), false);
    cache[node] = true;
    results.emplace_back(node);

    std::queue<std::size_t> processQueue;
    processQueue.push(node);
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
