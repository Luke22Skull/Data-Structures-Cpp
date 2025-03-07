#ifndef PTRQUEUE_H
#define PTRQUEUE_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class PTR_Queue {
public:
    PTR_Queue() : head(nullptr), tail(nullptr) {}

    ~PTR_Queue() {
        if (!isEmptyCoda())
            while (!isEmptyCoda())
                deleteHead();
    }

    bool isEmptyCoda() {
        return head == nullptr && tail == nullptr;
    }

    T readHead() const {
        if (head != nullptr)
            return this->head->getValue();
        else
            throw std::out_of_range("Coda is empty");
    }

    void pushTail(T element) {
        auto* newNode = new Nodo(element);
        if (isEmptyCoda()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = tail->next;
        }
    }

    void deleteHead() {
        if (!isEmptyCoda()) {
            Nodo* temp = head;
            head = head->next;
            delete temp;
            if (head == nullptr)
                tail = nullptr;
        } else {
            throw std::out_of_range("Coda is empty");
        }
    }

private:
    struct Nodo {
        T data;
        Nodo* next;

        explicit Nodo(T value) : data(value), next(nullptr) {}
        Nodo(T value, Nodo* next) : data(value), next(next) {}

        T getValue() { return this->data; }
    };

    Nodo* head;
    Nodo* tail;
};

#endif
