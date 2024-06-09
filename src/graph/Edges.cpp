#include "Edges.h"

Edges::Edges(int v) : vertex(v), count(0), capacity(1) {
    edges = new Edge[capacity];
}

Edges::~Edges() {
    delete[] edges;
}

void Edges::add_edge(int dest, int weight) {
    if (count == capacity) {
        capacity *= 2;
        Edge* new_edges = new Edge[capacity];
        for (int i = 0; i < count; ++i) {
            new_edges[i] = edges[i];
        }
        delete[] edges;
        edges = new_edges;
    }
    edges[count].dest = dest;
    edges[count].weight = weight;
    count++;
}

void Edges::print_edges() const {
    printf("%2d: ", vertex);
    for (int i = 0; i < count; ++i) {
        printf("%2d -> %2d (w: %d), ", vertex, edges[i].dest, edges[i].weight);
    }
    printf("\n");
}

Edge* Edges::get_edges() const {
    return edges;
}

int Edges::get_count() const {
    return count;
}
