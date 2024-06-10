#pragma once
#include "ALGraph.h"
#include "IMGraph.h"

class MF {
public:
    static int ford_fulkerson(const ALGraph& graph, int start, int end);
    static int ford_fulkerson(const IMGraph& graph, int start, int end);
};