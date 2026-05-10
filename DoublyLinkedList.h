#pragma once
#include "Node.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class DoublyLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    int listSize;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

    // Додавання

    void pushFront(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        listSize++;
    }

    void pushBack(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        listSize++;
    }

    // Видалення

    void popFront() {
        if (!head)
            throw std::underflow_error("popFront: list is empty");
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head->next;
            head->prev.reset();
        }
        listSize--;
    }

    void popBack() {
        if (!tail)
            throw std::underflow_error("popBack: list is empty");
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            tail = tail->prev.lock();  // weak_ptr → shared_ptr
            tail->next = nullptr;
        }
        listSize--;
    }

    // Виведення

    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& list) {
        auto current = list.head;
        os << "[ ";
        while (current) {
            os << current->data;
            if (current->next) os << " <-> ";
            current = current->next;
        }
        os << " ]";
        return os;
    }
};