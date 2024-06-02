#pragma once
#include "ALGraph.h"
#include "IMGraph.h"

class MST {
public:
    static void prim(const ALGraph& graph);
    static void prim(const IMGraph& graph);
    static void kruskal(const ALGraph& graph);
    static void kruskal(const IMGraph& graph);

private:
    static void sort_edges(Edge* edges, int edge_count);
    static int find(int parent[], int i);
    static void unite(int parent[], int rank[], int x, int y);
};
