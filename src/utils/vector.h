#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

template<typename T>
class Vector {
public:
    Vector() : capacity(1), length(0) {
        data = new T[capacity];
    }
    ~Vector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (length == capacity) {
            grow();
        }
        data[length++] = value;
    }

    T& operator[](size_t index) {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t size() const {
        return length;
    }

    void resize(size_t newSize) {
        if (newSize > capacity) {
            T* newData = new T[newSize];
            copy_data(newData, data, length);
            delete[] data;
            data = newData;
            capacity = newSize;
        }
        length = newSize;
    }

private:
    size_t capacity;
    size_t length;
    T* data;

    void grow() {
        capacity *= 2;
        T* newData = new T[capacity];
        copy_data(newData, data, length);
        delete[] data;
        data = newData;
    }

    void copy_data(T* destination, T* source, size_t length) {
        for (size_t i = 0; i < length; ++i) {
            destination[i] = source[i];
        }
    }
};

#endif // VECTOR_H
