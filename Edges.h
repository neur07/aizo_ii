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
    Edges(int v) : vertex(v), count(0), capacity(1) {
        edges = new Edge[capacity];
    }

    ~Edges() {
        delete[] edges;
    }

    void add_edge(int dest, int weight) {
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

    void print_edges() {
        printf("%2d: ", vertex);
        for (int i = 0; i < count; ++i) {
            printf("%2d -> %2d (w: %d), ", vertex, edges[i].dest, edges[i].weight);
        }
        printf("\n");
    }
};