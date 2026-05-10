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

    // Вставка/видалення за індексом

    void insertAt(int index, const T& value) {
        if (index < 0 || index > listSize)
            throw std::out_of_range("insertAt: index " + std::to_string(index) + " is out of range");
        if (index == 0) { pushFront(value); return; }
        if (index == listSize) { pushBack(value); return; }

        auto current = head;
        for (int i = 0; i < index - 1; i++) current = current->next;

        auto newNode = std::make_shared<Node<T>>(value);
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next) current->next->prev = newNode;
        current->next = newNode;
        listSize++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= listSize)
            throw std::out_of_range("removeAt: index " + std::to_string(index) + " is out of range");
        if (index == 0) { popFront(); return; }
        if (index == listSize - 1) { popBack(); return; }

        auto current = head;
        for (int i = 0; i < index; i++) current = current->next;

        auto prevNode = current->prev.lock();
        prevNode->next = current->next;
        if (current->next) current->next->prev = current->prev;
        listSize--;
    }

    // Доступ за індексом

    T& at(int index) {
        if (index < 0 || index >= listSize)
            throw std::out_of_range("at: index " + std::to_string(index) + " is out of range");
        auto current = head;
        for (int i = 0; i < index; i++) current = current->next;
        return current->data;
    }

    // Пошук

    int find(const T& value) const {
        auto current = head;
        int index = 0;
        while (current) {
            if (current->data == value) return index;
            current = current->next;
            index++;
        }
        return -1;
    }

    // Інфо

    int size() const { return listSize; }
    bool isEmpty() const { return listSize == 0; }
};