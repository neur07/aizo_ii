#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct RawData {
    size_t* data;
    size_t vertexCount;
    size_t edgeCount;
};

extern void printsep(const char* s);
extern int choice_input(string prompt = "Wybor");
extern string str_choice_input(string prompt = "Wybor");
extern bool between(int x, int a, int b);
extern void generate_random_connected_graph(int vertices, int edges, int* src, int* dest, int* weights);
extern RawData generateGraphData(float density, size_t vertices);
