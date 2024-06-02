#pragma once
#include <iostream>
#include <fstream>
#include "Edges.h"
#include "utils.h"

class ALGraph {
    Edges** adjacency_list;
    int vertices;
    bool directed;

public:
    ALGraph(int v = 0, bool dir = false);
    ~ALGraph();
    void add_edge(int src, int dest, int weight);
    void print_graph();
    void load_from_file(const std::string& filename);
};
