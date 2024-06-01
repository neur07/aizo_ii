#include <iostream>
#include <fstream>
#include "Edges.h"

class ALGraph {
    Edges** adjacency_list;
    int vertices;
    bool directed;

    public:

    ALGraph(int v = 0, bool dir = false) : vertices(v), directed(dir) {
        if (v > 0) {
            adjacency_list = new Edges*[vertices];
            for (int i = 0; i < vertices; ++i) {
                adjacency_list[i] = new Edges(i);
            }
        } else {
            adjacency_list = nullptr;
        }
    }

    ~ALGraph() {
        if (adjacency_list) {
            for (int i = 0; i < vertices; ++i) {
                delete adjacency_list[i];
            }
            delete[] adjacency_list;
        }
    }

    void add_edge(int src, int dest, int weight) {
        if (src < vertices && dest < vertices) {
            adjacency_list[src]->add_edge(dest, weight);
        }
    }

    void print_graph() {
        printf("\nGraf %sskierowany (Lista sąsiedztwa):\n\n", directed ? "" : "nie");
        for (int i = 0; i < vertices; i++) {
            adjacency_list[i]->print_edges();
        }
    }

    void load_from_file(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Nie można otworzyć pliku!" << std::endl;
            return;
        }

        int edges;
        file >> edges >> vertices; 

        adjacency_list = new Edges*[vertices];
        for (int i = 0; i < vertices; ++i) {
            adjacency_list[i] = new Edges(i);
        }

        int start, end, weight;
        for (int i = 0; i < edges; i++) {
            file >> start >> end >> weight;
            if (start >= 0 && start < vertices && end >= 0 && end < vertices) {
                add_edge(start, end, weight);
                // Dodanie przeciwnie skierowanej krawędzi
                if(!directed) add_edge(end, start, weight);
            }
        }
    }
};