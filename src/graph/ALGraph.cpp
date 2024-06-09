#include "ALGraph.h"

ALGraph::ALGraph(bool dir) : directed(dir) {
    adjacency_list = nullptr;
}

ALGraph::~ALGraph() {
    if (adjacency_list) {
        for (int i = 0; i < vertices; ++i) {
            delete adjacency_list[i];
        }
        delete[] adjacency_list;
    }
}

void ALGraph::add_edge(int src, int dest, int weight) {
    if (src < vertices && dest < vertices) {
        adjacency_list[src]->add_edge(dest, weight);
        if (!directed) {
            adjacency_list[dest]->add_edge(src, weight);
        }
    }
}

void ALGraph::print_graph() const {
    printf("\nGraf %sskierowany (Lista sąsiedztwa):\n\n", directed ? "" : "nie");
    for (int i = 0; i < vertices; i++) {
        adjacency_list[i]->print_edges();
    }
}

void ALGraph::load_from_file(const std::string& filename) {
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
        }
    }
    printsep("Pomyślnie załadowano Listę sąsiedztwa");
}

void ALGraph::generate_random_graph(int v, int e) {
    vertices = v;
    
    adjacency_list = new Edges*[vertices];
    for (int i = 0; i < vertices; ++i) {
        adjacency_list[i] = new Edges(i);
    }

    int* src = new int[e];
    int* dest = new int[e];
    int* weights = new int[e];

    generate_random_connected_graph(vertices, e, src, dest, weights);

    for (int i = 0; i < e; ++i) {
        add_edge(src[i], dest[i], weights[i]);
    }

    delete[] src;
    delete[] dest;
    delete[] weights;
}

int ALGraph::get_vertices() const {
    return vertices;
}

Edge* ALGraph::get_edges(int u) const {
    return adjacency_list[u]->get_edges();
}

int ALGraph::get_edge_count(int u) const {
    return adjacency_list[u]->get_count();
}
