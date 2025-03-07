#ifndef ARRSTACK_H
#define ARRSTACK_H

#include <iostream>
#include <stdexcept>

const int MAX_SIZE = 100;

// PILA - Array
template <typename T>
class Array_Stack {
private:
    T data[MAX_SIZE];
    int top;

public:
    Array_Stack() : top(-1) {}

    bool isEmptyStack() {
        return top == -1;
    }

    T readStack() {
        if (!isEmptyStack())
            return data[top];
        else
            throw std::out_of_range("Stack is empty");
    }

    void pushStack(T element) {
        if (top < MAX_SIZE - 1) {
            data[++top] = element;
        } else {
            throw std::overflow_error("Stack overflow");
        }
    }

    void popStack() {
        if (!isEmptyStack()) {
            --top;
        } else {
            throw std::out_of_range("Stack is empty");
        }
    }
};

#endif
