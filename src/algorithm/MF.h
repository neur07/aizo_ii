#pragma once
#include "ALGraph.h"
#include "IMGraph.h"

class MF {
public:
    static int ford_fulkerson(ALGraph& graph, int source, int sink);
    static int ford_fulkerson(IMGraph& graph, int source, int sink);

private:
    static bool bfs(ALGraph& graph, int source, int sink, Vector<int>& parent);
    static bool bfs(IMGraph& graph, int source, int sink, Vector<int>& parent);
    static int min_flow(ALGraph& graph, Vector<int>& parent, int sink);
    static int min_flow(IMGraph& graph, Vector<int>& parent, int sink);
};
