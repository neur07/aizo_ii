#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

enum class MatrixCell {
    None,
    Start,
    End
};

class IMGraph {
public:
    IMGraph(size_t num_edges, size_t num_vertices, size_t* values);
    ~IMGraph();

    void print() const;
    size_t get_num_vertices() const;
    size_t get_num_edges() const;
    MatrixCell** get_matrix() const;
    size_t* get_values() const;
    int get_weight(size_t u, size_t v) const;

private:
    size_t num_edges;
    size_t num_vertices;
    MatrixCell** matrix_handler;
    size_t* edge_values;
};
