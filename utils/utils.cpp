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
                weights[edge_count] = rand() % 10;
                edge_count++;
            }
        }
    }
}
