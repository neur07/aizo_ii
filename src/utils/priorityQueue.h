#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Vector.h"
#include <functional>

template<typename T, typename Compare = std::less<T>>
class PriorityQueue {
public:
    PriorityQueue();
    void push(const T& value);
    void pop();
    const T& top() const;
    bool empty() const;

private:
    Vector<T> data;
    Compare comp;
    void heapify_up(int index);
    void heapify_down(int index);
};

#include "PriorityQueue.cpp"
#endif // PRIORITYQUEUE_H
