#include "Graph.hpp"
#include "catch.hpp"

TEST_CASE("Graph - Dfs", "[graph]")
{
    CHECK(Dfs(AdjList{{1, 2}, {2}, {0, 3}, {3}}, 1) == Visited{1, 2, 0, 3});
    CHECK(Dfs(AdjList{{2, 1}, {2, 3}, {0}, {3}}, 2) == Visited{2, 0, 1, 3});
}
