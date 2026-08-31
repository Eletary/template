// @title Dijkstra Shortest Paths
// @brief Single-source shortest paths in a graph with non-negative edge weights.
// @complexity O((n + m) log n)
// @tags graph, shortest-path, priority-queue

using i64 = long long;
constexpr i64 INF = std::numeric_limits<i64>::max() / 4;

struct Edge {
    int to;
    i64 weight;
};

std::vector<i64> dijkstra(const std::vector<std::vector<Edge>>& graph, int source) {
    const int n = static_cast<int>(graph.size());
    std::vector<i64> distance(n, INF);
    using State = std::pair<i64, int>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> queue;

    distance[source] = 0;
    queue.emplace(0, source);
    while (!queue.empty()) {
        auto [current_distance, vertex] = queue.top();
        queue.pop();
        if (current_distance != distance[vertex]) continue;

        for (const Edge& edge : graph[vertex]) {
            const i64 candidate = current_distance + edge.weight;
            if (candidate >= distance[edge.to]) continue;
            distance[edge.to] = candidate;
            queue.emplace(candidate, edge.to);
        }
    }
    return distance;
}
