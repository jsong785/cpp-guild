#pragma once

#include <vector>

using Visited = std::vector<std::size_t>;
using AdjList = std::vector<std::vector<std::size_t>>;

Visited DfsHelper(const AdjList& graph, const std::size_t node, std::vector<bool>& visitedCache) {
    if(visitedCache[node]) {
        return {};
    }
    visitedCache[node] = true;
    Visited visited{ node };

    const auto& neighbors = graph[node];
    for(const auto n : neighbors) {
        auto v = DfsHelper(graph, n, visitedCache);
        visited.insert(visited.end(), v.cbegin(), v.cend()); // POD, so move doesn't matter
    }
    return visited;
}

Visited Dfs(const AdjList& graph, const std::size_t node) 
{
    std::vector<bool> visitedCache(graph.size());
    return DfsHelper(graph, node, visitedCache);
}

