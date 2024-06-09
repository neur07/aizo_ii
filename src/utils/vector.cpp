#include "Vector.h"
#include <stdexcept>

template<typename T>
Vector<T>::Vector() : capacity(1), length(0) {
    data = new T[capacity];
}

template<typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    if (length == capacity) {
        grow();
    }
    data[length++] = value;
}

template<typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template<typename T>
size_t Vector<T>::size() const {
    return length;
}

template<typename T>
void Vector<T>::resize(size_t newSize) {
    if (newSize > capacity) {
        T* newData = new T[newSize];
        copy_data(newData, data, length);
        delete[] data;
        data = newData;
        capacity = newSize;
    }
    length = newSize;
}

template<typename T>
void Vector<T>::grow() {
    capacity *= 2;
    T* newData = new T[capacity];
    copy_data(newData, data, length);
    delete[] data;
    data = newData;
}

template<typename T>
void Vector<T>::copy_data(T* destination, T* source, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        destination[i] = source[i];
    }
}
