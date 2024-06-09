#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "utils.h"

class IMGraph {
    int** incidence_matrix;
    int edges;
    int vertices;
    bool directed;

    void allocate_matrix();

public:
    IMGraph(bool dir = false);
    ~IMGraph();
    void load_from_file(const std::string& filename);
    void print_graph() const;
    void generate_random_graph(int v, int e);

    int get_vertices() const;
    int get_edges() const;
    int get_other_vertex(int u, int edge) const;
    const int* get_incidence_row(int u) const;
    bool is_directed() const { return directed; }
};
