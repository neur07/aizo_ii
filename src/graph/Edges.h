#pragma once
#include <cstdio>

struct Edge {
    int dest;
    int weight;
};

class Edges {
    int vertex;
    Edge* edges;
    int count;
    int capacity;

public:
    Edges(int v);
    ~Edges();

    void add_edge(int dest, int weight);
    void print_edges() const;
    Edge* get_edges() const;
    int get_count() const;
};
