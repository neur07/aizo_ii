#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

class UndirectedIMGraph {
private:
    int** incidence_matrix;
    int edges;
    int vertices;

    void allocate_matrix() {
        incidence_matrix = new int*[vertices];
        for (int i = 0; i < vertices; ++i) {
            incidence_matrix[i] = new int[edges];
            for (int j = 0; j < edges; ++j) {
                incidence_matrix[i][j] = 0;
            }
        }
    }

public:
    UndirectedIMGraph() : incidence_matrix(nullptr), edges(0), vertices(0) {}

    ~UndirectedIMGraph() {
        if (incidence_matrix) {
            for (int i = 0; i < vertices; ++i) {
                delete[] incidence_matrix[i];
            }
            delete[] incidence_matrix;
        }
    }

    void load_from_file(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Nie można otworzyć pliku!" << endl;
            return;
        }

        file >> edges >> vertices;
        allocate_matrix();

        int start, end, weight;
        for (int i = 0; i < edges; ++i) {
            file >> start >> end >> weight;
            if (start >= 0 && start < vertices && end >= 0 && end < vertices) {
                incidence_matrix[start][i] = weight;
                incidence_matrix[end][i] = weight;
            }
        }
    }

    void print_graph() const {
        cout << endl << "Graf nieskierowany (Macierz incydencji):" << endl << endl;
        printf("    ");
        for (int i = 1; i <= edges; ++i) printf("%3d ", i);
        cout << endl;
        for (int i = 0; i < vertices; ++i) {
            printf("%2d: ", i);
            for (int j = 0; j < edges; ++j) {
                printf("%3d ", incidence_matrix[i][j]);
            }
            cout << endl;
        }
    }
};
