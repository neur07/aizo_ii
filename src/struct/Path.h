#pragma once
#include "Array.h"
#include "PathEdge.h"
#include <iostream>

using namespace std;

class Path {
public:
    Path();
    Path(const Path& path);

    void add_edge(PathEdge edge);
    void print(ostream& output) const;

private:
    Array<PathEdge> edges;
    int total_cost;
};
