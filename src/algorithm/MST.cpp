#include "MST.h"
#include <iostream>
#include <chrono>

using namespace std;

// Sortowanie krawędzi za pomocą algorytmu sortowania przez wybór
void MST::selectionSort(Edge* edges, size_t num_edges) {
    for (size_t i = 0; i < num_edges - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < num_edges; ++j) {
            if (edges[j].value < edges[min_idx].value) {
                min_idx = j;
            }
        }
        // Zamiana miejscami
        Edge temp = edges[i];
        edges[i] = edges[min_idx];
        edges[min_idx] = temp;
    }
}

// Implementacja algorytmu Kruskala dla grafu reprezentowanego listą sąsiedztwa
void MST::kruskal(const ALGraph& graph) {
    auto start_time = chrono::high_resolution_clock::now(); // Start pomiaru czasu

    size_t num_vertices = graph.get_vertex_count();
    size_t num_edges = graph.get_edge_count();

    Edge* edges = new Edge[num_edges];
    size_t index = 0;

    for (size_t u = 0; u < num_vertices; ++u) {
        const Edge* edge = graph.get_edges()[u];
        while (edge != nullptr) {
            edges[index++] = *edge;
            edge = edge->next_edge;
        }
    }

    // Sortowanie krawędzi za pomocą sortowania przez wybór
    selectionSort(edges, num_edges);

    size_t* tree_ids = new size_t[num_vertices];
    for (size_t i = 0; i < num_vertices; ++i) {
        tree_ids[i] = i;
    }

    size_t* result_buffer = new size_t[(num_vertices - 1) * 3];
    size_t result_index = 0;

    index = 0;
    while (result_index < num_vertices - 1 && index < num_edges) {
        Edge next_edge = edges[index++];

        size_t x = tree_ids[next_edge.start_vertex];
        size_t y = tree_ids[next_edge.end_vertex];

        if (x != y) {
            result_buffer[3 * result_index] = next_edge.start_vertex;
            result_buffer[3 * result_index + 1] = next_edge.end_vertex;
            result_buffer[3 * result_index + 2] = next_edge.value;

            for (size_t i = 0; i < num_vertices; ++i) {
                if (tree_ids[i] == x) {
                    tree_ids[i] = y;
                }
            }

            result_index++;
        }
    }

    auto stop_time = chrono::high_resolution_clock::now(); // Koniec pomiaru czasu
    auto duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);
    cout << "Czas działania algorytmu Kruskala (Lista Sąsiedztwa): " << duration.count() << " mikrosekund" << endl;

    cout << "Minimalne Drzewo Rozpinające (Lista Sąsiedztwa):" << endl;
    for (size_t i = 0; i < result_index; ++i) {
        cout << "Krawędź: " << result_buffer[3 * i] << " - " << result_buffer[3 * i + 1] << " Waga: " << result_buffer[3 * i + 2] << endl;
    }

    delete[] edges;
    delete[] tree_ids;
    delete[] result_buffer;
}

// Implementacja algorytmu Kruskala dla grafu reprezentowanego macierzą incydencji
void MST::kruskal(const IMGraph& graph) {
    auto start_time = chrono::high_resolution_clock::now(); // Start pomiaru czasu

    size_t num_vertices = graph.get_num_vertices();
    size_t num_edges = graph.get_num_edges();

    Edge* edges = new Edge[num_edges];
    size_t index = 0;

    for (size_t u = 0; u < num_vertices; ++u) {
        for (size_t v = 0; v < num_vertices; ++v) {
            int value = graph.get_weight(u, v);
            if (value != -1) {
                edges[index++] = {u, v, (size_t)value};
            }
        }
    }

    // Sortowanie krawędzi za pomocą sortowania przez wybór
    selectionSort(edges, num_edges);

    size_t* tree_ids = new size_t[num_vertices];
    for (size_t i = 0; i < num_vertices; ++i) {
        tree_ids[i] = i;
    }

    size_t* result_buffer = new size_t[(num_vertices - 1) * 3];
    size_t result_index = 0;

    index = 0;
    while (result_index < num_vertices - 1 && index < num_edges) {
        Edge next_edge = edges[index++];

        size_t x = tree_ids[next_edge.start_vertex];
        size_t y = tree_ids[next_edge.end_vertex];

        if (x != y) {
            result_buffer[3 * result_index] = next_edge.start_vertex;
            result_buffer[3 * result_index + 1] = next_edge.end_vertex;
            result_buffer[3 * result_index + 2] = next_edge.value;

            for (size_t i = 0; i < num_vertices; ++i) {
                if (tree_ids[i] == x) {
                    tree_ids[i] = y;
                }
            }

            result_index++;
        }
    }

    auto stop_time = chrono::high_resolution_clock::now(); // Koniec pomiaru czasu
    auto duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);
    cout << "Czas działania algorytmu Kruskala (Macierz Incydencji): " << duration.count() << " mikrosekund" << endl;

    cout << "Minimalne Drzewo Rozpinające (Macierz Incydencji):" << endl;
    for (size_t i = 0; i < result_index; ++i) {
        cout << "Krawędź: " << result_buffer[3 * i] << " - " << result_buffer[3 * i + 1] << " Waga: " << result_buffer[3 * i + 2] << endl;
    }

    delete[] edges;
    delete[] tree_ids;
    delete[] result_buffer;
}

// Implementacja algorytmu Prima dla grafu reprezentowanego listą sąsiedztwa
void MST::prim(const ALGraph& graph) {
    auto start_time = chrono::high_resolution_clock::now(); // Start pomiaru czasu

    size_t num_vertices = graph.get_vertex_count();

    int* key = new int[num_vertices];
    int* parent = new int[num_vertices];
    bool* inMST = new bool[num_vertices];

    for (size_t i =    0; i < num_vertices; ++i) {
        key[i] = numeric_limits<int>::max();
        parent[i] = -1;
        inMST[i] = false;
    }

    key[0] = 0;

    for (size_t count = 0; count < num_vertices - 1; ++count) {
        int min = numeric_limits<int>::max(), minIndex = -1;

        for (size_t v = 0; v < num_vertices; ++v) {
            if (!inMST[v] && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }

        inMST[minIndex] = true;

        const Edge* edge = graph.get_neighbors(minIndex);
        while (edge != nullptr) {
            size_t v = edge->end_vertex;
            if (!inMST[v] && edge->value < key[v]) {
                parent[v] = minIndex;
                key[v] = edge->value;
            }
            edge = edge->next_edge;
        }
    }

    auto stop_time = chrono::high_resolution_clock::now(); // Koniec pomiaru czasu
    auto duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);
    cout << "Czas działania algorytmu Prima (Lista Sąsiedztwa): " << duration.count() << " mikrosekund" << endl;

    for (size_t i = 1; i < num_vertices; ++i) {
        cout << parent[i] << " - " << i << endl;
    }

    delete[] key;
    delete[] parent;
    delete[] inMST;
}

// Implementacja algorytmu Prima dla grafu reprezentowanego macierzą incydencji
void MST::prim(const IMGraph& graph) {
    auto start_time = chrono::high_resolution_clock::now(); // Start pomiaru czasu

    size_t num_vertices = graph.get_num_vertices();

    int* key = new int[num_vertices];
    int* parent = new int[num_vertices];
    bool* inMST = new bool[num_vertices];

    for (size_t i = 0; i < num_vertices; ++i) {
        key[i] = numeric_limits<int>::max();
        parent[i] = -1;
        inMST[i] = false;
    }

    key[0] = 0;

    for (size_t count = 0; count < num_vertices - 1; ++count) {
        int min = numeric_limits<int>::max(), minIndex = -1;

        for (size_t v = 0; v < num_vertices; ++v) {
            if (!inMST[v] && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }

        inMST[minIndex] = true;

        for (size_t v = 0; v < num_vertices; ++v) {
            int weight = graph.get_weight(minIndex, v);
            if (weight != -1 && !inMST[v] && weight < key[v]) {
                parent[v] = minIndex;
                key[v] = weight;
            }
        }
    }

    auto stop_time = chrono::high_resolution_clock::now(); // Koniec pomiaru czasu
    auto duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);
    cout << "Czas działania algorytmu Prima (Macierz Incydencji): " << duration.count() << " mikrosekund" << endl;

    for (size_t i = 1; i < num_vertices; ++i) {
        cout << parent[i] << " - " << i << endl;
    }

    delete[] key;
    delete[] parent;
    delete[] inMST;
}

