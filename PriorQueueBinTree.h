#ifndef PRIORQUEUEBINTREE_H
#define PRIORQUEUEBINTREE_H
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class PriorQueueTree {
private:
    struct Node { // Node structure
        T data;
        Node* left;
        Node* right;
        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };
    Node* root; // Root of the Min-Heap

    // Auxiliary function to insert an element while maintaining the Min-Heap structure
    void insertHeap(Node*& node, T element) {
        if (!node) {
            node = new Node(element);
            return;
        }
        if (element < node->data) {
            swap(node->data, element); // Swap two elements
        }
        if (!node->left) {
            insertHeap(node->left, element);
        } else if (!node->right) {
            insertHeap(node->right, element);
        } else {
            // Insert into the subtree with fewer nodes
            if (height(node->left) <= height(node->right)) {
                insertHeap(node->left, element);
            } else {
                insertHeap(node->right, element);
            }
        }
    }

    // Auxiliary function to find the minimum element
    T findMin(Node* node) const {
        if (!node) throw logic_error("Queue is empty");
        return node->data;
    }

    // Auxiliary function to find the parent node
    Node* findParent(Node* node, Node* target) const {
        if (!node || node == target) return nullptr;
        if (node->left == target || node->right == target) return node;
        Node* leftResult = findParent(node->left, target);
        if (leftResult) return leftResult;
        return findParent(node->right, target);
    }

    // Auxiliary function to delete the minimum element
    void deleteMinHeap(Node*& node) {
        if (!node) return;
        if (!node->left && !node->right) {
            Node** travelerPTR;
            Node* parent = findParent(root, node);
            travelerPTR = &parent;
            (*travelerPTR)->left = nullptr;
            (*travelerPTR)->right = nullptr;
            delete node;
            node = nullptr;
            return;
        }
        Node* minChild = nullptr;
        if (node->left && node->right) {
            minChild = (node->left->data < node->right->data) ? node->left : node->right;
        } else {
            minChild = node->left ? node->left : node->right;
        }
        swap(node->data, minChild->data);
        deleteMinHeap(minChild);
    }

    // Function to calculate the height of a node
    int height(Node* node) const {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    // Function to print the tree (for debugging purposes)
    void printTree(Node* node, int depth = 0) const {
        if (!node) return;
        if (node->right)
            printTree(node->right, depth + 1);
        for (int i = 0; i < depth; ++i) cout << " ";
        cout << node->data << endl;
        if (node->left)
            printTree(node->left, depth + 1);
    }

    // Function to deallocate the tree
    void deleteSubBinTree(Node* node) {
        if (!node) return;
        deleteSubBinTree(node->left);
        deleteSubBinTree(node->right);
        delete node;
    }

public:
    PriorQueueTree() : root(nullptr) {} // createPriorQueue
    ~PriorQueueTree() {
        deleteSubBinTree(root);
    }

    void insert(T element) { // insert
        insertHeap(root, element);
    }

    T min() const { // min
        return findMin(root);
    }

    void deleteMin() { // deleteMin
        deleteMinHeap(root);
    }

    void print() const { // Print the tree for debugging purposes
        printTree(root);
    }
};

#endif
