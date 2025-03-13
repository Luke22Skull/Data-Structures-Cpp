#ifndef ARRSTACK_H
#define ARRSTACK_H

#include <iostream>
#include <stdexcept>

const int MAX_SIZE = 100; // Maximum size of the stack

// STACK - Array
template <typename T>
class ArrayStack {
private:
    T data[MAX_SIZE]; // Array to hold stack elements
    int top; // Index of the top element

public:
    // Constructor: initialize top to -1 indicating an empty stack
    ArrayStack() : top(-1) {}

    // Check if the stack is empty
    bool isEmptyStack() {
        return top == -1;
    }

    // Read the top element of the stack
    T readStack() {
        if (!isEmptyStack())
            return data[top];
        else
            throw std::out_of_range("Stack is empty");
    }

    // Push a new element onto the stack
    void pushStack(T element) {
        if (top < MAX_SIZE - 1) {
            data[++top] = element;
        } else {
            throw std::overflow_error("Stack overflow");
        }
    }

    // Pop the top element from the stack
    void popStack() {
        if (!isEmptyStack()) {
            --top;
        } else {
            throw std::out_of_range("Stack is empty");
        }
    }
};

#endif
