#pragma once
#include "ALGraph.h"
#include "IMGraph.h"

class SP {
public:
    static void dijkstra(const ALGraph& graph, int start, int end);
    static void bellman_ford(const ALGraph& graph, int start, int end);
    static void dijkstra(const IMGraph& graph, int start, int end);
    static void bellman_ford(const IMGraph& graph, int start, int end);
};
