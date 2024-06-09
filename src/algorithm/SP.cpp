#include "SP.h"
#include "PriorityQueue.h"

void SP::dijkstra(const ALGraph& graph, int start, int end) {
    Vector<int> dist(graph.size(), INT_MAX);
    dist[start] = 0;
    PriorityQueue<int, int> pq;
    pq.push(start, 0);

    while (!pq.empty()) {
        int u = pq.pop();

        for (const auto& edge : graph.edges(u)) {
            int v = edge.to;
            int weight = edge.weight;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(v, dist[v]);
            }
        }
    }

    printf("Odległość od %d do %d wynosi %d\n", start, end, dist[end]);
}

void SP::dijkstra(const IMGraph& graph, int start, int end) {
    Vector<int> dist(graph.size(), INT_MAX);
    dist[start] = 0;
    PriorityQueue<int, int> pq;
    pq.push(start, 0);

    while (!pq.empty()) {
        int u = pq.pop();

        for (int v = 0; v < graph.size(); ++v) {
            int weight = graph.weight(u, v);
            if (weight && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(v, dist[v]);
            }
        }
    }

    printf("Odległość od %d do %d wynosi %d\n", start, end, dist[end]);
}

void SP::bellman_ford(const ALGraph& graph, int start, int end) {
    Vector<int> dist(graph.size(), INT_MAX);
    dist[start] = 0;

    for (int i = 1; i < graph.size(); ++i) {
        for (const auto& edge : graph.get_all_edges()) {
            int u = edge.from;
            int v = edge.to;
            int weight = edge.weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (const auto& edge : graph.get_all_edges()) {
        int u = edge.from;
        int v = edge.to;
        int weight = edge.weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graf zawiera cykl o ujemnej wadze\n");
            return;
        }
    }

    printf("Odległość od %d do %d wynosi %d\n", start, end, dist[end]);
}

void SP::bellman_ford(const IMGraph& graph, int start, int end) {
    Vector<int> dist(graph.size(), INT_MAX);
    dist[start] = 0;

    for (int i = 1; i < graph.size(); ++i) {
        for (const auto& edge : graph.get_all_edges()) {
            int u = edge.from;
            int v = edge.to;
            int weight = edge.weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (const auto& edge : graph.get_all_edges()) {
        int u = edge.from;
        int v = edge.to;
        int weight = edge.weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graf zawiera cykl o ujemnej wadze\n");
            return;
        }
    }

    printf("Odległość od %d do %d wynosi %d\n", start, end, dist[end]);
}
