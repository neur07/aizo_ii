#pragma once
#include "Edges.h"
#include <iostream>
#include <fstream>
#include <utils.h>

class ALGraph {
    Edges** adjacency_list;
    int vertices;
    bool directed;

public:
    ALGraph(bool dir = false);
    ~ALGraph();
    void add_edge(int src, int dest, int weight);
    void print_graph() const;
    void load_from_file(const std::string& filename);
    void generate_random_graph(int v, int e);

    int get_vertices() const;
    Edge* get_edges(int u) const;
    int get_edge_count(int u) const;
    bool is_directed() const { return directed; }
};
