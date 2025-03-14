#ifndef PTRLIST_H
#define PTRLIST_H
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class PTRList {
private:
    struct Node { // Node structure
        T data;
        Node* next;
        Node(T value, Node* n = nullptr) : data(value), next(n) {}
    };
    Node* head; // Head of the list

    // Check if the node has a next node
    bool itHasNext (Node* position) {return position->next;};

public:
    PTRList() : head(nullptr) {} // Constructor
    ~PTRList() {
        while (!isEmptyList())
            deleteList(firstList());
    }

    // Check if the list is empty
    bool isEmptyList() const {
        return head == nullptr;
    }

    // Build a new node
    Node* buildNode(T value) {return new Node(value, nullptr);};

    // Set the next node
    void setNext (Node* from, Node* to) {(from && to) ? from->next = to : throw invalid_argument("setH: Invalid node");};

    // Set the head of the list
    void setHead (Node* newHead) {newHead ? head = newHead : throw invalid_argument("setH: Invalid node");};

    // Read the value of a node
    T readList(Node* position) const {
        if (!position) {
            throw out_of_range("read: Invalid position");
        }
        return position->data;
    }

    // Write a value to a node
    void writeList(T element, Node* position) {
        if (!position) {
            throw out_of_range("write: Invalid position");
        }
        position->data = element;
    }

    // Get the first node of the list
    Node* firstList() const {
        return head;
    }

    // Check if the node is the last node
    bool endList(Node* position) const {
        return position->next == nullptr;
    }

    // Get the next node
    Node* nextList(Node* position) const {
        if (!position) {
            throw out_of_range("next: Invalid position");
        }
        return position->next;
    }

    // Get the previous node
    Node* prevList(Node* position) const {
        if (position == head || !head) {
            return nullptr;
        }
        Node* temp = head;
        while (temp->next != position) {
            temp = temp->next;
        }
        return temp;
    }

    // Insert a node into the list
    void insertList(T element, Node* position) {
        if (position == nullptr) { // Insert at the head
            head = new Node(element, head);
        } else { // Insert after the position
            if (itHasNext(position)) {
                Node* temp = position->next;
                Node* newNode = new Node(element, nullptr);
                position->next = newNode;
                newNode->next = temp;
            } else {
                position->next = new Node(element, nullptr);
            }
        }
    }

    // Delete a node from the list
    void deleteList(Node* position) {
        if (position == head) { // Delete at the head
            Node* temp = head;
            head = head->next;
            delete temp;
        } else { // Delete after a node
            Node* prev = prevList(position);
            prev->next = position->next;
            delete position;
        }
    }

    // Print the list
    void printList() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

#endif
