#include "MF.h"

/*

int MF::ford_fulkerson(ALGraph& graph, int source, int sink) {
    int u, v;
    Vector<int> parent(graph.size());
    int max_flow = 0;

    while (bfs(graph, source, sink, parent)) {
        int path_flow = min_flow(graph, parent, sink);
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            graph.add_flow(u, v, -path_flow);
            graph.add_flow(v, u, path_flow);
        }
        max_flow += path_flow;
    }

    return max_flow;
}

int MF::ford_fulkerson(IMGraph& graph, int source, int sink) {
    int u, v;
    Vector<int> parent(graph.size());
    int max_flow = 0;

    while (bfs(graph, source, sink, parent)) {
        int path_flow = min_flow(graph, parent, sink);
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            graph.add_flow(u, v, -path_flow);
            graph.add_flow(v, u, path_flow);
        }
        max_flow += path_flow;
    }

    return max_flow;
}

bool MF::bfs(ALGraph& graph, int source, int sink, Vector<int>& parent) {
    Vector<bool> visited(graph.size(), false);
    List<int> queue;
    queue.push_back(source);
    visited[source] = true;
    parent[source] = -1;

    while (!queue.is_empty()) {
        int u = queue.pop_front();
        for (int v : graph.neighbors(u)) {
            if (!visited[v] && graph.capacity(u, v) > 0) {
                if (v == sink) {
                    parent[v] = u;
                    return true;
                }
                queue.push_back(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

bool MF::bfs(IMGraph& graph, int source, int sink, Vector<int>& parent) {
    Vector<bool> visited(graph.size(), false);
    List<int> queue;
    queue.push_back(source);
    visited[source] = true;
    parent[source] = -1;

    while (!queue.is_empty()) {
        int u = queue.pop_front();
        for (int v = 0; v < graph.size(); v++) {
            if (!visited[v] && graph.capacity(u, v) > 0) {
                if (v == sink) {
                    parent[v] = u;
                    return true;
                }
                queue.push_back(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

int MF::min_flow(ALGraph& graph, Vector<int>& parent, int sink) {
    int flow = INT_MAX;
    for (int v = sink; v != -1; v = parent[v]) {
        int u = parent[v];
        flow = std::min(flow, graph.capacity(u, v));
    }
    return flow;
}

int MF::min_flow(IMGraph& graph, Vector<int>& parent, int sink) {
    int flow = INT_MAX;
    for (int v = sink; v != -1; v = parent[v]) {
        int u = parent[v];
        flow = std::min(flow, graph.capacity(u, v));
    }
    return flow;
}
*/