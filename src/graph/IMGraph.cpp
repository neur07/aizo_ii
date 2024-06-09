#include "IMGraph.h"

IMGraph::IMGraph(bool dir) : incidence_matrix(nullptr), edges(0), vertices(0), directed(dir) {}

IMGraph::~IMGraph() {
    if (incidence_matrix) {
        for (int i = 0; i < vertices; ++i) {
            delete[] incidence_matrix[i];
        }
        delete[] incidence_matrix;
    }
}

void IMGraph::allocate_matrix() {
    incidence_matrix = new int*[vertices];
    for (int i = 0; i < vertices; ++i) {
        incidence_matrix[i] = new int[edges]();
    }
}

void IMGraph::load_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file!" << std::endl;
        return;
    }

    file >> edges >> vertices;
    allocate_matrix();

    int start, end, weight;
    for (int i = 0; i < edges; ++i) {
        file >> start >> end >> weight;
        if (start >= 0 && start < vertices && end >= 0 && end < vertices) {
            incidence_matrix[start][i] = (directed ? -1 : 1) * weight;
            incidence_matrix[end][i] = weight;
        }
    }
    printsep("Successfully loaded Incidence Matrix");
}

void IMGraph::generate_random_graph(int v, int e) {
    vertices = v;
    edges = e;

    allocate_matrix();

    int* src = new int[e];
    int* dest = new int[e];
    int* weights = new int[e];

    generate_random_connected_graph(vertices, e, src, dest, weights);

    for (int i = 0; i < e; ++i) {
        incidence_matrix[src[i]][i] = (directed ? -1 : 1) * weights[i];
        incidence_matrix[dest[i]][i] = weights[i];
    }

    delete[] src;
    delete[] dest;
    delete[] weights;
}

void IMGraph::print_graph() const {
    printf("\nGraph %sdirected (Incidence Matrix):\n\n", directed ? "" : "not ");
    printf("    ");
    for (int i = 1; i <= edges; ++i) printf("#%-3d ", i);
    std::cout << std::endl;
    for (int i = 0; i < vertices; ++i) {
        printf("%2d: ", i);
        for (int j = 0; j < edges; ++j) {
            printf("%4d ", incidence_matrix[i][j]);
        }
        std::cout << std::endl;
    }
}

int IMGraph::get_other_vertex(int u, int edge) const {
    for (int v = 0; v < vertices; ++v) {
        if (v != u && incidence_matrix[v][edge] != 0) {
            return v;
        }
    }
    return -1;
}

int IMGraph::get_vertices() const {
    return vertices;
}

int IMGraph::get_edges() const {
    return edges;
}

const int* IMGraph::get_incidence_row(int u) const {
    return incidence_matrix[u];
}
