#pragma once
#include "ALGraph.h"
#include "IMGraph.h"

class SP {
public:
    static void dijkstra(const ALGraph& graph, int src, int dest);
    static void dijkstra(const IMGraph& graph, int src, int dest);
    static void bellman_ford(const ALGraph& graph, int src, int dest);
    static void bellman_ford(const IMGraph& graph, int src, int dest);
};
