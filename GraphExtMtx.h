#ifndef GRAPHEXTMTX_H
#define GRAPHEXTMTX_H 
#include <iostream>
#include <stdexcept>
#include "PTRQueue.h"
#include "PTRStack.h"

template <class T>
class ExtendedAdjacencyMatrixGraph {
private:
    static const int MAX_NODES = 100;
    int matrix[MAX_NODES][MAX_NODES]; // Adjacency matrix
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
    ExtendedAdjacencyMatrixGraph() : numNodes(0) {
        for (int i = 0; i < MAX_NODES; ++i) {
            for (int j = 0; j < MAX_NODES; ++j) {
                matrix[i][j] = 0;
            }
            values[i] = -1;
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
        values[numNodes] = value;
        ++numNodes;
    }

    // Insert a new edge with a weight
    void insertEdge(int u, int v, int weight = 1) {
        if (u >= numNodes || v >= numNodes)
            throw std::out_of_range("Invalid node");
        if (weight <= 0)
            throw std::invalid_argument("Weight must be positive");
        matrix[u][v] = weight;
    }

    // Delete a node
    void deleteNode(T value) {
        int node = findNodeIndex(value);
        if (node == -1)
            throw std::invalid_argument("Node not found");
        for (int i = 0; i < numNodes; ++i) {
            matrix[i][node] = 0;
            matrix[node][i] = 0;
        }
        values[node] = -1;
    }

    // Delete an edge
    void deleteEdge(int u, int v) {
        if (u >= numNodes || v >= numNodes)
            throw std::out_of_range("Invalid node");
        matrix[u][v] = 0;
    }

    // Print adjacent nodes of a given node
    void printAdjacents(T value) const {
        int node = findNodeIndex(value);
        if (node == -1)
            throw std::invalid_argument("Node not found");
        for (int i = 0; i < numNodes; ++i) {
            if (matrix[node][i] > 0)
                std::cout << values[i] << " ";
        }
        std::cout << std::endl;
    }

    // Check if a node exists
    bool nodeExists(T value) const {
        return findNodeIndex(value) != -1;
    }

    // Check if an edge exists
    bool edgeExists(int u, int v) const {
        if (u >= numNodes || v >= numNodes)
            throw std::out_of_range("Invalid node");
        return matrix[u][v] > 0;
    }

    // Read the index of a node
    int readNode(T value) const {
        int node = findNodeIndex(value);
        if (node == -1)
            throw std::invalid_argument("Node not found");
        return node;
    }

    // Read the weight of an edge
    int readWeight(int u, int v) const {
        if (u >= numNodes || v >= numNodes)
            throw std::out_of_range("Invalid node");
        return matrix[u][v];
    }

    // Print the adjacency matrix
    void printMatrix() const {
        std::cout << "Extended Adjacency Matrix:\n";
        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Breadth-first search
    void bfs(T initialValue, T searchValue) {
        int initialNode = findNodeIndex(initialValue);
        if (initialNode == -1)
            throw std::invalid_argument("Initial node not found");
        bool visited[MAX_NODES] = {false};
        PTR_Queue<int> queue;
        queue.pushTail(initialNode);
        visited[initialNode] = true;
        while (!queue.isEmptyQueue()) {
            int currentNode = queue.readHead();
            queue.deleteHead();
            if (values[currentNode] == searchValue) {
                std::cout << "Node found with value: " << searchValue << std::endl;
                return;
            }
            for (int i = 0; i < numNodes; ++i) {
                if (matrix[currentNode][i] > 0 && !visited[i]) {
                    queue.pushTail(i);
                    visited[i] = true;
                }
            }
        }
        std::cout << "Node with value " << searchValue << " not found." << std::endl;
    }

    // Depth-first search
    void dfs(T initialValue, T searchValue) {
        int initialNode = findNodeIndex(initialValue);
        if (initialNode == -1)
            throw std::invalid_argument("Initial node not found");
        bool visited[MAX_NODES] = {false};
        PTR_Stack<int> stack;
        stack.pushStack(initialNode);
        while (!stack.isEmptyStack()) {
            int currentNode = stack.readStack();
            stack.popStack();
            if (!visited[currentNode]) {
                visited[currentNode] = true;
                if (values[currentNode] == searchValue) {
                    std::cout << "Node found with value: " << searchValue << std::endl;
                    return;
                }
                for (int i = 0; i < numNodes; ++i) {
                    if (matrix[currentNode][i] > 0 && !visited[i]) {
                        stack.pushStack(i);
                    }
                }
            }
        }
        std::cout << "Node with value " << searchValue << " not found." << std::endl;
    }
};

#endif
