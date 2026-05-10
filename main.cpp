#include <iostream>
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

int main() {
    try {
        // ===== Singly Linked List =====
        std::cout << "=== Singly Linked List (int) ===" << std::endl;

        SinglyLinkedList<int> sll;
        sll.pushBack(2);
        sll.pushBack(3);
        sll.pushFront(1);
        sll.pushBack(4);
        std::cout << "After push:          " << sll << std::endl;

        sll.insertAt(2, 99);
        std::cout << "After insertAt(2,99):" << sll << std::endl;

        sll.popFront();
        std::cout << "After popFront:      " << sll << std::endl;

        sll.popBack();
        std::cout << "After popBack:       " << sll << std::endl;

        sll.removeAt(1);
        std::cout << "After removeAt(1):   " << sll << std::endl;

        std::cout << "at(0): " << sll.at(0) << std::endl;
        std::cout << "find(3): " << sll.find(3) << std::endl;
        std::cout << "find(99): " << sll.find(99) << std::endl;
        std::cout << "size: " << sll.size() << std::endl;
        std::cout << "isEmpty: " << sll.isEmpty() << std::endl;

        // Шаблон з рядками
        std::cout << "\n=== Singly Linked List (string) ===" << std::endl;
        SinglyLinkedList<std::string> strList;
        strList.pushBack("hello");
        strList.pushBack("world");
        strList.pushFront("start");
        std::cout << strList << std::endl;

        // ===== Doubly Linked List =====
        std::cout << "\n=== Doubly Linked List (int) ===" << std::endl;

        DoublyLinkedList<int> dll;
        dll.pushBack(2);
        dll.pushBack(3);
        dll.pushFront(1);
        dll.pushBack(4);
        std::cout << "After push:          " << dll << std::endl;

        dll.insertAt(2, 99);
        std::cout << "After insertAt(2,99):" << dll << std::endl;

        dll.popFront();
        std::cout << "After popFront:      " << dll << std::endl;

        dll.popBack();
        std::cout << "After popBack:       " << dll << std::endl;

        dll.removeAt(1);
        std::cout << "After removeAt(1):   " << dll << std::endl;

        std::cout << "at(1): " << dll.at(1) << std::endl;
        std::cout << "find(2): " << dll.find(2) << std::endl;
        std::cout << "size: " << dll.size() << std::endl;
        std::cout << "isEmpty: " << dll.isEmpty() << std::endl;

        // ===== Exceptions =====
        std::cout << "\n=== Exception tests ===" << std::endl;

        try {
            sll.at(100);
        }
        catch (const std::out_of_range& e) {
            std::cout << "Caught: " << e.what() << std::endl;
        }

        try {
            SinglyLinkedList<int> empty;
            empty.popFront();
        }
        catch (const std::underflow_error& e) {
            std::cout << "Caught: " << e.what() << std::endl;
        }

        try {
            dll.insertAt(-1, 5);
        }
        catch (const std::out_of_range& e) {
            std::cout << "Caught: " << e.what() << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Fatal: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}