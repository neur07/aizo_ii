#pragma once
struct Edge {
    int u;
    int v;
    int weight;

    Edge() : u(0), v(0), weight(0) {}
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};