#pragma once
#include "Vector.h"
#include <stdexcept>

template<typename T>
class PriorityQueue {
private:
    Vector<T> data;
    
    void heapify_up(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (compare(data[parent], data[index])) {
                my_swap(data[parent], data[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapify_down(int index) {
        int size = data.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && compare(data[largest], data[left])) {
                largest = left;
            }
            if (right < size && compare(data[largest], data[right])) {
                largest = right;
            }
            if (largest != index) {
                my_swap(data[index], data[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

    bool compare(const T& a, const T& b) const {
        return a < b;
    }

    void my_swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

public:
    PriorityQueue() = default;

    void push(const T& value) {
        data.push_back(value);
        heapify_up(data.size() - 1);
    }

    T pop() {
        if (data.empty()) {
            throw std::out_of_range("Kolejka jest pusta");
        }
        T removed_item = data[0];
        my_swap(data[0], data[data.size() - 1]);
        data.resize(data.size() - 1);
        if (!data.empty()) {
            heapify_down(0);
        }
        return removed_item;
    }

    const T& top() const {
        if (data.empty()) {
            throw std::out_of_range("Kolejka jest pusta");
        }
        return data[0];
    }

    bool empty() const {
        return data.size() == 0;
    }
};
