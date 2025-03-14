#ifndef BST_H
#define BST_H
#include <iostream>
#include <stdexcept>
using namespace std;

class BST {
private:
    struct Node {
        Node* right;
        Node* left;
        int value;
        // Constructor with an initial value
        explicit Node (int val) {
            right = nullptr;
            left = nullptr;
            value = val;
        }
        // Default constructor
        Node () {
            right = nullptr;
            left = nullptr;
            value = int{}; // Default value for int type
        }
    };
    // Root node
    Node* root;

    // Get functions
    const int getValue (Node *currentNode) {return currentNode->value;};
    Node* getRight (Node *currentNode) {return currentNode->right;};
    Node* getLeft (Node *currentNode) {return currentNode->left;};

    // Set functions
    void setValue (int val, Node* currentNode) {currentNode->value = val;};
    void setRight (Node* nodeToSet, Node* currentNode) {currentNode->right = nodeToSet;};
    void setLeft (Node* nodeToSet, Node* currentNode) {currentNode->left= nodeToSet;};

    // Search for a node with a specific key
    Node* searchNode(Node* currentNode, int key) {
        if (!currentNode || currentNode->value == key) {
            return currentNode;
        }
        if (key < currentNode->value) {
            return searchNode(currentNode->left, key); // Continue search in the left subtree
        }
        return searchNode(currentNode->right, key); // Continue search in the right subtree
    }

    // Find the minimum node starting from a given node
    Node* findMin(Node* currentNode) {
        while (currentNode && currentNode->left) { // Traverse left nodes
            currentNode = currentNode->left;
        }
        return currentNode; // Return the leftmost node
    }

    // Find the maximum node starting from a given node
    Node* findMax(Node* currentNode) {
        while (currentNode && currentNode->right) { // Traverse right nodes
            currentNode = currentNode->right;
        }
        return currentNode; // Return the rightmost node
    }

public:
    explicit BST(int rootVal) : root(new Node(rootVal)) {}; // Constructor with an initial value
    BST() : root(nullptr) {}; // Default constructor
    ~BST() {};

    Node* getRoot () {return root;};
    void setRoot (Node* nodeToSet) {root = nodeToSet;};

    // Check if the tree or nodes are empty
    bool isBSTempty () {return root == nullptr;};
    bool isRightempty (Node* currentNode) {return currentNode->right == nullptr;};
    bool isLeftempty (Node* currentNode) {return currentNode->left == nullptr;};

    // Insert a value into the tree
    Node* insertValue (Node* currentNode, int value) {
        if (!currentNode) {
            return new Node(value);
        }
        if (value >= currentNode->value) {
            // Insert into the right subtree
            if (isRightempty(currentNode)) {
                Node *nodeToInsert = new Node(value);
                setRight(nodeToInsert, currentNode);
            } else {
                return insertValue(currentNode->right, value);
            }
        } else {
            // Insert into the left subtree
            if (isLeftempty(currentNode)) {
                Node *nodeToInsert = new Node(value);
                setLeft(nodeToInsert, currentNode);
            } else {
                return insertValue(currentNode->left, value);
            }
        }
        return root;
    }

    // Search for a node with a specific key
    bool search(int key) {
        return searchNode(root, key) != nullptr; // Return true if the node is found
    }

    // Search for a node and return it
    Node* searchAndGetNode(int key) {
        return searchNode(root, key);
    }

    // Find the successor of a node with a specific key
    int findSuccessor(int key) {
        Node* current = searchNode(root, key); // Check if the node exists
        if (!current) {
            throw std::invalid_argument("Key not found");
        }
        if (current->right) {
            return findMin(current->right)->value; // Return the minimum value in the right subtree
        }
        Node* successor = nullptr;
        Node* ancestor = root;
        while (ancestor != current) {
            if (key < ancestor->value) {
                successor = ancestor; // Move successor if key is less than ancestor's value
                ancestor = ancestor->left;
            } else {
                ancestor = ancestor->right;
            }
        }
        if (successor) {
            return successor->value; // Return the successor's value
        }
        throw std::invalid_argument("Successor not found");
    }

    // Find the predecessor of a node with a specific key
    int findPredecessor(int key) {
        Node* current = searchNode(root, key);
        if (!current) {
            throw std::invalid_argument("Key not found");
        }
        if (current->left) {
            return findMax(current->left)->value; // Return the maximum value in the left subtree
        }
        Node* predecessor = nullptr;
        Node* ancestor = root;
        while (ancestor != current) {
            if (key > ancestor->value) {
                predecessor = ancestor; // Move predecessor if key is greater than ancestor's value
                ancestor = ancestor->right;
            } else {
                ancestor = ancestor->left;
            }
        }
        if (predecessor) {
            return predecessor->value; // Return the predecessor's value
        }
        throw std::invalid_argument("Predecessor not found");
    }

    // Delete a subtree starting from a node
    Node* deleteSubBinTree (Node* currentNode) {
        if (!currentNode) {
            this->printInOrder(getRoot()); // Print tree for debugging
            throw std::invalid_argument("Null node provided");
        }
        Node** travelerPointer = &currentNode; // Create double pointer to currentNode
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

    // Print the values of the tree (in order)
    void printInOrder(Node* node) {
        if (node == nullptr) return;
        printInOrder(node->left);
        std::cout << node->value << " ";
        printInOrder(node->right);
    }
};

#endif
