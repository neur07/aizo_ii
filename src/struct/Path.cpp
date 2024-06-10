#include "Path.h"

using namespace std;

// Dodaje krawędź do ścieżki
void Path::add_edge(PathEdge edge) {
    this->total_cost += edge.value;
    this->edges.add_at_start(edge);
}

// Drukuje informacje o ścieżce
void Path::print(ostream& output) const {
    this->edges.print(output);
    output << "Total cost: " << this->total_cost << endl;
}
