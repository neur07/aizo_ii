#pragma once
#include "ALGraph.h"
#include "IMGraph.h"
#include "Vector.h"

class MST {
public:
    static void prim(const ALGraph& graph);
    static void prim(const IMGraph& graph);
    static void kruskal(const ALGraph& graph);
    static void kruskal(const IMGraph& graph);

private:
    static int find_set(Vector<int>& parent, int i);
    static void union_set(Vector<int>& parent, Vector<int>& rank, int x, int y);
};
