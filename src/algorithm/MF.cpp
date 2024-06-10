#include "MF.h"
#include <iostream>
#include <limits>
#include <chrono>

using namespace std;

class SimpleQueue {
    int* data;         // tablica do przechowywania elementów kolejki
    int capacity;      // maksymalna pojemność kolejki
    int front;         // indeks przedniego elementu kolejki
    int rear;          // indeks tylnego elementu kolejki
    int count;         // liczba elementów w kolejce

public:
    SimpleQueue(int size) : capacity(size), front(0), rear(0), count(0) {
        data = new int[capacity]; // inicjalizacja tablicy
    }

    ~SimpleQueue() {
        delete[] data; // zwolnienie pamięci
    }

    void enqueue(int value) {
        if (count == capacity) return; // kolejka jest pełna
        data[rear] = value;            // dodanie elementu na koniec kolejki
        rear = (rear + 1) % capacity;  // przesunięcie tylnego wskaźnika
        ++count;                       // zwiększenie liczby elementów
    }

    void dequeue() {
        if (count == 0) return; // kolejka jest pusta
        front = (front + 1) % capacity; // przesunięcie przedniego wskaźnika
        --count;                        // zmniejszenie liczby elementów
    }

    int frontValue() const {
        return data[front]; // zwrócenie przedniego elementu
    }

    bool isEmpty() const {
        return count == 0; // sprawdzenie, czy kolejka jest pusta
    }
};

// Przeprowadza BFS w celu znalezienia ścieżki powiększającej w grafie rezydualnym
bool bfs(int** residualGraph, int vertexCount, int start, int end, int parent[]) {
    bool* visited = new bool[vertexCount];
    for (int i = 0; i < vertexCount; ++i) {
        visited[i] = false; // inicjalizacja tablicy odwiedzonych wierzchołków
    }

    SimpleQueue q(vertexCount);
    q.enqueue(start);
    visited[start] = true; // oznaczenie wierzchołka początkowego jako odwiedzonego
    parent[start] = -1;    // wierzchołek startowy nie ma rodzica

    while (!q.isEmpty()) {
        int u = q.frontValue();
        q.dequeue();

        for (int v = 0; v < vertexCount; ++v) {
            if (!visited[v] && residualGraph[u][v] > 0) { // jeśli wierzchołek nieodwiedzony i istnieje krawędź
                if (v == end) {
                    parent[v] = u; // zapisanie ścieżki
                    delete[] visited;
                    return true; // znaleziono ścieżkę do wierzchołka końcowego
                }
                q.enqueue(v);
                parent[v] = u;
                visited[v] = true; // oznaczenie wierzchołka jako odwiedzonego
            }
        }
    }

    delete[] visited;
    return false; // nie znaleziono ścieżki
}

// Implementacja algorytmu Forda-Fulkersona dla grafu reprezentowanego listą sąsiedztwa
int MF::ford_fulkerson(const ALGraph& graph, int start, int end) {
    auto start_time = chrono::high_resolution_clock::now(); // rozpoczęcie pomiaru czasu

    size_t vertexCount = graph.get_vertex_count();
    int** residualGraph = new int*[vertexCount];
    for (size_t i = 0; i < vertexCount; ++i) {
        residualGraph[i] = new int[vertexCount];
        for (size_t j = 0; j < vertexCount; ++j) {
            residualGraph[i][j] = 0; // inicjalizacja macierzy rezydualnej
        }
    }

    for (size_t u = 0; u < vertexCount; ++u) {
        const Edge* edge = graph.get_neighbors(u);
        while (edge != nullptr) {
            residualGraph[u][edge->end_vertex] = edge->value; // ustawienie przepustowości krawędzi
            edge = edge->next_edge;
        }
    }

    int* parent = new int[vertexCount]; // tablica do przechowywania ścieżki
    int maxFlow = 0; // maksymalny przepływ początkowo 0

    // Dopóki istnieje ścieżka powiększająca, wykonuj pętlę
    while (bfs(residualGraph, vertexCount, start, end, parent)) {
        int pathFlow = numeric_limits<int>::max();
        // Znajdź minimalną przepustowość na znalezionej ścieżce
        for (int v = end; v != start; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // Aktualizuj przepustowości rezydualne krawędzi
        for (int v = end; v != start; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow; // zwiększ maksymalny przepływ
    }

    auto stop_time = chrono::high_resolution_clock::now(); // zakończenie pomiaru czasu
    auto duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);
    cout << "Czas działania algorytmu Forda-Fulkersona (Lista Sąsiedztwa): " << duration.count() << " mikrosekund" << endl;

    for (size_t i = 0; i < vertexCount; ++i) {
        delete[] residualGraph[i];
    }
    delete[] residualGraph;
    delete[] parent;

    return maxFlow; // zwrócenie maksymalnego przepływu
}

// Implementacja algorytmu Forda-Fulkersona dla grafu reprezentowanego macierzą incydencji
int MF::ford_fulkerson(const IMGraph& graph, int start, int end) {
    auto start_time = chrono::high_resolution_clock::now(); // rozpoczęcie pomiaru czasu

    size_t vertexCount = graph.get_num_vertices();
    int** residualGraph = new int*[vertexCount];
    for (size_t i = 0; i < vertexCount; ++i) {
        residualGraph[i] = new int[vertexCount];
        for (size_t j = 0; j < vertexCount; ++j) {
            residualGraph[i][j] = 0; // inicjalizacja macierzy rezydualnej
        }
    }

    for (size_t u = 0; u < vertexCount; ++u) {
        for (size_t v = 0; v < vertexCount; ++v) {
            int weight = graph.get_weight(u, v);
            if (weight != -1) {
                residualGraph[u][v] = weight; // ustawienie przepustowości krawędzi
            }
        }
    }

    int* parent = new int[vertexCount]; // tablica do przechowywania ścieżki
    int maxFlow = 0; // maksymalny przepływ początkowo 0

    // Dopóki istnieje ścieżka powiększająca, wykonuj pętlę
    while (bfs(residualGraph, vertexCount, start, end, parent)) {
        int pathFlow = numeric_limits<int>::max();
        // Znajdź minimalną przepustowość na znalezionej ścieżce
        for (int v = end; v != start; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // Aktualizuj przepustowości rezydualne krawędzi
        for (int v = end; v != start; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow; // zwiększ maksymalny przepływ
    }

    auto stop_time = chrono::high_resolution_clock::now(); // zakończenie pomiaru czasu
    auto duration = chrono::duration_cast<chrono::microseconds>(stop_time - start_time);
    cout << "Czas działania algorytmu Forda-Fulkersona (Macierz Incydencji): " << duration.count() << " mikrosekund" << endl;

    for (size_t i = 0; i < vertexCount; ++i) {
        delete[] residualGraph[i];
    }
    delete[] residualGraph;
    delete[] parent;

    return maxFlow; // zwrócenie maksymalnego przepływu
}
