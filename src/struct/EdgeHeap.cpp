#include "EdgeHeap.h"
#include <iostream>

using namespace std;

EdgeHeap::EdgeHeap(bool clear_on_destruction)
        : clear_on_destruction(clear_on_destruction), size(0), root(nullptr) {}

EdgeHeap::~EdgeHeap() {
    if (clear_on_destruction) {
        for (size_t i = 0; i < size; ++i) {
            delete root[i];
        }
    }
    delete[] root;
}

void EdgeHeap::add(Edge* edge) {
    Edge** buffer = new Edge*[size + 1];
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = root[i];
    }
    buffer[size] = edge;
    delete[] root;
    root = buffer;
    ++size;
    heapifyUp();
}

Edge* EdgeHeap::remove() {
    if (size == 0) {
        return nullptr;
    }

    Edge* edge_to_return = root[0];
    root[0] = root[--size];

    Edge** buffer = new Edge*[size];
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = root[i];
    }
    delete[] root;
    root = buffer;
    heapifyDown();
    return edge_to_return;
}

bool EdgeHeap::isEmpty() const {
    return size == 0;
}

void EdgeHeap::print() const {
    for (size_t i = 0; i < size; ++i) {
        cout << root[i]->start_vertex << ' ' << root[i]->end_vertex << ' ' << root[i]->value << endl;
    }
}

void EdgeHeap::heapifyUp() {
    int i = size - 1;
    int parent = (i - 1) / 2;
    while (i > 0 && root[parent]->value > root[i]->value) {
        Edge* temp = root[i];
        root[i] = root[parent];
        root[parent] = temp;
        i = parent;
        parent = (i - 1) / 2;
    }
}

void EdgeHeap::heapifyDown() {
    int i = 0;
    while (2 * i + 1 < size) {
        int j = 2 * i + 1;
        if (j + 1 < size && root[j]->value > root[j + 1]->value) {
            j++;
        }
        if (root[i]->value <= root[j]->value) {
            break;
        }
        Edge* temp = root[i];
        root[i] = root[j];
        root[j] = temp;
        i = j;
    }
}
