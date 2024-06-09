#include "List.h"
#include <stdexcept>

template<typename T>
List<T>::List() : head(nullptr), tail(nullptr) {}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
void List<T>::push_back(const T& value) {
    Node* newNode = new Node(value);
    if (tail) {
        tail->next = newNode;
        tail = newNode;
    } else {
        head = tail = newNode;
    }
}

template<typename T>
void List<T>::emplace_back(const T& value) {
    push_back(value);
}

template<typename T>
bool List<T>::empty() const {
    return head == nullptr;
}

template<typename T>
void List<T>::clear() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}

template<typename T>
typename List<T>::Iterator List<T>::begin() {
    return Iterator(head);
}

template<typename T>
typename List<T>::Iterator List<T>::end() {
    return Iterator(nullptr);
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    if (node) {
        node = node->next;
    }
    return *this;
}

template<typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const {
    return node != other.node;
}

template<typename T>
T& List<T>::Iterator::operator*() {
    if (!node) {
        throw std::out_of_range("Dereferencing end iterator");
    }
    return node->data;
}
