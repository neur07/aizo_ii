#include "ALGraph.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

ALGraph::ALGraph(bool dir) : vertices(0), directed(dir) {}

int ALGraph::size() {
    return vertices;
}

void ALGraph::allocate_list() {
    adjacencyList.resize(vertices);
}

void ALGraph::add_edge(int u, int v, int weight) {
    if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
        adjacencyList[u].push_back(Edge(u, v, weight));
        if (!directed) {
            adjacencyList[v].push_back(Edge(v, u, weight));
        }
    }
}

void ALGraph::load_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Błąd otwarcia pliku!" << std::endl;
        return;
    }

    int edges;
    file >> vertices >> edges;
    allocate_list();

    int start, end, weight;
    for (int i = 0; i < edges; ++i) {
        file >> start >> end >> weight;
        add_edge(start, end, weight);
    }
    std::cout << "Pomyślnie wczytano listę sąsiedztwa" << std::endl;
}

void ALGraph::generate_random_graph(int v, int e) {
    vertices = v;
    allocate_list();

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

void ALGraph::print_graph() const {
    printf("\nGraf %s skierowany (Lista Sąsiedztwa):\n\n", directed ? "" : "nie ");
    for (int i = 0; i < vertices; ++i) {
        printf("%2d: ", i);
        for (const auto& edge : adjacencyList[i]) {
            printf(" -> (%d, %d)", edge.v, edge.weight);
        }
        std::cout << std::endl;
    }
}

Vector<Edge> ALGraph::get_edges() const {
    Vector<Edge> edges_list;
    for (int i = 0; i < vertices; ++i) {
        for (const auto& edge : adjacencyList[i]) {
            if (directed || i < edge.v) { // unikamy duplikatów dla grafów nieskierowanych
                edges_list.push_back(edge);
            }
        }
    }
    return edges_list;
}

Vector<int> ALGraph::get_neighbors(int v) const {
    Vector<int> neighbors;
    for (const auto& edge : adjacencyList[v]) {
        neighbors.push_back(edge.v);
    }
    return neighbors;
}

int ALGraph::get_weight(int u, int v) const {
    for (const auto& edge : adjacencyList[u]) {
        if (edge.v == v) {
            return edge.weight;
        }
    }
    return 0; // lub inna wartość wskazująca na brak krawędzi
}
