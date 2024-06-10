#pragma once
#include <iostream>

using namespace std;

class PathEdge {
public:
    int start;   // Punkt początkowy krawędzi
    int end;     // Punkt końcowy krawędzi
    int value;   // Wartość (waga) krawędzi

    PathEdge() : start(0), end(0), value(0) {}

    PathEdge(int s, int e, int v) : start(s), end(e), value(v) {}

    friend ostream& operator<<(ostream& output, const PathEdge& edge);
};

ostream& operator<<(ostream& output, const PathEdge& edge) {
    output << "Start: " << edge.start << ", End: " << edge.end << ", Value: " << edge.value;
    return output;
}
