#ifndef Vector_H
#define Vector_H

template<typename T>
class Vector {
public:
    Vector();
    ~Vector();

    void push_back(const T& value);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t size() const;
    void resize(size_t newSize);

private:
    size_t capacity;
    size_t length;
    T* data;
    void grow();
    void copy_data(T* destination, T* source, size_t length);
};

#include "vector.cpp"
#endif // Vector_H
