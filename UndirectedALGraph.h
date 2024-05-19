#include <iostream>
#include <fstream>

struct Edge {
    int dest;
    int weight;
    Edge* next;

    Edge(int d, int w) : dest(d), weight(w), next(nullptr) {}
};

using namespace std;

class UndirectedALGraph {
private:
    Edge** adjacencyList;
    int vertices;

    void addEdge(int src, int dest, int weight) {
        Edge* newEdge = new Edge(dest, weight);
        newEdge->next = adjacencyList[src];
        adjacencyList[src] = newEdge;

        newEdge = new Edge(src, weight);
        newEdge->next = adjacencyList[dest];
        adjacencyList[dest] = newEdge;
    }

public:
    UndirectedALGraph() : adjacencyList(nullptr), vertices(0) {}

    ~UndirectedALGraph() {
        for (int i = 0; i < vertices; ++i) {
            Edge* current = adjacencyList[i];
            while (current) {
                Edge* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] adjacencyList;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Unable to open file!" << endl;
            return;
        }

        int edges;
        file >> edges >> vertices;

        adjacencyList = new Edge*[vertices];
        for (int i = 0; i < vertices; ++i) {
            adjacencyList[i] = nullptr;
        }

        int start, end, weight;
        for (int i = 0; i < edges; ++i) {
            file >> start >> end >> weight;
            if (start >= 0 && start < vertices && end >= 0 && end < vertices) {
                addEdge(start, end, weight);
            }
        }
    }

    void printGraph() const {
        cout << endl << "Graf nieskierowany (Lista sąsiedztwa):" << endl << endl;
        for (int i = 0; i < vertices; ++i) {
            Edge* current = adjacencyList[i];
            cout << "Vertex " << i << " :";
            while (current) {
                cout << " -> " << current->dest << " (Weight: " << current->weight << ")";
                current = current->next;
            }
            cout << endl;
        }
    }

    // void primMST() const {
    //     int* parent = new int[vertices];
    //     int* key = new int[vertices];
    //     bool* mstSet = new bool[vertices];

    //     for (int i = 0; i < vertices; ++i) {
    //         key[i] = INT_MAX;
    //         mstSet[i] = false;
    //     }

    //     key[0] = 0;
    //     parent[0] = -1;

    //     for (int count = 0; count < vertices - 1; ++count) {
    //         int u = minKey(key, mstSet);
    //         mstSet[u] = true;

    //         Edge* current = adjacencyList[u];
    //         while (current) {
    //             int v = current->dest;
    //             int weight = current->weight;
    //             if (!mstSet[v] && weight < key[v]) {
    //                 parent[v] = u;
    //                 key[v] = weight;
    //             }
    //             current = current->next;
    //         }
    //     }

    //     printMST(parent);

    //     delete[] parent;
    //     delete[] key;
    //     delete[] mstSet;
    // }

    // int minKey(int* key, bool* mstSet) const {
    //     int min = INT_MAX;
    //     int minIndex = -1;

    //     for (int v = 0; v < vertices; ++v) {
    //         if (!mstSet[v] && key[v] < min) {
    //             min = key[v];
    //             minIndex = v;
    //         }
    //     }

    //     return minIndex;
    // }

    // void printMST(int* parent) const {
    //     cout << "Edge \tWeight\n";
    //     for (int i = 1; i < vertices; ++i) {
    //         cout << parent[i] << " - " << i << "\t" << getWeight(parent[i], i) << "\n";
    //     }
    // }

    // int getWeight(int src, int dest) const {
    //     Edge* current = adjacencyList[src];
    //     while (current) {
    //         if (current->dest == dest) {
    //             return current->weight;
    //         }
    //         current = current->next;
    //     }
    //     return -1; // Edge not found
    // }

    // void kruskalMST() const {
    //     struct Subset {
    //         int parent;
    //         int rank;
    //     };

    //     Subset* subsets = new Subset[vertices];
    //     for (int i = 0; i < vertices; ++i) {
    //         subsets[i].parent = i;
    //         subsets[i].rank = 0;
    //     }

    //     int edgesIncluded = 0;
    //     int edgeIndex = 0;

    //     while (edgesIncluded < vertices - 1) {
    //         int u, v, uRep, vRep;
    //         int minWeight = INT_MAX;

    //         for (int i = 0; i < vertices; ++i) {
    //             Edge* current = adjacencyList[i];
    //             while (current) {
    //                 if (current->dest > i && current->weight < minWeight) {
    //                     minWeight = current->weight;
    //                     u = i;
    //                     v = current->dest;
    //                 }
    //                 current = current->next;
    //             }
    //         }

    //         uRep = find(subsets, u);
    //         vRep = find(subsets, v);

    //         if (uRep != vRep) {
    //             cout << u << " - " << v << "\t" << minWeight << endl;
    //             edgesIncluded++;
    //             Union(subsets, uRep, vRep);
    //         }
    //     }

    //     delete[] subsets;
    // }

    // int find(Subset* subsets, int i) const {
    //     if (subsets[i].parent != i) {
    //         subsets[i].parent = find(subsets, subsets[i].parent);
    //     }
    //     return subsets[i].parent;
    // }

    // void Union(Subset* subsets, int x, int y) const {
    //     int xRoot = find(subsets, x);
    //     int yRoot = find(subsets, y);

    //     if (subsets[xRoot].rank < subsets[yRoot].rank) {
    //         subsets[xRoot].parent = yRoot;
    //     } else if (subsets[xRoot].rank > subsets[yRoot].rank) {
    //         subsets[yRoot].parent = xRoot;
    //     } else {
    //         subsets[yRoot].parent = xRoot;
    //         subsets[xRoot].rank++;
    //     }
    // }
};
