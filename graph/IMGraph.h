#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
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
};
