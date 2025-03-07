#ifndef PTRSTACK_H
#define PTRSTACK_H

#include <iostream>
#include <stdexcept>

template <typename T>
class PTR_Stack {
public:
    PTR_Stack() : top(nullptr) {}

    ~PTR_Stack() {
        while (!isEmptyStack())
            popStack();
    }

    bool isEmptyStack() {
        return top == nullptr;
    }

    T readStack() {
        if (!isEmptyStack())
            return this->top->getValue();
        else
            throw std::out_of_range("Stack is empty");
    }

    void pushStack(T element) {
        auto* newNode = new Nodo(element);
        newNode->next = top;
        top = newNode;
    }

    void popStack() {
        if (!isEmptyStack()) {
            Nodo* temp = this->top;
            top = top->next;
            delete temp;
        } else {
            throw std::out_of_range("Stack is empty");
        }
    }

private:
    // Nodo per Stack e Code
    struct Nodo {
        T data;
        Nodo* next;

        explicit Nodo(T value) : data(value), next(nullptr) {}
        Nodo(T value, Nodo* next) : data(value), next(next) {}

        T getValue() { return this->data; }
    };
    
    Nodo* top;
};
#endif
