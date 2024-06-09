#ifndef LIST_H
#define LIST_H

template<typename T>
class List {
public:
    List();
    ~List();

    void push_back(const T& value);
    void emplace_back(const T& value);
    bool empty() const;
    void clear();

    class Iterator {
    public:
        Iterator() : node(nullptr) {}
        Iterator& operator++();
        bool operator!=(const Iterator& other) const;
        T& operator*();
    private:
        friend class List;
        struct Node* node;
        Iterator(Node* node) : node(node) {}
    };

    Iterator begin();
    Iterator end();

private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* head;
    Node* tail;
};

#include "List.cpp"
#endif // LIST_H
