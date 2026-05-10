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



        // Вставка/видалення за індексом

        void insertAt(int index, const T & value) {
            if (index < 0 || index > listSize)
                throw std::out_of_range("insertAt: index " + std::to_string(index) + " is out of range");
            if (index == 0) { pushFront(value); return; }

            auto current = head;
            for (int i = 0; i < index - 1; i++) current = current->next;

            auto newNode = std::make_shared<Node<T>>(value);
            newNode->next = current->next;
            current->next = newNode;
            listSize++;
        }

        void removeAt(int index) {
            if (index < 0 || index >= listSize)
                throw std::out_of_range("removeAt: index " + std::to_string(index) + " is out of range");
            if (index == 0) { popFront(); return; }

            auto current = head;
            for (int i = 0; i < index - 1; i++) current = current->next;
            current->next = current->next->next;
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

        int find(const T & value) const {
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
    }
};