#include "SP.h"
#include "PriorityQueue.h"
#include "Edges.h"
#include <iostream>
#include <limits>

void SP::dijkstra(const ALGraph& graph, int start) {
    int V = graph.vertices;
    Vector<int> dist(V, std::numeric_limits<int>::max());
    Vector<bool> visited(V, false);

    dist[start] = 0;

    PriorityQueue<std::pair<int, int>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const auto& [v, weight] : graph.adjacencyList[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 0; i < V; i++) {
        std::cout << "Distance from " << start << " to " << i << " is " << dist[i] << std::endl;
    }
}

void SP::bellman_ford(const ALGraph& graph, int start) {
    int V = graph.vertices;
    Vector<int> dist(V, std::numeric_limits<int>::max());

    dist[start] = 0;

    Vector<Edge> edges;
    for (int u = 0; u < V; u++) {
        for (const auto& [v, weight] : graph.adjacencyList[u]) {
            edges.push_back({u, v, weight});
        }
    }

    for (int i = 1; i <= V - 1; i++) {
        for (const auto& edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int weight = edge.weight;
            if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (const auto& edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        int weight = edge.weight;
        if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
            std::cout << "Graph contains negative weight cycle" << std::endl;
            return;
        }
    }

    for (int i = 0; i < V; i++) {
        std::cout << "Distance from " << start << " to " << i << " is " << dist[i] << std::endl;
    }
}

void SP::dijkstra(const IMGraph& graph, int start) {
    int V = graph.vertices;
    int E = graph.edges;
    Vector<int> dist(V, std::numeric_limits<int>::max());
    Vector<bool> visited(V, false);

    dist[start] = 0;

    PriorityQueue<std::pair<int, int>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (int edgeIndex = 0; edgeIndex < E; edgeIndex++) {
            if (graph.incidenceMatrix[u][edgeIndex] != 0) {
                int v = -1;

                for (int i = 0; i < V; i++) {
                    if (graph.incidenceMatrix[i][edgeIndex] != 0 && i != u) {
                        v = i;
                        break;
                    }
                }

                int weight = std::abs(graph.incidenceMatrix[u][edgeIndex]);
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    for (int i = 0; i < V; i++) {
        std::cout << "Distance from " << start << " to " << i << " is " << dist[i] << std::endl;
    }
}

void SP::bellman_ford(const IMGraph& graph, int start) {
    int V = graph.vertices;
    int E = graph.edges;
    Vector<int> dist(V, std::numeric_limits<int>::max());

    dist[start] = 0;

    Vector<Edge> edges;
    for (int edgeIndex = 0; edgeIndex < E; edgeIndex++) {
        int u = -1, v = -1;
        for (int i = 0; i < V; i++) {
            if (graph.incidenceMatrix[i][edgeIndex] == 1) {
                u = i;
            } else if (graph.incidenceMatrix[i][edgeIndex] == -1) {
                v = i;
            }
        }
        if (u != -1 && v != -1) {
            edges.push_back({u, v, std::abs(graph.incidenceMatrix[u][edgeIndex])});
        }
    }

    for (int i = 1; i <= V - 1; i++) {
        for (const auto& edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int weight = edge.weight;
            if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (const auto& edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        int weight = edge.weight;
        if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
            std::cout << "Graph contains negative weight cycle" << std::endl;
            return;
        }
    }

    for (int i = 0; i < V; i++) {
        std::cout << "Distance from " << start << " to " << i << " is " << dist[i] << std::endl;
    }
}
