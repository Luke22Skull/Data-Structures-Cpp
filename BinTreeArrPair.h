#ifndef BINTREEARRPAIR_H
#define BINTREEARRPAIR_H

#include <iostream>
#include <stdexcept>
#include "ArrList.h"

using namespace std;

class ArrayBinaryTree {
private:
    ArrList<std::pair<int, bool>> nodes; // List of nodes

public:
    // Constructor
    ArrayBinaryTree() {}

    // Check if the tree is empty
    bool isEmptyTree() const {
        return nodes.isEmptyList();
    }

    // Check if the right child is empty
    bool isEmptyRight(int position) const {
        int right = 2 * position + 2;
        return right >= nodes.getSize() || !nodes.readValueAtIndex(right).second;
    }

    // Check if the left child is empty
    bool isEmptyLeft(int position) const {
        int left = 2 * position + 1;
        return left >= nodes.getSize() || !nodes.readValueAtIndex(left).second;
    }

    // Check if the node is empty
    bool isEmptyNode(int position) const {
        return isEmptyRight(position) && isEmptyLeft(position);
    }

    // Set the data of a node
    void setNodeData(int position, int value) {
        if (position < 0 || position >= nodes.getSize()) {
            throw std::out_of_range("Invalid position");
        }
        nodes.writeValue({value, true}, position);
    }

    // Get the root value
    int getRoot() const {
        if (isEmptyTree()) throw std::runtime_error("Tree is empty");
        return nodes.readValueAtIndex(0).first;
    }

    // Insert the root node
    void insertRoot(int value) {
        nodes.insertValue({value, true}, 0);
    }

    // Insert the right child
    void insertRightChild(int position, int value) {
        int right = 2 * position + 2;
        if (right >= MAX_SIZE) throw std::out_of_range("Out of bounds");
        nodes.insertValue({value, true}, right);
    }

    // Insert the left child
    void insertLeftChild(int position, int value) {
        int left = 2 * position + 1;
        if (left >= MAX_SIZE) throw std::out_of_range("Out of bounds");
        nodes.insertValue({value, true}, left);
    }

    // Unite two trees
    void uniteTrees(ArrayBinaryTree& T1, ArrayBinaryTree& T2) {
        nodes.insertValue({0, true}, 0);
        insertLeftChild(0, T1.getRoot());
        insertRightChild(0, T2.getRoot());
    }

    // Delete a subtree
    void deleteSubTree(int position) {
        if (position < 0 || position >= nodes.getSize()) return;
        nodes.writeValue({nodes.readValueAtIndex(position).first, false}, position);
        deleteSubTree(2 * position + 1);
        deleteSubTree(2 * position + 2);
    }

    // Print the tree
    void printTree() const {
        if (isEmptyTree()) {
            std::cout << "The tree is empty." << std::endl;
            return;
        }
        cout << endl;
        int level = 0;
        int elementsAtLevel = 1;
        int i = 0;
        while (i < nodes.getSize()) {
            // Print indentation for the current level
            int indentation = (1 << (level + 1)) - 1;
            for (int k = 0; k < indentation; ++k) {
                std::cout << " ";
            }
            for (int j = 0; j < elementsAtLevel && i < nodes.getSize(); ++j, ++i) {
                auto node = nodes.readValueAtIndex(i);
                if (node.second) {
                    std::cout << node.first;
                } else {
                    std::cout << "X"; // Indicates an empty node
                }
                // Print spaces between nodes at the same level
                int spacesBetweenNodes = (1 << (level + 2)) - 1;
                for (int k = 0; k < spacesBetweenNodes; ++k) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
            level++;
            elementsAtLevel = 1 << level; // 2^level
        }
    }

    // Get the parent of a node
    int getParent(int position) const {
        if (position < 0 || position >= nodes.getSize()) {
            throw std::out_of_range("Invalid position");
        }
        if (position == 0) {
            throw std::runtime_error("The root node has no parent");
        }
        int parentPos = (position - 1) / 2;
        if (!nodes.readValueAtIndex(parentPos).second) {
            throw std::runtime_error("The parent node does not exist");
        }
        return nodes.readValueAtIndex(parentPos).first;
    }
};

#endif
