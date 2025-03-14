#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H
#include <iostream>
#include <stdexcept>
using namespace std;

const int MAX_SIZE = 100;

template <typename T>
class Circular_Queue {
private:
    T data[MAX_SIZE]; // Array to store queue elements
    int head, tail, size; // Indices for head, tail, and size of the queue

public:
    Circular_Queue() : head(0), tail(0), size(0) {} // Constructor

    // Check if the queue is empty
    bool isEmptyQueue() const {
        return size == 0;
    }

    // Check if the queue is full
    bool isFull() const {
        return size == MAX_SIZE;
    }

    // Add an element to the tail of the queue
    void pushTail(T element) {
        if (isFull()) throw std::overflow_error("Queue is full");
        data[tail] = element;
        tail = (tail + 1) % MAX_SIZE;
        size++;
    }

    // Remove the element at the head of the queue
    void deleteHead() {
        if (isEmptyQueue()) throw std::out_of_range("Queue is empty");
        head = (head + 1) % MAX_SIZE;
        size--;
    }

    // Read the element at the head of the queue
    T readHead() const {
        if (isEmptyQueue()) throw std::out_of_range("Queue is empty");
        return data[head];
    }

    // Read the element at the tail of the queue
    T readTail() const {
        if (isEmptyQueue()) throw std::out_of_range("Queue is empty");
        return data[(tail - 1 + MAX_SIZE) % MAX_SIZE];
    }
};

#endif
