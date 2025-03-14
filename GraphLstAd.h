#ifndef GRAPHLSTAD_H
#define GRAPHLSTAD_H
#include <iostream>
#include <stdexcept>

template <class T>
class AdjacencyListGraph {
private:
    static const int MAX_NODES = 100;

    struct Node { // Node structure
        T value;
        Node* next;
        Node(T val) : value(val), next(nullptr) {}
    };

    Node* adjacents[MAX_NODES]; // Array of pointers to adjacency lists
    T values[MAX_NODES]; // Node values
    int numNodes;

    // Function to find the index of a node
    int findNodeIndex(T value) const {
        for (int i = 0; i < numNodes; ++i) {
            if (values[i] == value)
                return i;
        }
        return -1;
    }

public:
    AdjacencyListGraph() : numNodes(0) {
        for (int i = 0; i < MAX_NODES; ++i) {
            adjacents[i] = nullptr;
        }
    }

    // Check if the graph is empty
    bool isEmpty() const {
        return numNodes == 0;
    }

    // Insert a new node
    void insertNode(T value) {
        if (numNodes >= MAX_NODES)
            throw std::overflow_error("Maximum number of nodes reached");
        values[numNodes++] = value;
    }

    // Insert a new edge
    void insertEdge(T val1, T val2) {
        int u = findNodeIndex(val1);
        int v = findNodeIndex(val2);
        if (u == -1 || v == -1)
            throw std::out_of_range("Invalid node");
        Node* newNode = new Node(val2);
        newNode->next = adjacents[u];
        adjacents[u] = newNode;
    }

    // Delete a node
    void deleteNode(T value) {
        int node = findNodeIndex(value);
        if (node == -1)
            throw std::invalid_argument("Node not found");
        while (adjacents[node] != nullptr) {
            Node* temp = adjacents[node];
            adjacents[node] = adjacents[node]->next;
            delete temp;
        }
        values[node] = T{};
    }

    // Delete an edge
    void deleteEdge(T val1, T val2) {
        int u = findNodeIndex(val1);
        if (u == -1)
            throw std::out_of_range("Invalid node");
        Node* temp = adjacents[u];
        Node* prev = nullptr;
        while (temp != nullptr && temp->value != val2) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != nullptr) {
            if (prev != nullptr)
                prev->next = temp->next;
            else
                adjacents[u] = temp->next;
            delete temp;
        }
    }

    // Print adjacent nodes of a given node
    void printAdjacents(T value) const {
        int node = findNodeIndex(value);
        if (node == -1)
            throw std::invalid_argument("Node not found");
        Node* temp = adjacents[node];
        while (temp != nullptr) {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // Check if a node exists
    bool nodeExists(T value) const {
        return findNodeIndex(value) != -1;
    }

    // Check if an edge exists
    bool edgeExists(T val1, T val2) const {
        int u = findNodeIndex(val1);
        if (u == -1)
            throw std::out_of_range("Invalid node");
        Node* temp = adjacents[u];
        while (temp != nullptr) {
            if (temp->value == val2)
                return true;
            temp = temp->next;
        }
        return false;
    }

    // Print the adjacency list
    void printList() const {
        for (int i = 0; i < numNodes; ++i) {
            if (values[i] != T{}) {
                std::cout << "Node " << values[i] << ": ";
                Node* temp = adjacents[i];
                while (temp != nullptr) {
                    std::cout << temp->value << " ";
                    temp = temp->next;
                }
                std::cout << std::endl;
            }
        }
    }
};

#endif
