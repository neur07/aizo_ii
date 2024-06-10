#include "IMGraph.h"

using namespace std;

IMGraph::IMGraph(size_t num_edges, size_t num_vertices, size_t* data)
        : num_edges(num_edges), num_vertices(num_vertices) {
    edge_values = new size_t[num_edges];
    matrix_handler = new MatrixCell*[num_vertices];
    for (size_t i = 0; i < num_vertices; ++i) {
        matrix_handler[i] = new MatrixCell[num_edges];
        for (size_t j = 0; j < num_edges; ++j) {
            matrix_handler[i][j] = MatrixCell::None;
        }
    }

    size_t index = 0;
    for (size_t i = 0; i < num_edges; ++i) {
        size_t start = data[index++];
        size_t end = data[index++];
        size_t value = data[index++];
        matrix_handler[start][i] = MatrixCell::Start;
        matrix_handler[end][i] = MatrixCell::End;
        edge_values[i] = value;
    }
}

IMGraph::~IMGraph() {
    for (size_t i = 0; i < num_vertices; ++i) {
        delete[] matrix_handler[i];
    }
    delete[] matrix_handler;
    delete[] edge_values;
}

void IMGraph::print() const {
    cout << "    ";
    for (size_t i = 0; i < num_edges; ++i) {
        cout << setw(2) << i << "   ";
    }
    cout << endl;

    for (size_t i = 0; i < num_vertices; ++i) {
        cout << setw(2) << i << "  ";
        for (size_t j = 0; j < num_edges; ++j) {
            cout << setw(2) << static_cast<int>(matrix_handler[i][j]) << " | ";
        }
        cout << endl;
    }

    cout << " w  ";
    for (size_t i = 0; i < num_edges; ++i) {
        cout << setw(2) << edge_values[i] << " | ";
    }
    cout << endl;
}

size_t IMGraph::get_num_vertices() const {
    return num_vertices;
}

size_t IMGraph::get_num_edges() const {
    return num_edges;
}

MatrixCell** IMGraph::get_matrix() const {
    return matrix_handler;
}

size_t* IMGraph::get_values() const {
    return edge_values;
}

int IMGraph::get_weight(size_t u, size_t v) const {
    for (size_t i = 0; i < num_edges; ++i) {
        if (matrix_handler[u][i] == MatrixCell::Start && matrix_handler[v][i] == MatrixCell::End) {
            return edge_values[i];
        }
    }
    return -1; // Jeśli nie znaleziono krawędzi, zwróć -1
}
