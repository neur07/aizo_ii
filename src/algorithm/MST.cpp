#include "MST.h"
#include <iostream>
#include <limits>

using namespace std;

void MST::prim(const ALGraph& graph) {
    int vertices = graph.get_vertices();
    bool* inMST = new bool[vertices]();
    int* key = new int[vertices];
    int* parent = new int[vertices];
    for (int i = 0; i < vertices; ++i) {
        key[i] = numeric_limits<int>::max();
        parent[i] = -1;
    }

    key[0] = 0;
    for (int count = 0; count < vertices - 1; ++count) {
        int u = -1;
        for (int i = 0; i < vertices; ++i)
            if (!inMST[i] && (u == -1 || key[i] < key[u]))
                u = i;

        inMST[u] = true;
        Edge* edges = graph.get_edges(u);
        int edge_count = graph.get_edge_count(u);
        for (int i = 0; i < edge_count; ++i) {
            int v = edges[i].dest;
            int weight = edges[i].weight;
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    printsep("Algorytm MST (Prim) dla Listy sąsiedztwa");
    for (int i = 1; i < vertices; ++i)
        cout << parent[i] << " - " << i << " : " << key[i] << "\n";

    delete[] inMST;
    delete[] key;
    delete[] parent;
}

void MST::prim(const IMGraph& graph) {
    int vertices = graph.get_vertices();
    int edges = graph.get_edges();
    bool* inMST = new bool[vertices]();
    int* key = new int[vertices];
    int* parent = new int[vertices];
    for (int i = 0; i < vertices; ++i) {
        key[i] = numeric_limits<int>::max();
        parent[i] = -1;
    }

    key[0] = 0;
    for (int count = 0; count < vertices - 1; ++count) {
        int u = -1;
        for (int i = 0; i < vertices; ++i)
            if (!inMST[i] && (u == -1 || key[i] < key[u]))
                u = i;

        inMST[u] = true;
        const int* incidence_row = graph.get_incidence_row(u);
        for (int j = 0; j < edges; ++j) {
            if (incidence_row[j] != 0) {
                int v = graph.get_other_vertex(u, j);
                int weight = incidence_row[j];
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                }
            }
        }
    }

    printsep("Algorytm MST (Prim) dla Macierzy incydencji");
    for (int i = 1; i < vertices; ++i)
        cout << parent[i] << " - " << i << " : " << key[i] << "\n";

    delete[] inMST;
    delete[] key;
    delete[] parent;
}

void MST::kruskal(const ALGraph& graph) {
    int vertices = graph.get_vertices();
    int total_edges = 0;
    for (int i = 0; i < vertices; ++i) {
        total_edges += graph.get_edge_count(i);
    }

    Edge* edges = new Edge[total_edges];
    int edge_index = 0;
    for (int i = 0; i < vertices; ++i) {
        Edge* vertex_edges = graph.get_edges(i);
        int edge_count = graph.get_edge_count(i);
        for (int j = 0; j < edge_count; ++j) {
            edges[edge_index++] = vertex_edges[j];
        }
    }

    sort_edges(edges, total_edges);

    int* parent = new int[vertices];
    int* rank = new int[vertices];

    for (int i = 0; i < vertices; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }

    int mst_edges = 0;
    int mst_cost = 0;

    printsep("Algorytm MST (Kruskal) dla Listy sąsiedztwa");
    for (int i = 0; i < total_edges && mst_edges < vertices - 1; ++i) {
        int u = find(parent, edges[i].dest);
        int v = find(parent, edges[i].weight);

        if (u != v) {
            cout << edges[i].dest << " - " << edges[i].weight << " : " << edges[i].weight << "\n";
            unite(parent, rank, u, v);
            mst_cost += edges[i].weight;
            ++mst_edges;
        }
    }

    cout << "Całkowita waga: " << mst_cost << "\n";

    delete[] edges;
    delete[] parent;
    delete[] rank;
}

void MST::kruskal(const IMGraph& graph) {
    int vertices = graph.get_vertices();
    int edges = graph.get_edges();
    Edge* edge_list = new Edge[edges];

    int edge_index = 0;
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < edges; ++j) {
            if (graph.get_incidence_row(i)[j] != 0) {
                edge_list[edge_index].dest = i;
                edge_list[edge_index].weight = graph.get_incidence_row(i)[j];
                ++edge_index;
            }
        }
    }

    sort_edges(edge_list, edges);

    int* parent = new int[vertices];
    int* rank = new int[vertices];

    for (int i = 0; i < vertices; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }

    int mst_edges = 0;
    int mst_cost = 0;

    printsep("Algorytm MST (Kruskal) dla Macierzy incydencji");
    for (int i = 0; i < edges && mst_edges < vertices - 1; ++i) {
        int u = find(parent, edge_list[i].dest);
        int v = find(parent, edge_list[i].weight);

        if (u != v) {
            cout << edge_list[i].dest << " - " << edge_list[i].weight << " : " << edge_list[i].weight << "\n";
            unite(parent, rank, u, v);
            mst_cost += edge_list[i].weight;
            ++mst_edges;
        }
    }

    cout << "Całkowita waga: " << mst_cost << "\n";

    delete[] edge_list;
    delete[] parent;
    delete[] rank;
}

void MST::sort_edges(Edge* edges, int edge_count) {
    for (int i = 0; i < edge_count - 1; ++i) {
        for (int j = 0; j < edge_count - i - 1; ++j) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

int MST::find(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void MST::unite(int parent[], int rank[], int x, int y) {
    int root_x = find(parent, x);
    int root_y = find(parent, y);

    if (rank[root_x] < rank[root_y])
        parent[root_x] = root_y;
    else if (rank[root_x] > rank[root_y])
        parent[root_y] = root_x;
    else {
        parent[root_y] = root_x;
        ++rank[root_x];
    }
}
