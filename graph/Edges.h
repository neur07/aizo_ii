#pragma once
#include <climits>
#include <string>
#include <cstdio>

class Edges {
    struct Edge {
        int dest;
        int weight;
    };
    int vertex;
    Edge* edges;
    int count;
    int capacity;

public:
    Edges(int v);
    ~Edges();
    void add_edge(int dest, int weight);
    void print_edges();
};
