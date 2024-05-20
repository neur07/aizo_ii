#include <iostream>
#include <fstream>
#include <climits>
#include <string>
using namespace std;

struct Edge {
    int dest;
    int weight;
    Edge* next;

    Edge(int d, int w) : dest(d), weight(w), next(nullptr) {}
};

struct UndirectedALGraph {
private:
    Edge** adjacency_list;
    int vertices;

    void add_edge(int src, int dest, int weight) {
        // Dodaje krawędź do grafu
        Edge* new_edge = new Edge(dest, weight);
        new_edge->next = adjacency_list[src];
        adjacency_list[src] = new_edge;

        // Graf nieskierowany wymaga dodania krawędzi w obu kierunkach
        new_edge = new Edge(src, weight);
        new_edge->next = adjacency_list[dest];
        adjacency_list[dest] = new_edge;
    }

public:
    UndirectedALGraph() : adjacency_list(nullptr), vertices(0) {}

    ~UndirectedALGraph() {
        for (int i = 0; i < vertices; ++i) {
            Edge* current = adjacency_list[i];
            while (current) {
                Edge* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] adjacency_list;
    }

    void load_from_file(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Nie można otworzyć pliku!" << endl;
            return;
        }

        int edges;
        file >> vertices >> edges;

        adjacency_list = new Edge*[vertices];
        for (int i = 0; i < vertices; ++i) {
            adjacency_list[i] = nullptr;
        }

        int start, end, weight;
        for (int i = 0; i < edges; ++i) {
            file >> start >> end >> weight;
            if (start >= 0 && start < vertices && end >= 0 && end < vertices) {
                add_edge(start, end, weight);
            }
        }
    }

    void print_graph() const {
        cout << endl << "Graf nieskierowany (Lista sąsiedztwa):" << endl << endl;
        for (int i = 0; i < vertices; ++i) {
            Edge* current = adjacency_list[i];
            if(!current) break;
            printf("%2d: [", i);
            while (current) {
                cout << "[" << current->dest << ", " << current->weight << "]";
                current = current->next;
                if (current) cout << ", ";
            }
            cout << "]" << endl;
        }
    }
};
