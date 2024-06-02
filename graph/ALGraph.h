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
    ALGraph(int v = 0, bool dir = false);
    ~ALGraph();
    void add_edge(int src, int dest, int weight);
    void print_graph() const;
    void load_from_file(const std::string& filename);

    int get_vertices() const;
    Edge* get_edges(int u) const;
    int get_edge_count(int u) const;
};
