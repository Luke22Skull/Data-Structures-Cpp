#ifndef PTRSTACK_H
#define PTRSTACK_H
#include <iostream>
#include <stdexcept>

template <typename T>
class PTR_Stack {
public:
    PTR_Stack() : top(nullptr) {} // Constructor
    ~PTR_Stack() {
        while (!isEmptyStack())
            popStack();
    }

    // Check if the stack is empty
    bool isEmptyStack() {
        return top == nullptr;
    }

    // Read the top element of the stack
    T readStack() {
        if (!isEmptyStack())
            return this->top->getValue();
        else
            throw std::out_of_range("Stack is empty");
    }

    // Push an element onto the stack
    void pushStack(T element) {
        auto* newNode = new Node(element);
        newNode->next = top;
        top = newNode;
    }

    // Pop the top element from the stack
    void popStack() {
        if (!isEmptyStack()) {
            Node* temp = this->top;
            top = top->next;
            delete temp;
        } else {
            throw std::out_of_range("Stack is empty");
        }
    }

private:
    // Node structure for Stack
    struct Node {
        T data;
        Node* next;
        explicit Node(T value) : data(value), next(nullptr) {}
        Node(T value, Node* next) : data(value), next(next) {}
        T getValue() { return this->data; }
    };

    Node* top; // Top of the stack
};

#endif
