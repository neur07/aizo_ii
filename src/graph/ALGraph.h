#pragma once
#include "Vector.h"
#include "Edge.h"
#include <string>

class ALGraph {
public:
    int vertices;
    bool directed;
    Vector<Vector<Edge> > adjacencyList;

    ALGraph(bool dir = false);
    int size();
    bool is_directed() const { return directed; }
    void print_graph() const;
    void load_from_file(const std::string& filename);
    void generate_random_graph(int v, int e);
    void add_edge(int u, int v, int weight);
    Vector<Edge> get_edges() const;
    Vector<int> get_neighbors(int v) const;
    int get_weight(int u, int v) const;

private:
    void allocate_list();
};
