#pragma once
#include <stdexcept>

template<typename T> 
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    class Iterator {
    private:
        friend class List;
        Node* node;
        Iterator(Node* node) : node(node) {}

    public:
        Iterator() : node(nullptr) {}
        Iterator& operator++() {
            if (node) {
                node = node->next;
            }
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            return node != other.node;
        }
        T& operator*() {
            if (!node) {
                throw std::out_of_range("Poza zakresem");
            }
            return node->data;
        }
    };

    List() : head(nullptr), tail(nullptr) {}
    ~List() {
        clear();
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (tail) {
            tail->next = newNode;
            tail = newNode;
        } else {
            head = tail = newNode;
        }
    }

    void emplace_back(const T& value) {
        push_back(value);
    }

    bool empty() const {
        return head == nullptr;
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
    }

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
};
