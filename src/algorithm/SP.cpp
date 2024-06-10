#include "SP.h"
#include <iostream>
#include <limits>
#include <chrono>

using namespace std;

// Implementacja algorytmu Dijkstry dla grafu reprezentowanego listą sąsiedztwa
void SP::dijkstra(const ALGraph& graph, int start, int end) {
    auto start_time = chrono::high_resolution_clock::now(); // Start pomiaru czasu

    size_t num_vertices = graph.get_vertex_count();
    int* distance = new int[num_vertices];
    bool* visited = new bool[num_vertices];

    for (size_t i = 0; i < num_vertices; ++i) {
        distance[i] = numeric_limits<int>::max();
        visited[i] = false;
    }

    distance[start] = 0;

    for (size_t count = 0; count < num_vertices - 1; ++count) {
        int min = numeric_limits<int>::max(), minIndex = -1;

        for (size_t v = 0; v < num_vertices; ++v) {
            if (!visited[v] && distance[v] <= min) {
                min = distance[v];
                minIndex = v;
            }
        }

        int u = minIndex;
        visited[u] = true;

        const Edge* edge = graph.get_neighbors(u);
        while (edge != nullptr) {
            int v = edge->end_vertex;
            if (!visited[v] && distance[u] != numeric_limits<int>::max() && distance[u] + edge->value < distance[v]) {
                distance[v] = distance[u] + edge->value;
            }
            edge = edge->next_edge;
        }
    }

    auto stop_time = chrono::high_resolution_clock::now(); // Koniec pomiaru czasu
    auto duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);
    cout << "Czas działania algorytmu Dijkstry (Lista Sąsiedztwa): " << duration.count() << " mikrosekund" << endl;

    for (size_t i = 0; i < num_vertices; ++i) {
        cout << "Odległość od " << start << " do " << i << " wynosi " << distance[i] << endl;
    }

    delete[] distance;
    delete[] visited;
}

// Implementacja algorytmu Dijkstry dla grafu reprezentowanego macierzą incydencji
void SP::dijkstra(const IMGraph& graph, int start, int end) {
    auto start_time = chrono::high_resolution_clock::now(); // Start pomiaru czasu

    size_t num_vertices = graph.get_num_vertices();
    int* distance = new int[num_vertices];
    bool* visited = new bool[num_vertices];

    for (size_t i = 0; i < num_vertices; ++i) {
        distance[i] = numeric_limits<int>::max();
        visited[i] = false;
    }

    distance[start] = 0;

    for (size_t count = 0; count < num_vertices - 1; ++count) {
        int min = numeric_limits<int>::max(), minIndex = -1;

        for (size_t v = 0; v < num_vertices; ++v) {
            if (!visited[v] && distance[v] <= min) {
                min = distance[v];
                minIndex = v;
            }
        }

        int u = minIndex;
        visited[u] = true;

        for (size_t v = 0; v < num_vertices; ++v) {
            int weight = graph.get_weight(u, v);
            if (weight != -1 && !visited[v] && distance[u] != numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    auto stop_time = chrono::high_resolution_clock::now(); // Koniec pomiaru czasu
    auto duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);
    cout << "Czas działania algorytmu Dijkstry (Macierz Incydencji): " << duration.count() << " mikrosekund" << endl;

    for (size_t i = 0; i < num_vertices; ++i) {
        cout << "Odległość od " << start << " do " << i << " wynosi " << distance[i] << endl;
    }

    delete[] distance;
    delete[] visited;
}

// Implementacja algorytmu Bellmana-Forda dla grafu reprezentowanego listą sąsiedztwa
void SP::bellman_ford(const ALGraph& graph, int start, int dest) {
    auto start_time = chrono::high_resolution_clock::now(); // Start pomiaru czasu

    size_t num_vertices = graph.get_vertex_count();
    size_t num_edges = graph.get_edge_count();

    int* distance = new int[num_vertices];
    for (size_t i = 0; i < num_vertices; ++i) {
        distance[i] = numeric_limits<int>::max();
    }
    distance[start] = 0;

    Edge* edges = new Edge[num_edges];
    size_t index = 0;

    for (size_t u = 0; u < num_vertices; ++u) {
        const Edge* edge = graph.get_edges()[u];
        while (edge != nullptr) {
            edges[index++] = *edge;
            edge = edge->next_edge;
        }
    }

    for (size_t i = 1; i < num_vertices; ++i) {
        for (size_t j = 0; j < num_edges; ++j) {
            int u = edges[j].start_vertex;
            int v = edges[j].end_vertex;
            int weight = edges[j].value;
            if (distance[u] != numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    auto stop_time = chrono::high_resolution_clock::now(); // Koniec pomiaru czasu
    auto duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);
    cout << "Czas działania algorytmu Bellmana-Forda (Lista Sąsiedztwa): " << duration.count() << " mikrosekund" << endl;

    for (size_t i = 0; i < num_vertices; ++i) {
        cout << "Odległość od " << start << " do " << i << " wynosi " << distance[i] << endl;
    }

    delete[] distance;
    delete[] edges;
}

// Implementacja algorytmu Bellmana-Forda dla grafu reprezentowanego macierzą incydencji
void SP::bellman_ford(const IMGraph& graph, int start, int dest) {
    auto start_time = chrono::high_resolution_clock::now(); // Start pomiaru czasu

    size_t num_vertices = graph.get_num_vertices();
    size_t num_edges = graph.get_num_edges();

    int* distance = new int[num_vertices];
    for (size_t i = 0; i < num_vertices; ++i) {
        distance[i] = numeric_limits<int>::max();
    }
    distance[start] = 0;

    Edge* edges = new Edge[num_edges];
    size_t index = 0;

    for (size_t u = 0; u < num_vertices; ++u) {
        for (size_t v = 0; v < num_vertices; ++v) {
            int weight = graph.get_weight(u, v);
            if (weight != -1) {
                edges[index++] = {u, v, static_cast<size_t>(weight)};
            }
        }
    }

    for (size_t i = 1; i < num_vertices; ++i) {
        for (size_t j = 0; j < num_edges; ++j) {
            int u = edges[j].start_vertex;
            int v = edges[j].end_vertex;
            int weight = edges[j].value;
            if (distance[u] != numeric_limits<int>::max() && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    auto stop_time = chrono::high_resolution_clock::now(); // Koniec pomiaru czasu
    auto duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);
    cout << "Czas działania algorytmu Bellmana-Forda (Macierz Incydencji): " << duration.count() << " mikrosekund" << endl;

    for (size_t i = 0; i < num_vertices; ++i) {
        cout << "Odległość od " << start << " do " << i << " wynosi " << distance[i] << endl;
    }

    delete[] distance;
    delete[] edges;
}
