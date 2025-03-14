#ifndef BINTREEPTR_H
#define BINTREEPTR_H
#include <iostream>
#include <stdexcept>
#include "PTRStack.h"
#include "PTRQueue.h"
using namespace std;

template <class T>
class BinTree {
private:
    struct BinTreeNode {
        T data;
        BinTreeNode *left;
        BinTreeNode *right;
        explicit BinTreeNode (T value) {
            data = value;
            left = nullptr;
            right = nullptr;
        }
        BinTreeNode () {
            data = T{};
            left = nullptr;
            right = nullptr;
        }
    };
    BinTreeNode *root;

    BinTreeNode* getFatherRecursive(BinTreeNode* parent, BinTreeNode* currentNode) {
        if (!parent) return nullptr; // Base case: null node
        // Check if the current node is a child of the parent node
        if (getLeft(parent) == currentNode || getRight(parent) == currentNode) {
            return parent;
        }
        // Recursively search in the left and right subtrees
        getFatherRecursive(getLeft(parent), currentNode);
        getFatherRecursive(getRight(parent), currentNode);
    }

    void printInOrder(const BinTreeNode* currentNode) const {
        if (!currentNode) return; // Base case: null node
        printInOrder(currentNode->left); // Visit the left subtree
        std::cout << currentNode->data << " "; // Print the current node's value
        printInOrder(currentNode->right); // Visit the right subtree
    }

public:
    explicit BinTree(T value) : root(new BinTreeNode(value)) {}; // Constructor with root value
    BinTree() : root(nullptr) {}; // Default constructor
    ~BinTree() {
        deleteSubBinTree(root);
        delete root;
    }

    void printTree () const {
        printInOrder(this->root);
        std::cout << "\n" << std::endl;
    }

    // Check if the tree or nodes are empty
    bool isEmptyTree() {return this->root == nullptr;};
    bool isEmptyDx(const BinTreeNode* currentNode) {return currentNode->right == nullptr;};
    bool isEmptySx(const BinTreeNode* currentNode) {return currentNode->left == nullptr;};
    bool isEmptyNode(const BinTreeNode* currentNode) {return isEmptyDx(currentNode) && isEmptySx(currentNode);};

    // Set the value of a node
    void setNodeData(BinTreeNode *currentNode, T value) {
        if (!currentNode) throw std::invalid_argument("Null node.");
        currentNode->data = value;
    }

    // Read the value of a node
    T readNodeData(BinTreeNode *currentNode) const {return currentNode->data;};

    // Get left, right, and root nodes
    BinTreeNode* getLeft (BinTreeNode* currentNode) {return currentNode->left;};
    BinTreeNode* getRight (BinTreeNode* currentNode) {return currentNode->right;};
    BinTreeNode* getRoot() const {return this->root;};

    // Get the parent node
    BinTreeNode* getFather(BinTreeNode* currentNode) {
        if (!root || root == currentNode || !currentNode) return nullptr; // Root has no parent
        return getFatherRecursive(root, currentNode);
    }

    // Insert parent node with default value
    BinTreeNode* insertFather(BinTreeNode* currentNode) {
        if (!currentNode)
            throw std::invalid_argument("Null pointer provided.");
        if (currentNode == root) {
            BinTreeNode* newRoot = new BinTreeNode(T{}); // Create new node with default value
            newRoot->left = currentNode;
            return newRoot;
        } else {
            return currentNode;
        }
    }

    // Insert right child node with default value
    BinTreeNode* insertChildDx(BinTreeNode* currentNode) {
        if (!currentNode)
            throw std::invalid_argument("Null pointer");
        else if (!isEmptyDx(currentNode)) {
            return insertChildDx(currentNode->right); // Recursively insert right child
        }
        BinTreeNode* newChildNode = new BinTreeNode(); // Create default empty node
        currentNode->right = newChildNode; // Set right pointer to new node
        return newChildNode; // Return new node
    }

    // Insert left child node with default value
    BinTreeNode* insertChildSx(BinTreeNode* currentNode) {
        if (!currentNode)
            throw std::invalid_argument("Null pointer");
        else if (!isEmptySx(currentNode)) {
            return insertChildSx(currentNode->left); // Recursively insert left child
        }
        BinTreeNode* newChildNode = new BinTreeNode();
        currentNode->left = newChildNode;
        return newChildNode;
    }

    // Unite two trees into one
    BinTree uniteTrees(BinTree& T1, BinTree& T2) {
        BinTree<T> unionTree(T{}); // Create new tree with empty root
        if (!T1.isEmptyTree() && !T2.isEmptyTree()) {
            unionTree.root->left = T1.root; // Set T1 as left subtree
            unionTree.root->right = T2.root; // Set T2 as right subtree
        } else {
            throw std::invalid_argument("Both trees must be non-empty for union.");
        }
        return unionTree;
    }

    // Delete a subtree starting from a node
    BinTreeNode* deleteSubBinTree (BinTreeNode* currentNode) {
        if (!currentNode) {
            this->printTree(); // Print tree for debugging
            throw std::invalid_argument("Null node provided");
        }
        BinTreeNode** travelerPointer = &currentNode; // Create double pointer to currentNode
        while ((*travelerPointer)->left || (*travelerPointer)->right) { // Traverse until both left and right are null
            if ((*travelerPointer)->left) {
                travelerPointer = &(*travelerPointer)->left; // Move to left child
            } else if ((*travelerPointer)->right) {
                travelerPointer = &(*travelerPointer)->right; // Move to right child
            }
        }
        if (*travelerPointer == currentNode) // If travelerPointer equals initial currentNode, stop
            return currentNode;
        else {
            delete *travelerPointer; // Delete node and set to nullptr
            *travelerPointer = nullptr;
            return deleteSubBinTree(currentNode); // Recursively call function on currentNode
        }
    }

    // Breadth-first search for a node with a specific value
    BinTreeNode* bfs(T value) const {
        if (!root) return nullptr; // Empty tree
        PTR_Queue<BinTreeNode*> queue; // Use implemented queue
        queue.pushTail(root);
        while (!queue.isEmptyQueue()) {
            BinTreeNode* node = queue.readHead();
            queue.deleteHead();
            if (node->data == value) return node;
            if (node->left) queue.pushTail(node->left);
            if (node->right) queue.pushTail(node->right);
        }
        return nullptr; // Node not found
    }

    // Depth-first search for a node with a specific value
    BinTreeNode* dfs(T value) const {
        if (!root) return nullptr; // Empty tree
        PTR_Stack<BinTreeNode*> stack; // Use implemented stack
        stack.pushStack(root);
        while (!stack.isEmptyStack()) {
            BinTreeNode* node = stack.readStack();
            stack.popStack();
            if (node->data == value) return node;
            if (node->right) stack.pushStack(node->right);
            if (node->left) stack.pushStack(node->left);
        }
        return nullptr; // Node not found
    }
};

#endif
