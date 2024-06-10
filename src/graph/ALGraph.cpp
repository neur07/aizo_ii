#include "ALGraph.h"

using namespace std;

ALGraph::ALGraph(size_t edge_count, size_t vertex_count, size_t* data)
        : edge_count(edge_count), vertex_count(vertex_count) {
    edges = new Edge*[vertex_count];
    for (size_t i = 0; i < vertex_count; ++i) {
        edges[i] = nullptr;
    }

    size_t data_count = 3 * edge_count;
    for (size_t i = 0; i < data_count; i += 3) {
        size_t start = data[i];
        size_t end = data[i + 1];
        size_t value = data[i + 2];

        Edge* new_edge = new Edge(start, end, value, nullptr, nullptr);
        if (edges[start] == nullptr) {
            edges[start] = new_edge;
        } else {
            Edge* tmp = edges[start];
            while (tmp->next_edge != nullptr) {
                tmp = tmp->next_edge;
            }
            tmp->next_edge = new_edge;
            new_edge->previous_edge = tmp;
        }
    }
}

ALGraph::~ALGraph() {
    for (size_t i = 0; i < vertex_count; ++i) {
        Edge* edge = edges[i];
        while (edge != nullptr) {
            Edge* to_delete = edge;
            edge = edge->next_edge;
            delete to_delete;
        }
    }
    delete[] edges;
}

void ALGraph::print() const {
    for (size_t i = 0; i < vertex_count; ++i) {
        cout << setw(2) << i << " --> ";
        Edge* edge = edges[i];
        while (edge != nullptr) {
            cout << setw(2) << edge->end_vertex << '[' << setw(2) << edge->value << "] | ";
            edge = edge->next_edge;
        }
        cout << endl;
    }
}

size_t ALGraph::get_vertex_count() const {
    return vertex_count;
}

size_t ALGraph::get_edge_count() const {
    return edge_count;
}

Edge** ALGraph::get_edges() const {
    return edges;
}

const Edge* ALGraph::get_neighbors(size_t index) const {
    if (index < vertex_count) {
        return edges[index];
    }
    return nullptr;
}
