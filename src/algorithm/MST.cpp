#include "MST.h"
#include "PriorityQueue.h"
#include <iostream>
#include <limits>
#include <cmath>

void MST::prim(const ALGraph& graph) {
    int V = graph.vertices;
    Vector<int> key(V, std::numeric_limits<int>::max());
    Vector<bool> inMST(V, false);
    Vector<int> parent(V, -1);

    key[0] = 0;

    PriorityQueue<std::pair<int, int>, std::greater<std::pair<int, int> > > pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (const auto& [v, weight] : graph.adjacencyList[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            std::cout << parent[i] << " - " << i << std::endl;
        }
    }
}

void MST::prim(const IMGraph& graph) {
    int V = graph.vertices;
    Vector<int> key(V, std::numeric_limits<int>::max());
    Vector<bool> inMST(V, false);
    Vector<int> parent(V, -1);

    key[0] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;

        for (int v = 0; v < V; v++) {
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;
        }

        inMST[u] = true;

        for (int edgeIndex = 0; edgeIndex < graph.edges; edgeIndex++) {
            if (graph.incidenceMatrix[u][edgeIndex] != 0) {
                int v = -1;

                for (int i = 0; i < V; i++) {
                    if (graph.incidenceMatrix[i][edgeIndex] != 0 && i != u) {
                        v = i;
                        break;
                    }
                }

                int weight = std::abs(graph.incidenceMatrix[u][edgeIndex]);
                if (v != -1 && !inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                }
            }
        }
    }

    for (int i = 1; i < V; i++) {
        if (parent[i] != -1) {
            std::cout << parent[i] << " - " << i << std::endl;
        }
    }
}

void MST::kruskal(const ALGraph& graph) {
    int V = graph.vertices;
    Vector<Edge> edges;

    for (int u = 0; u < V; u++) {
        for (const auto& [v, weight] : graph.adjacencyList[u]) {
            if (u < v) {
                edges.push_back({u, v, weight});
            }
        }
    }

    sort_edges(edges);

    Vector<int> parent(V);
    Vector<int> rank(V, 0);
    for (int v = 0; v < V; v++) {
        parent[v] = v;
    }

    Vector<Edge> mstEdges;

    for (const auto& edge : edges) {
        int uRoot = find(parent, edge.src);
        int vRoot = find(parent, edge.dest);

        if (uRoot != vRoot) {
            mstEdges.push_back(edge);
            unite(parent, rank, uRoot, vRoot);
        }
    }

    for (const auto& edge : mstEdges) {
        std::cout << edge.src << " - " << edge.dest << " : " << edge.weight << std::endl;
    }
}

void MST::kruskal(const IMGraph& graph) {
    int V = graph.vertices;
    Vector<Edge> edges;

    for (int edgeIndex = 0; edgeIndex < graph.edges; edgeIndex++) {
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

    sort_edges(edges);

    Vector<int> parent(V);
    Vector<int> rank(V, 0);
    for (int v = 0; v < V; v++) {
        parent[v] = v;
    }

    Vector<Edge> mstEdges;

    for (const auto& edge : edges) {
        int uRoot = find(parent, edge.src);
        int vRoot = find(parent, edge.dest);

        if (uRoot != vRoot) {
            mstEdges.push_back(edge);
            unite(parent, rank, uRoot, vRoot);
        }
    }

    for (const auto& edge : mstEdges) {
        std::cout << edge.src << " - " << edge.dest << " : " << edge.weight << std::endl;
    }
}

void MST::sort_edges(Vector<Edge>& edges) {
    for (size_t i = 0; i < edges.size() - 1; ++i) {
        for (size_t j = 0; j < edges.size() - i - 1; ++j) {
            if (edges[j].weight > edges[j + 1].weight) {
                std::swap(edges[j], edges[j + 1]);
            }
        }
    }
}

int MST::find(Vector<int>& parent, int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void MST::unite(Vector<int>& parent, Vector<int>& rank, int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}
