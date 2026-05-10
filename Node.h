#pragma once
#include <memory>

template <typename T>
struct Node {
    T data;
    std::shared_ptr<Node<T>> next;
    std::weak_ptr<Node<T>> prev;

    explicit Node(const T& value) : data(value), next(nullptr) {}
};