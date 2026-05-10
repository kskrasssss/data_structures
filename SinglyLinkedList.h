#pragma once
#include "Node.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class SinglyLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    int listSize;

public:
    SinglyLinkedList() : head(nullptr), listSize(0) {}

    // Додавання

    void pushFront(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);
        newNode->next = head;
        head = newNode;
        listSize++;
    }

    void pushBack(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (!head) {
            head = newNode;
        }
        else {
            auto current = head;
            while (current->next) current = current->next;
            current->next = newNode;
        }
        listSize++;
    }

    // Видалення

    void popFront() {
        if (!head)
            throw std::underflow_error("popFront: list is empty");
        head = head->next;
        listSize--;
    }

    void popBack() {
        if (!head)
            throw std::underflow_error("popBack: list is empty");
        if (!head->next) {
            head = nullptr;
            listSize--;
            return;
        }
        auto current = head;
        while (current->next->next) current = current->next;
        current->next = nullptr;
        listSize--;
    }

    // Виведення

    friend std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& list) {
        auto current = list.head;
        os << "[ ";
        while (current) {
            os << current->data;
            if (current->next) os << " -> ";
            current = current->next;
        }
        os << " ]";
        return os;
    }
};