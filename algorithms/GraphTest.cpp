#include "Graph.hpp"
#include "catch.hpp"

TEST_CASE("Graph - Dfs", "[graph]")
{
    CHECK(Dfs(AdjList{{1, 2}, {2}, {0, 3}, {3}}, 1) == Results{1, 2, 0, 3});
    CHECK(Dfs(AdjList{{2, 1}, {2, 3}, {0}, {3}}, 2) == Results{2, 0, 1, 3});
    CHECK(Dfs(AdjList{{1}, {2, 3}, {4, 5}, {6, 7}, {}, {}, {}, {}}, 0) == Results{0, 1, 2, 4, 5, 3, 6, 7});
}

TEST_CASE("Graph - Bfs", "[graph]")
{
    CHECK(Bfs(AdjList{{1, 2}, {2}, {0, 3}, {3}}, 2) == Results{2, 0, 3, 1});
    CHECK(Bfs(AdjList{{2, 1}, {2, 3}, {0}, {3}}, 1) == Results{1, 2, 3, 0});
    CHECK(Bfs(AdjList{{1}, {2, 3}, {4, 5}, {6, 7}, {}, {}, {}, {}}, 0) == Results{0, 1, 2, 3, 4, 5, 6, 7});
}
