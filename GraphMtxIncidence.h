#ifndef GRAPHMTXINCIDENCE_H
#define GRAPHMTXINCIDENCE_H
#include <iostream>
#include <stdexcept>

template <class T>
class IncidenceMatrixGraph {
private:
    static const int MAX_NODES = 100;
    static const int MAX_EDGES = 200;
    int matrix[MAX_NODES][MAX_EDGES]; // Incidence matrix
    T values[MAX_NODES]; // Node values
    int numNodes;
    int numEdges;

    // Function to find the index of a node
    int findNodeIndex(T value) const {
        for (int i = 0; i < numNodes; ++i) {
            if (values[i] == value)
                return i;
        }
        return -1;
    }

public:
    IncidenceMatrixGraph() : numNodes(0), numEdges(0) {
        for (int i = 0; i < MAX_NODES; ++i) {
            values[i] = -1;
            for (int j = 0; j < MAX_EDGES; ++j) {
                matrix[i][j] = 0;
            }
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
        if (u == -1 || v == -1 || numEdges >= MAX_EDGES)
            throw std::out_of_range("Invalid node or edge");
        matrix[u][numEdges] = 1;
        matrix[v][numEdges] = -1;
        numEdges++;
    }

    // Delete a node
    void deleteNode(T value) {
        int node = findNodeIndex(value);
        if (node == -1)
            throw std::invalid_argument("Node not found");
        values[node] = -1;
        for (int j = 0; j < numEdges; ++j) {
            matrix[node][j] = 0;
        }
    }

    // Delete an edge
    void deleteEdge(int edgeIndex) {
        if (edgeIndex >= numEdges)
            throw std::out_of_range("Invalid edge");
        for (int i = 0; i < numNodes; ++i) {
            matrix[i][edgeIndex] = 0;
        }
    }

    // Print adjacent nodes of a given node
    void printAdjacents(T value) const {
        int node = findNodeIndex(value);
        if (node == -1)
            throw std::invalid_argument("Node not found");
        for (int j = 0; j < numEdges; ++j) {
            if (matrix[node][j] != 0) {
                for (int i = 0; i < numNodes; ++i) {
                    if (matrix[i][j] != 0 && i != node)
                        std::cout << values[i] << " ";
                }
            }
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
        int v = findNodeIndex(val2);
        if (u == -1 || v == -1)
            throw std::out_of_range("Invalid node");
        for (int j = 0; j < numEdges; ++j) {
            if (matrix[u][j] == 1 && matrix[v][j] == -1)
                return true;
        }
        return false;
    }

    // Print the incidence matrix
    void printMatrix() const {
        std::cout << "Incidence Matrix:\n";
        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numEdges; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif
