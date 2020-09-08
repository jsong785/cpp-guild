#pragma once

#include <queue>
#include <vector>

using Visited = std::vector<std::size_t>;
using AdjList = std::vector<std::vector<std::size_t>>;

Visited Dfs(const AdjList& graph, const std::size_t node) 
{
    Visited visited;
    visited.reserve(graph.size());

    std::queue<std::size_t> processQueue;
    processQueue.push(node);

    std::vector<bool> visitedCache(graph.size());
    while(!processQueue.empty()) {
        const auto v = processQueue.front();
        processQueue.pop();
        if(visitedCache[v]) {
            continue;
        }
        visitedCache[v] = true;
        visited.emplace_back(v);

        for(const auto n : graph[v]) {
            processQueue.push(n);
        }
    }
    return visited;
}

