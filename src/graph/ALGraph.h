#pragma once

#include <iostream>
#include <iomanip>

using namespace std;

struct Edge {
    size_t start_vertex;
    size_t end_vertex;
    size_t value;
    Edge* next_edge;
    Edge* previous_edge;

    Edge(size_t start, size_t end, size_t val, Edge* next = nullptr, Edge* prev = nullptr)
        : start_vertex(start), end_vertex(end), value(val), next_edge(next), previous_edge(prev) {}
};

class ALGraph {
public:
    ALGraph(size_t edge_count, size_t vertex_count, size_t* data);
    ~ALGraph();

    void print() const;
    size_t get_vertex_count() const;
    size_t get_edge_count() const;
    Edge** get_edges() const;
    const Edge* get_neighbors(size_t index) const;

private:
    size_t edge_count;
    size_t vertex_count;
    Edge** edges;
};

