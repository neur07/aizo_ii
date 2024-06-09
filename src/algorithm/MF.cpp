#include "MF.h"
#include "PriorityQueue.h"
#include <iostream>
#include <limits>
#include <queue>

bool MF::bfs(const ALGraph& graph, int source, int sink, Vector<int>& parent) {
    int V = graph.vertices;
    Vector<bool> visited(V, false);

    std::queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const auto& [v, capacity] : graph.adjacencyList[u]) {
            if (!visited[v] && capacity > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == sink) {
                    return true;
                }
            }
        }
    }

    return false;
}

int MF::fordFulkerson(ALGraph& graph, int source, int sink) {
    int V = graph.vertices;
    Vector<int> parent(V);
    int maxFlow = 0;

    while (bfs(graph, source, sink, parent)) {
        int pathFlow = std::numeric_limits<int>::max();
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            int capacity = 0;
            for (const auto& [adjV, cap] : graph.adjacencyList[u]) {
                if (adjV == v) {
                    capacity = cap;
                    break;
                }
            }
            pathFlow = std::min(pathFlow, capacity);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            for (auto& [adjV, cap] : graph.adjacencyList[u]) {
                if (adjV == v) {
                    cap -= pathFlow;
                    break;
                }
            }
            bool found = false;
            for (auto& [adjU, cap] : graph.adjacencyList[v]) {
                if (adjU == u) {
                    cap += pathFlow;
                    found = true;
                    break;
                }
            }
            if (!found) {
                graph.adjacencyList[v].emplace_back(u, pathFlow);
            }
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

bool MF::bfs(const IMGraph& graph, int source, int sink, Vector<int>& parent) {
    int V = graph.vertices;
    Vector<bool> visited(V, false);

    std::queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int edgeIndex = 0; edgeIndex < graph.edges; edgeIndex++) {
            if (graph.incidenceMatrix[u][edgeIndex] != 0) {
                int v = -1;
                for (int i = 0; i < V; i++) {
                    if (graph.incidenceMatrix[i][edgeIndex] != 0 && i != u) {
                        v = i;
                        break;
                    }
                }
                int capacity = std::abs(graph.incidenceMatrix[u][edgeIndex]);
                if (!visited[v] && capacity > 0) {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                    if (v == sink) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

int MF::fordFulkerson(IMGraph& graph, int source, int sink) {
    int V = graph.vertices;
    Vector<int> parent(V);
    int maxFlow = 0;

    while (bfs(graph, source, sink, parent)) {
        int pathFlow = std::numeric_limits<int>::max();
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            int capacity = 0;
            for (int edgeIndex = 0; edgeIndex < graph.edges; edgeIndex++) {
                if (graph.incidenceMatrix[u][edgeIndex] != 0 && std::abs(graph.incidenceMatrix[u][edgeIndex]) == capacity) {
                    capacity = std::abs(graph.incidenceMatrix[u][edgeIndex]);
                    break;
                }
            }
            pathFlow = std::min(pathFlow, capacity);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            for (int edgeIndex = 0; edgeIndex < graph.edges; edgeIndex++) {
                if (graph.incidenceMatrix[u][edgeIndex] != 0 && std::abs(graph.incidenceMatrix[u][edgeIndex]) == pathFlow) {
                    graph.incidenceMatrix[u][edgeIndex] -= pathFlow;
                    graph.incidenceMatrix[v][edgeIndex] += pathFlow;
                    break;
                }
            }
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}
