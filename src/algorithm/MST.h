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
    static void selectionSort(Edge* edges, size_t num_edges);
};
