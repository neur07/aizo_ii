#include "MST.h"
#include "PriorityQueue.h"

void MST::prim(const ALGraph& graph) {
    Vector<int> key(graph.size(), INT_MAX);
    Vector<bool> in_mst(graph.size(), false);
    Vector<int> parent(graph.size(), -1);
    key[0] = 0;
    PriorityQueue<int, int> pq;
    pq.push(0, 0);

    while (!pq.empty()) {
        int u = pq.pop();
        in_mst[u] = true;

        for (const auto& edge : graph.edges(u)) {
            int v = edge.to;
            int weight = edge.weight;
            if (!in_mst[v] && key[v] > weight) {
                key[v] = weight;
                pq.push(v, key[v]);
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < graph.size(); ++i)
        std::cout << parent[i] << " - " << i << std::endl;
}

void MST::prim(const IMGraph& graph) {
    Vector<int> key(graph.size(), INT_MAX);
    Vector<bool> in_mst(graph.size(), false);
    Vector<int> parent(graph.size(), -1);
    key[0] = 0;
    PriorityQueue<int, int> pq;
    pq.push(0, 0);

    while (!pq.empty()) {
        int u = pq.pop();
        in_mst[u] = true;

        for (int v = 0; v < graph.size(); ++v) {
            int weight = graph.weight(u, v);
            if (weight && !in_mst[v] && key[v] > weight) {
                key[v] = weight;
                pq.push(v, key[v]);
                parent[v] = u;
            }
        }
    }

    for (int i = 1; i < graph.size(); ++i)
        std::cout << parent[i] << " - " << i << std::endl;
}

void MST::kruskal(const ALGraph& graph) {
    Vector<Edge> edges = graph.get_all_edges();
    std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) { return a.weight < b.weight; });

    Vector<int> parent(graph.size());
    Vector<int> rank(graph.size(), 0);
    for (int i = 0; i < graph.size(); ++i)
        parent[i] = i;

    Vector<Edge> mst;
    for (const auto& edge : edges) {
        int u = edge.from;
        int v = edge.to;
        int set_u = find_set(parent, u);
        int set_v = find_set(parent, v);
        if (set_u != set_v) {
            mst.push_back(edge);
            union_set(parent, rank, set_u, set_v);
        }
    }

    for (const auto& edge : mst)
        std::cout << edge.from << " - " << edge.to << std::endl;
}

void MST::kruskal(const IMGraph& graph) {
    Vector<Edge> edges = graph.get_all_edges();
    std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) { return a.weight < b.weight; });

    Vector<int> parent(graph.size());
    Vector<int> rank(graph.size(), 0);
    for (int i = 0; i < graph.size(); ++i)
        parent[i] = i;

    Vector<Edge> mst;
    for (const auto& edge : edges) {
        int u = edge.from;
        int v = edge.to;
        int set_u = find_set(parent, u);
        int set_v = find_set(parent, v);
        if (set_u != set_v) {
            mst.push_back(edge);
            union_set(parent, rank, set_u, set_v);
        }
    }

    for (const auto& edge : mst)
        std::cout << edge.from << " - " << edge.to << std::endl;
}

int MST::find_set(Vector<int>& parent, int i) {
    if (parent[i] != i)
        parent[i] = find_set(parent, parent[i]);
    return parent[i];
}

void MST::union_set(Vector<int>& parent, Vector<int>& rank, int x, int y) {
    int root_x = find_set(parent, x);
    int root_y = find_set(parent, y);
    if (rank[root_x] < rank[root_y]) {
        parent[root_x] = root_y;
    } else if (rank[root_x] > rank[root_y]) {
        parent[root_y] = root_x;
    } else {
        parent[root_y] = root_x;
        rank[root_x]++;
    }
}
