#pragma once
#include "ALGraph.h"

class EdgeHeap {
public:
    EdgeHeap(bool clear_on_destruction = true);
    ~EdgeHeap();

    void add(Edge* edge);
    Edge* remove();
    bool isEmpty() const;
    void print() const;

private:
    void heapifyUp();
    void heapifyDown();

    bool clear_on_destruction;
    size_t size;
    Edge** root;
};
