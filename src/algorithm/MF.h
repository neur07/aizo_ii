#pragma once
#include "ALGraph.h"
#include "IMGraph.h"

class MF {
public:
    static int ford_fulkerson(ALGraph& graph, int source, int sink);
    static int ford_fulkerson(IMGraph& graph, int source, int sink);
private:
    static bool bfs(const ALGraph& graph, int source, int sink, Vector<int>& parent);
    static bool bfs(const IMGraph& graph, int source, int sink, Vector<int>& parent);
};
