#ifndef PTR_GRAPH_H
#define PTR_GRAPH_H
#include <iostream>
#include <stdexcept>

template <class T>
class PTR_Graph {
private:
    struct Node { // Node structure
        T value;
        Node* next;
        Node(T val) : value(val), next(nullptr) {}
    };

    struct AdjacencyList { // Adjacency list structure
        Node* head;
        AdjacencyList() : head(nullptr) {}
    };

    struct Vertex { // Vertex structure
        T value;
        AdjacencyList adjacents;
        Vertex* next;
        Vertex(T val) : value(val), next(nullptr) {}
    };

    Vertex* head;

    // Function to find a vertex with a specific value
    Vertex* findVertex(T value) const {
        Vertex* temp = head;
        while (temp) {
            if (temp->value == value)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

public:
    PTR_Graph() : head(nullptr) {} // Constructor

    // Check if the graph is empty
    bool isEmpty() const {
        return head == nullptr;
    }

    // Insert a new vertex
    void insertNode(T value) {
        if (nodeExists(value))
            throw std::invalid_argument("Node already exists");
        Vertex* newVertex = new Vertex(value);
        newVertex->next = head;
        head = newVertex;
    }

    // Insert a new edge
    void insertEdge(T u, T v) {
        Vertex* vertexU = findVertex(u);
        Vertex* vertexV = findVertex(v);
        if (!vertexU || !vertexV)
            throw std::out_of_range("Invalid node");
        Node* newNode = new Node(v);
        newNode->next = vertexU->adjacents.head;
        vertexU->adjacents.head = newNode;
    }

    // Delete a vertex
    void deleteNode(T value) {
        Vertex** ptr = &head;
        while (*ptr && (*ptr)->value != value) {
            ptr = &((*ptr)->next);
        }
        if (*ptr) {
            Node* tempA = (*ptr)->adjacents.head;
            while (tempA) {
                Node* toDelete = tempA;
                tempA = tempA->next;
                delete toDelete;
            }
            Vertex* toDelete = *ptr;
            *ptr = (*ptr)->next;
            delete toDelete;
        }
    }

    // Delete an edge
    void deleteEdge(T u, T v) {
        Vertex* vertexU = findVertex(u);
        if (!vertexU)
            throw std::out_of_range("Invalid node");
        Node** ptr = &(vertexU->adjacents.head);
        while (*ptr && (*ptr)->value != v) {
            ptr = &((*ptr)->next);
        }
        if (*ptr) {
            Node* toDelete = *ptr;
            *ptr = (*ptr)->next;
            delete toDelete;
        }
    }

    // Print adjacent vertices of a given vertex
    void printAdjacents(T value) const {
        Vertex* vertex = findVertex(value);
        if (!vertex)
            throw std::invalid_argument("Node not found");
        Node* temp = vertex->adjacents.head;
        while (temp) {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // Check if a node exists
    bool nodeExists(T value) const {
        return findVertex(value) != nullptr;
    }

    // Check if an edge exists
    bool edgeExists(T u, T v) const {
        Vertex* vertexU = findVertex(u);
        if (!vertexU)
            throw std::out_of_range("Invalid node");
        Node* temp = vertexU->adjacents.head;
        while (temp) {
            if (temp->value == v)
                return true;
            temp = temp->next;
        }
        return false;
    }

    // Print the graph
    void printGraph() const {
        Vertex* temp = head;
        while (temp) {
            std::cout << "Node " << temp->value << ": ";
            Node* adj = temp->adjacents.head;
            while (adj) {
                std::cout << adj->value << " ";
                adj = adj->next;
            }
            std::cout << std::endl;
            temp = temp->next;
        }
    }
};

#endif
