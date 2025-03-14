#ifndef ADJMTXGRAPH_H
#define ADJMTXGRAPH_H
#include <iostream>
#include <stdexcept>
#include "PTRStack.h"
#include "PTRQueue.h"

template <class T>
class AdjacencyMatrixGraph {
private:
    static const int MAX_NODES = 100;
    bool matrix[MAX_NODES][MAX_NODES]; // Adjacency matrix
    T values[MAX_NODES]; // Node values
    int numNodes;

    // Function to find the index of a node
    int findNode(const T& value) const {
        for (int i = 0; i < numNodes; ++i) {
            if (values[i] == value)
                return i;
        }
        return -1;
    }

public:
    AdjacencyMatrixGraph() : numNodes(0) {
        for (int i = 0; i < MAX_NODES; ++i) {
            for (int j = 0; j < MAX_NODES; ++j) {
                matrix[i][j] = false;
            }
            values[i] = T(); // Initialize with the default value of type T
        }
    }

    // Check if the graph is empty
    bool isEmpty() const {
        return numNodes == 0;
    }

    // Insert a new node
    void insertNode(const T& value) {
        if (numNodes >= MAX_NODES)
            throw std::overflow_error("Maximum number of nodes reached");
        values[numNodes] = value;
        ++numNodes;
    }

    // Insert a new edge
    void insertEdge(int u, int v) {
        if (u >= numNodes || v >= numNodes)
            throw std::out_of_range("insertEdge: Invalid node");
        matrix[u][v] = true;
    }

    // Delete a node
    void deleteNode(const T& value) {
        int node = findNode(value);
        if (node == -1)
            throw std::invalid_argument("Node not found");
        for (int i = 0; i < numNodes; ++i) {
            matrix[i][node] = false;
            matrix[node][i] = false;
        }
        values[node] = T(); // Reset to the default value of type T
        numNodes--;
    }

    // Delete an edge
    void deleteEdge(int u, int v) {
        if (u >= numNodes || v >= numNodes)
            throw std::out_of_range("deleteEdge: Invalid node");
        matrix[u][v] = false;
    }

    // Print adjacent nodes of a given node
    void printAdjacents(const T& value) const {
        int node = findNode(value);
        if (node == -1)
            throw std::invalid_argument("Node not found");
        for (int i = 0; i < numNodes; ++i) {
            if (matrix[node][i])
                std::cout << values[i] << " ";
        }
        std::cout << std::endl;
    }

    // Check if a node exists
    bool nodeExists(const T& value) const {
        return findNode(value) != -1;
    }

    // Check if an edge exists
    bool edgeExists(int u, int v) const {
        if (u >= numNodes || v >= numNodes)
            throw std::out_of_range("edgeExists: Invalid node");
        return matrix[u][v];
    }

    // Read the index of a node
    int readNode(const T& value) const {
        int node = findNode(value);
        if (node == -1)
            throw std::invalid_argument("Node not found");
        return node;
    }

    // Print the adjacency matrix
    void printMatrix() const {
        std::cout << "Adjacency Matrix:\n";
        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Breadth-first search
    void bfs(const T& initialValue, const T& searchValue) {
        int initialNode = findNode(initialValue);
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
                if (matrix[currentNode][i] && !visited[i]) {
                    queue.pushTail(i);
                    visited[i] = true;
                }
            }
        }
        std::cout << "Node with value " << searchValue << " not found." << std::endl;
    }

    // Depth-first search
    void dfs(const T& initialValue, const T& searchValue) {
        int initialNode = findNode(initialValue);
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
                    if (matrix[currentNode][i] && !visited[i]) {
                        stack.pushStack(i);
                    }
                }
            }
        }
        std::cout << "Node with value " << searchValue << " not found." << std::endl;
    }
};

#endif
