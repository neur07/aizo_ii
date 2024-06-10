#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Array {
private:
    T* head;
    size_t size;

public:
    Array() : head(nullptr), size(0) {}
    Array(const Array<T>& array);
    ~Array();

    void add_at_start(const T& data);
    void add_at_end(const T& data);
    bool add_at_position(const size_t& index, const T& data);
    bool search(const T& data) const;
    bool remove_from_start();
    bool remove_from_end();
    bool remove_from_position(const size_t& index);

    void print(ostream& output) const;

    T get_start() const;
    T get_end() const;
    T get_at_position(const size_t& index) const;

    size_t get_size() const;
};

// Implementacja funkcji członkowskich

template <typename T>
Array<T>::Array(const Array<T>& array) {
    this->head = new T[array.size];
    for (size_t i = 0; i < array.size; i++) {
        this->head[i] = array.head[i];
    }
    this->size = array.size;
}

template <typename T>
Array<T>::~Array() {
    if (this->head != nullptr) {
        delete[] this->head;
    }
}

template <typename T>
void Array<T>::add_at_start(const T& data) {
    T* new_head = new T[this->size + 1];
    new_head[0] = data;

    if (this->head != nullptr) {
        for (size_t i = 0; i < this->size; i++) {
            new_head[i + 1] = this->head[i];
        }
        delete[] this->head;
    }

    this->size++;
    this->head = new_head;
}

template <typename T>
void Array<T>::add_at_end(const T& data) {
    T* new_head = new T[this->size + 1];
    new_head[this->size] = data;

    if (this->head != nullptr) {
        for (size_t i = 0; i < this->size; i++) {
            new_head[i] = this->head[i];
        }
        delete[] this->head;
    }

    this->size++;
    this->head = new_head;
}

template <typename T>
bool Array<T>::add_at_position(const size_t& index, const T& data) {
    if (index > this->size) {
        return false;
    }

    T* new_head = new T[this->size + 1];
    new_head[index] = data;

    for (size_t i = 0; i < index; i++) {
        new_head[i] = this->head[i];
    }

    for (size_t i = index + 1; i <= size; i++) {
        new_head[i] = this->head[i - 1];
    }

    delete[] this->head;
    this->size++;
    this->head = new_head;
    return true;
}

template <typename T>
bool Array<T>::search(const T& data) const {
    if (this->size == 0) {
        return false;
    }

    for (size_t i = 0; i < this->size; i++) {
        if (this->head[i] == data) {
            return true;
        }
    }

    return false;
}

template <typename T>
bool Array<T>::remove_from_start() {
    if (this->head == nullptr) {
        return false;
    }

    T* new_head = nullptr;

    if (this->size > 1) {
        new_head = new T[size - 1];
        for (size_t i = 1; i < this->size; i++) {
            new_head[i - 1] = this->head[i];
        }
    }

    delete[] this->head;
    this->size--;
    this->head = new_head;
    return true;
}

template <typename T>
bool Array<T>::remove_from_end() {
    if (this->head == nullptr) {
        return false;
    }

    T* new_head = nullptr;
    this->size--;

    if (this->size >= 1) {
        new_head = new T[size];
        for (size_t i = 0; i < this->size; i++) {
            new_head[i] = this->head[i];
        }
    }

    delete[] this->head;
    this->head = new_head;
    return true;
}

template <typename T>
bool Array<T>::remove_from_position(const size_t& index) {
    if (index >= this->size) {
        return false;
    }

    T* new_head = nullptr;

    if (this->size > 1) {
        new_head = new T[size - 1];

        for (size_t i = 0; i < index; i++) {
            new_head[i] = this->head[i];
        }

        for (size_t i = index + 1; i < size; i++) {
            new_head[i - 1] = this->head[i];
        }
    }

    delete[] this->head;
    this->size--;
    this->head = new_head;
    return true;
}

template <typename T>
void Array<T>::print(ostream& output) const {
    if (this->size > 0 && this->head != nullptr) {
        for (size_t i = 0; i < this->size; i++) {
            output << i << "> " << this->head[i] << endl;
        }
        return;
    }
    output << "Data structure is empty" << endl;
}

template <typename T>
T Array<T>::get_start() const {
    if (this->size == 0) {
        throw runtime_error("Size is 0");
    }

    return this->head[0];
}

template <typename T>
T Array<T>::get_end() const {
    if (this->size == 0) {
        throw runtime_error("Size is 0");
    }

    return this->head[this->size - 1];
}

template <typename T>
T Array<T>::get_at_position(const size_t& index) const {
    if (index >= this->size) {
        throw runtime_error("Index out of range");
    }

    return this->head[index];
}

template <typename T>
size_t Array<T>::get_size() const {
    return this->size;
}

// Przeciążenie operatora << dla klasy KrawedzSciezki
class PathEdge;
ostream& operator<<(ostream& output, const PathEdge& edge);
