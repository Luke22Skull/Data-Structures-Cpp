#ifndef PTRQUEUE_H
#define PTRQUEUE_H
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class PTR_Queue {
public:
    PTR_Queue() : head(nullptr), tail(nullptr) {} // Constructor
    ~PTR_Queue() {
        if (!isEmptyQueue())
            while (!isEmptyQueue())
                deleteHead();
    }

    // Check if the queue is empty
    bool isEmptyQueue() {
        return head == nullptr && tail == nullptr;
    }

    // Read the value at the head of the queue
    T readHead() const {
        if (head != nullptr)
            return this->head->getValue();
        else
            throw std::out_of_range("Queue is empty");
    }

    // Push an element to the tail of the queue
    void pushTail(T element) {
        auto* newNode = new Node(element);
        if (isEmptyQueue()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = tail->next;
        }
    }

    // Delete the head element of the queue
    void deleteHead() {
        if (!isEmptyQueue()) {
            Node* temp = head;
            head = head->next;
            delete temp;
            if (head == nullptr)
                tail = nullptr;
        } else {
            throw std::out_of_range("Queue is empty");
        }
    }

private:
    // Node structure for Queue
    struct Node {
        T data;
        Node* next;
        explicit Node(T value) : data(value), next(nullptr) {}
        Node(T value, Node* next) : data(value), next(next) {}
        T getValue() { return this->data; }
    };

    Node* head; // Head of the queue
    Node* tail; // Tail of the queue
};
#endif
