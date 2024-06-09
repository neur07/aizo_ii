#pragma once
#include "ALGraph.h"
#include "IMGraph.h"
#include "Edges.h"
#include "Vector.h"

class MST {
public:
    static void prim(const ALGraph& graph);
    static void prim(const IMGraph& graph);
    static void kruskal(const ALGraph& graph);
    static void kruskal(const IMGraph& graph);

private:
    static void sort_edges(Vector<Edge>& edges);
    static int find(Vector<int>& parent, int i);
    static void unite(Vector<int>& parent, Vector<int>& rank, int x, int y);
};
