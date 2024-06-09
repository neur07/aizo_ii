#include "IMGraph.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

IMGraph::IMGraph(bool dir) : vertices(0), edges(0), directed(dir) {}

int IMGraph::size() {
    return vertices;
}

void IMGraph::allocate_matrix() {
    incidenceMatrix.resize(vertices);
    for (int i = 0; i < vertices; ++i) {
        incidenceMatrix[i].resize(edges);
    }
}

void IMGraph::add_edge(int u, int v, int weight) {
    if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
        incidenceMatrix[u][edges] = directed ? -weight : weight;
        incidenceMatrix[v][edges] = weight;
    }
}

void IMGraph::load_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Błąd otwarcia pliku!" << std::endl;
        return;
    }

    file >> vertices >> edges;
    allocate_matrix();

    int start, end, weight;
    for (int i = 0; i < edges; ++i) {
        file >> start >> end >> weight;
        add_edge(start, end, weight);
    }
    std::cout << "Pomyślnie wczytano macierz incydencji" << std::endl;
}

void IMGraph::generate_random_graph(int v, int e) {
    vertices = v;
    edges = e;
    allocate_matrix();

    int* src = new int[e];
    int* dest = new int[e];
    int* weights = new int[e];

    std::srand(std::time(nullptr));
    for (int i = 0; i < e; ++i) {
        src[i] = std::rand() % vertices;
        dest[i] = std::rand() % vertices;
        weights[i] = (std::rand() % 100) + 1;
    }

    for (int i = 0; i < e; ++i) {
        add_edge(src[i], dest[i], weights[i]);
    }

    delete[] src;
    delete[] dest;
    delete[] weights;
}

void IMGraph::print_graph() const {
    printf("\nGraf %skierowany (Macierz Incydencji):\n\n", directed ? "" : "nie ");
    printf("    ");
    for (int i = 1; i <= edges; ++i) printf("#%-3d ", i);
    std::cout << std::endl;
    for (int i = 0; i < vertices; ++i) {
        printf("%2d: ", i);
        for (int j = 0; j < edges; ++j) {
            printf("%4d ", incidenceMatrix[i][j]);
        }
        std::cout << std::endl;
    }
}

Vector<Edge> IMGraph::get_edges() const {
    Vector<Edge> edges_list;
    for (int i = 0; i < edges; ++i) {
        int u = -1, v = -1, weight = 0;
        for (int j = 0; j < vertices; ++j) {
            if (incidenceMatrix[j][i] != 0) {
                if (u == -1) {
                    u = j;
                    weight = incidenceMatrix[j][i];
                } else {
                    v = j;
                }
            }
        }
        if (u != -1 && v != -1) {
            edges_list.push_back({u, v, weight});
        }
    }
    return edges_list;
}

Vector<int> IMGraph::get_neighbors(int v) const {
    Vector<int> neighbors;
    for (int i = 0; i < edges; ++i) {
        if (incidenceMatrix[v][i] != 0) {
            for (int j = 0; j < vertices; ++j) {
                if (j != v && incidenceMatrix[j][i] != 0) {
                    neighbors.push_back(j);
                }
            }
        }
    }
    return neighbors;
}

int IMGraph::get_weight(int u, int v) const {
    for (int i = 0; i < edges; ++i) {
        if (incidenceMatrix[u][i] != 0 && incidenceMatrix[v][i] != 0) {
            return incidenceMatrix[v][i];
        }
    }
    return 0; // lub inna wartość wskazująca na brak krawędzi
}
