#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <iostream>
#include <stdexcept>
using namespace std;

const int MAX_SIZE = 100;

template <typename T>
class Circular_Queue {
private:
    T data[MAX_SIZE];
    int head, tail, size;

public:
    Circular_Queue() : head(0), tail(0), size(0) {}

    bool isEmptyCoda() const {
        return size == 0;
    }

    bool isFull() const {
        return size == MAX_SIZE;
    }

    void pushTail(T element) {
        if (isFull()) throw std::overflow_error("Coda piena");
        data[tail] = element;
        tail = (tail + 1) % MAX_SIZE;
        size++;
    }

    void deleteHead() {
        if (isEmptyCoda()) throw std::out_of_range("Coda vuota");
        head = (head + 1) % MAX_SIZE;
        size--;
    }

    T readHead() const {
        if (isEmptyCoda()) throw std::out_of_range("Coda vuota");
        return data[head];
    }

    T readTail() const {
        if (isEmptyCoda()) throw std::out_of_range("Coda vuota");
        return data[(tail - 1 + MAX_SIZE) % MAX_SIZE];
    }
};

#endif
