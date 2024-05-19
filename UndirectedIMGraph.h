#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;
class UndirectedIMGraph {
private:
    int** incidenceMatrix;
    int edges;
    int vertices;

    void allocateMatrix() {
        incidenceMatrix = new int*[vertices];
        for (int i = 0; i < vertices; ++i) {
            incidenceMatrix[i] = new int[edges];
            for (int j = 0; j < edges; ++j) {
                incidenceMatrix[i][j] = 0; // Initialize with zeros
            }
        }
    }

public:
    UndirectedIMGraph() : incidenceMatrix(nullptr), edges(0), vertices(0) {}

    ~UndirectedIMGraph() {
        if (incidenceMatrix) {
            for (int i = 0; i < vertices; ++i) {
                delete[] incidenceMatrix[i];
            }
            delete[] incidenceMatrix;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Unable to open file!" << endl;
            return;
        }

        file >> edges >> vertices;
        allocateMatrix();

        int start, end, weight;
        for (int i = 0; i < edges; ++i) {
            file >> start >> end >> weight;
            if (start >= 0 && start < vertices && end >= 0 && end < vertices) {
                incidenceMatrix[start][i] = weight;
                incidenceMatrix[end][i] = weight; // Since it's undirected, set both vertices
            }
        }
    }

    void printGraph() const {
        cout << endl << "Graf nieskierowany (Macierz incydencji):" << endl << endl;
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < edges; ++j) {
                cout << incidenceMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void primMST() const {
        int* parent = new int[vertices];
        int* key = new int[vertices];
        bool* mstSet = new bool[vertices];

        for (int i = 0; i < vertices; ++i) {
            key[i] = INT_MAX;
            mstSet[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < vertices - 1; ++count) {
            int u = minKey(key, mstSet);
            mstSet[u] = true;
            for (int v = 0; v < vertices; ++v) {
                if (incidenceMatrix[v][u] && !mstSet[v] && incidenceMatrix[v][u] < key[v]) {
                    parent[v] = u;
                    key[v] = incidenceMatrix[v][u];
                }
            }
        }

        printMST(parent);
        
        delete[] parent;
        delete[] key;
        delete[] mstSet;
    }

    int minKey(int* key, bool* mstSet) const {
        int min = INT_MAX;
        int minIndex;

        for (int v = 0; v < vertices; ++v) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }

        return minIndex;
    }

    void printMST(int* parent) const {
        cout << "Edge \tWeight\n";
        for (int i = 1; i < vertices; ++i) {
            cout << parent[i] << " - " << i << "\t" << incidenceMatrix[i][parent[i]] << "\n";
        }
    }

    void kruskalMST() const {
        int* parent = new int[vertices];
        int* rank = new int[vertices];
        for (int i = 0; i < vertices; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }

        int edgesIncluded = 0;
        int edgeIndex = 0;

        while (edgesIncluded < vertices - 1) {
            int u, v, uRep, vRep;
            int minWeight = INT_MAX;

            for (int i = 0; i < edges; ++i) {
                if (incidenceMatrix[0][i] != 0 && incidenceMatrix[1][i] != 0 && incidenceMatrix[0][i] < minWeight) {
                    minWeight = incidenceMatrix[0][i];
                    edgeIndex = i;
                }
            }

            u = incidenceMatrix[0][edgeIndex];
            v = incidenceMatrix[1][edgeIndex];
            uRep = find(parent, u);
            vRep = find(parent, v);

            if (uRep != vRep) {
                cout << u << " - " << v << "\t" << incidenceMatrix[2][edgeIndex] << endl;
                edgesIncluded++;
                Union(parent, rank, uRep, vRep);
            }
            incidenceMatrix[0][edgeIndex] = 0;
            incidenceMatrix[1][edgeIndex] = 0;
        }

        delete[] parent;
        delete[] rank;
    }

    int find(int* parent, int i) const {
        if (parent[i] != i) {
            parent[i] = find(parent, parent[i]);
        }
        return parent[i];
    }

    void Union(int* parent, int* rank, int x, int y) const {
        int xRoot = find(parent, x);
        int yRoot = find(parent, y);

        if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        } else if (rank[xRoot] > rank[yRoot]) {
            parent[yRoot] = xRoot;
        } else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }
};
