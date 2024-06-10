#include "utils.h"

void printsep(const char* s) {
    printf("\n%s\n", s);
}

int choice_input(string prompt) {
    int option;
    cout << endl << prompt << ": ";
    cin >> option;
    return option;
}

string str_choice_input(string prompt) {
    string option;
    cout << endl << prompt << ": ";
    cin >> option;
    return option;
}

bool between(int x, int a, int b) {
    return x >= a && x <= b;
}

void generate_random_connected_graph(int vertices, int edges, int* src, int* dest, int* weights) {
    if (edges < vertices - 1) {
        printsep("Liczba krawędzi zostałą nadpisana z powodu podania zbyt małej wartości.");
        edges = vertices - 1;
    }

    srand(time(0));

    // Generowanie drzewa rozpinającego
    for (int i = 0; i < vertices - 1; ++i) {
        src[i] = i;
        dest[i] = i + 1;
        weights[i] = rand() % 10 + 1;
    }

    int edge_count = vertices - 1;

    // Dodawanie losowych krawędzi
    while (edge_count < edges) {
        int u = rand() % vertices;
        int v = rand() % vertices;
        if (u != v) {
            bool exists = false;
            for (int i = 0; i < edge_count; ++i) {
                if ((src[i] == u && dest[i] == v) || (src[i] == v && dest[i] == u)) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                src[edge_count] = u;
                dest[edge_count] = v;
                weights[edge_count] = rand() % 9 + 1;
                edge_count++;
            }
        }
    }
}

RawData generateGraphData(float density, size_t vertices) {
    srand(static_cast<unsigned int>(time(nullptr)));
    int maxValue = 20;
    size_t minEdgeCount = vertices;
    size_t edgeCount = static_cast<size_t>((density * vertices * (vertices - 1)) / 2);
    edgeCount = edgeCount > minEdgeCount ? edgeCount : minEdgeCount;
    size_t dataSize = 3 * edgeCount;
    size_t* data = new size_t[dataSize];

    bool** connectionsExist = new bool*[vertices];
    for (size_t i = 0; i < vertices; ++i) {
        connectionsExist[i] = new bool[vertices]();
    }

    for (size_t i = 0; i < minEdgeCount - 1; ++i) {
        data[3 * i] = i;
        data[3 * i + 1] = i + 1;
        data[3 * i + 2] = rand() % maxValue + 1;
        connectionsExist[i][i + 1] = true;
        connectionsExist[i + 1][i] = true;
    }

    data[3 * (minEdgeCount - 1)] = minEdgeCount - 1;
    data[3 * (minEdgeCount - 1) + 1] = 0;
    data[3 * (minEdgeCount - 1) + 2] = rand() % maxValue + 1;
    connectionsExist[minEdgeCount - 1][0] = true;
    connectionsExist[0][minEdgeCount - 1] = true;

    for (size_t i = minEdgeCount; i < edgeCount; ++i) {
        size_t start = rand() % vertices;
        size_t end = rand() % vertices;

        while (start == end || connectionsExist[start][end]) {
            start = rand() % vertices;
            end = rand() % vertices;
        }

        data[3 * i] = start;
        data[3 * i + 1] = end;
        data[3 * i + 2] = rand() % maxValue + 1;

        connectionsExist[start][end] = true;
        connectionsExist[end][start] = true;
    }

    for (size_t i = 0; i < vertices; ++i) {
        delete[] connectionsExist[i];
    }
    delete[] connectionsExist;

    RawData result;
    result.data = data;
    result.vertexCount = vertices;
    result.edgeCount = edgeCount;

    return result;
}