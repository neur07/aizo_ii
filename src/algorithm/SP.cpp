#include "SP.h"
#include <iostream>
#include <limits>

using namespace std;

void SP::dijkstra(const ALGraph& graph, int src, int dest) {
    int vertices = graph.get_vertices();
    int* dist = new int[vertices];
    bool* sptSet = new bool[vertices];

    for (int i = 0; i < vertices; ++i) {
        dist[i] = numeric_limits<int>::max();
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < vertices - 1; ++count) {
        int u = -1;
        for (int i = 0; i < vertices; ++i)
            if (!sptSet[i] && (u == -1 || dist[i] < dist[u]))
                u = i;

        sptSet[u] = true;
        Edge* edges = graph.get_edges(u);
        int edge_count = graph.get_edge_count(u);
        for (int i = 0; i < edge_count; ++i) {
            int v = edges[i].dest;
            int weight = edges[i].weight;
            if (!sptSet[v] && dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    print_solution(dist, vertices);

    delete[] dist;
    delete[] sptSet;
}

void SP::dijkstra(const IMGraph& graph, int src, int dest) {
    int vertices = graph.get_vertices(); // Liczba wierzchołkow
    int edges = graph.get_edges(); // Liczba krawedzi
    int* dist = new int[vertices];  // Odległości do kolejnych wierzchołkow
    bool* sptSet = new bool[vertices]; 

    for (int i = 0; i < vertices; ++i) {
        dist[i] = numeric_limits<int>::max();
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < vertices - 1; ++count) {
        int u = -1;
        for (int i = 0; i < vertices; ++i)
            if (!sptSet[i] && (u == -1 || dist[i] < dist[u]))
                u = i;

        sptSet[u] = true;
        const int* incidence_row = graph.get_incidence_row(u);
        for (int j = 0; j < edges; ++j) {
            if (incidence_row[j] != 0) {
                int v = graph.get_other_vertex(u, j);
                int weight = incidence_row[j];
                if (!sptSet[v] && dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    print_solution(dist, vertices);

    delete[] dist;
    delete[] sptSet;
}

void SP::bellman_ford(const ALGraph& graph, int src, int dest) {
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

    int* dist = new int[vertices];
    for (int i = 0; i < vertices; ++i) {
        dist[i] = numeric_limits<int>::max();
    }
    dist[src] = 0;

    for (int i = 1; i < vertices; ++i) {
        for (int j = 0; j < total_edges; ++j) {
            int u = edges[j].dest;
            int v = edges[j].weight;
            int weight = edges[j].weight;
            if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (int i = 0; i < total_edges; ++i) {
        int u = edges[i].dest;
        int v = edges[i].weight;
        int weight = edges[i].weight;
        if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
            printsep("Graf zawiera cykl o ujemnych wagach");
            return;
        }
    }

    print_solution(dist, vertices);

    delete[] edges;
    delete[] dist;
}

void SP::bellman_ford(const IMGraph& graph, int src, int dest) {
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

    int* dist = new int[vertices];
    for (int i = 0; i < vertices; ++i) {
        dist[i] = numeric_limits<int>::max();
    }
    dist[src] = 0;

    for (int i = 1; i < vertices; ++i) {
        for (int j = 0; j < edge_index; ++j) {
            int u = edge_list[j].dest;
            int v = graph.get_other_vertex(u, j);
            int weight = edge_list[j].weight;
            if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (int i = 0; i < edge_index; ++i) {
        int u = edge_list[i].dest;
        int v = graph.get_other_vertex(u, i);
        int weight = edge_list[i].weight;
        if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
            printsep("Graf zawiera cykl o ujemnych wagach");
            return;
        }
    }

    print_solution(dist, vertices);

    delete[] edge_list;
    delete[] dist;
}

void SP::print_solution(int dist[], int vertices) {
    printsep("Wierz. | Odległość");
    for (int i = 0; i < vertices; i++) {
        printf("%6d | %9d\n", i, dist[i]);
    }
}
