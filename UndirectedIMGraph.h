#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

class UndirectedIMGraph {
    int** incidence_matrix;
    int edges;
    int vertices;

    // Alokacja macierzy; wierzchołki - wiersze, krawędzie - kolumny
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
        // Domyślnie pusty graf
        UndirectedIMGraph() : incidence_matrix(nullptr), edges(0), vertices(0) {}

        // Zwolnienie pamięci
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

            // Załadowanie liczby krawędzi oraz wierzchołkow z pierwszej linii pliku
            file >> edges >> vertices;

            // Alokacja potrzebnej pamięci
            allocate_matrix();

            int start, end, weight;

            // Wypełnianie i krawędzi
            for (int i = 0; i < edges; ++i) {
                // Wczytanie parametrow kolejnej krawędzi z pliku
                file >> start >> end >> weight;
                // Weryfikacja poprawności wierzchołkow
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
