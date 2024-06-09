#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "vector.h"
#include <functional>
#include <stdexcept>

template<typename T, typename Compare = std::less<T> >
class PriorityQueue {
private:
    Vector<T> data;
    Compare comp;
    void heapify_up(int index);
    void heapify_down(int index);

public:
    PriorityQueue() : comp(Compare()) {}
    void push(const T& value);
    void pop();
    const T& top() const;
    bool empty() const;
};

template<typename T, typename Compare>
void PriorityQueue<T, Compare>::push(const T& value) {
    data.push_back(value);
    heapify_up(data.size() - 1);
}

template<typename T, typename Compare>
void PriorityQueue<T, Compare>::pop() {
    if (data.empty()) {
        throw std::out_of_range("Priority queue is empty");
    }
    std::swap(data[0], data[data.size() - 1]);
    data.resize(data.size() - 1);
    heapify_down(0);
}

template<typename T, typename Compare>
const T& PriorityQueue<T, Compare>::top() const {
    if (data.empty()) {
        throw std::out_of_range("Priority queue is empty");
    }
    return data[0];
}

template<typename T, typename Compare>
bool PriorityQueue<T, Compare>::empty() const {
    return data.size() == 0;
}

template<typename T, typename Compare>
void PriorityQueue<T, Compare>::heapify_up(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (comp(data[parent], data[index])) {
            std::swap(data[parent], data[index]);
            index = parent;
        } else {
            break;
        }
    }
}

template<typename T, typename Compare>
void PriorityQueue<T, Compare>::heapify_down(int index) {
    int size = data.size();
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && comp(data[largest], data[left])) {
            largest = left;
        }
        if (right < size && comp(data[largest], data[right])) {
            largest = right;
        }
        if (largest != index) {
            std::swap(data[index], data[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

#endif // PRIORITYQUEUE_H
