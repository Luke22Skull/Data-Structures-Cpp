#ifndef PTR_NTREE_H 
#define PTR_NTREE_H
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class PTR_NTree {
private:
    struct TreeNode { // Node structure
        T data;
        TreeNode** children;
        int num_children;
        int level;
        TreeNode(T value, int max_children, int lvl) {
            data = value;
            children = new TreeNode*[max_children]{};
            num_children = 0;
            level = lvl;
        }
        ~TreeNode() {
            delete[] children;
        }
    };
    TreeNode* root;
    int degree;

    // Function to delete a subtree
    void auxDeleteSubtree(TreeNode* node) {
        if (!node) return;
        for (int i = 0; i < node->num_children; i++) {
            deleteSubtree(node->children[i]);
        }
        if (isLeaf(node)) {
            TreeNode** travelerPTR;
            TreeNode* parent = getFather(node);
            travelerPTR = &parent;
            (*travelerPTR)->children[getChildIndex(parent, node)] = nullptr;
            delete node;
            node = nullptr;
            return;
        }
    }

    // Function to find the parent of a node
    TreeNode* findParent(TreeNode* node, TreeNode* target) {
        if (!node || node->num_children == 0) return nullptr;
        for (int i = 0; i < node->num_children; i++) {
            if (node->children[i] == target) return node;
            TreeNode* found = findParent(node->children[i], target);
            if (found) return found;
        }
        return nullptr;
    }

    // Function to get the index of a child node
    int getChildIndex(TreeNode* parent, TreeNode* child) {
        if (!parent || !child) throw invalid_argument("Null nodes.");
        for (int i = 0; i < parent->num_children; i++) {
            if (parent->children[i] == child) return i;
        }
        return -1; // Child node not found
    }

    // Function to print the tree
    void print(TreeNode* node, int level) {
        if (!node) return;
        for (int i = 0; i < level; i++) cout << " "; // Indentation
        cout << node->data << endl;
        for (int i = 0; i < node->num_children; i++) {
            print(node->children[i], level + 1);
        }
    }

public:
    PTR_NTree(int max_num_children) : root(nullptr), degree(max_num_children) {}
    ~PTR_NTree() {
        deleteSubtree(root);
    }

    // Check if the tree is empty
    bool isEmptyTree() {
        return root == nullptr;
    }

    // Insert the root node
    void insertRoot(T value) {
        if (root) throw runtime_error("Root already exists.");
        root = new TreeNode(value, degree, 0);
    }

    // Get the root node
    TreeNode* getRoot() {
        return root;
    }

    // Get the parent of a node
    TreeNode* getFather(TreeNode* node) {
        if (!node || node == root) return nullptr;
        return findParent(root, node);
    }

    // Check if a node is a leaf
    bool isLeaf(TreeNode* node) {
        if (!node) throw invalid_argument("Null node.");
        return node->num_children == 0;
    }

    // Get the first child of a node
    TreeNode* firstChild(TreeNode* node) {
        if (!node || node->num_children == 0) return nullptr;
        return node->children[0];
    }

    // Get the last sibling of a node
    TreeNode* lastSibling(TreeNode* node) {
        if (!node || !root) return nullptr;
        TreeNode* parent = nullptr;
        for (TreeNode* n = root; n; n = firstChild(n)) {
            for (int i = 0; i < n->num_children; i++) {
                if (n->children[i] == node) {
                    parent = n;
                    break;
                }
            }
        }
        return parent ? parent->children[parent->num_children - 1] : nullptr;
    }

    // Get the next sibling of a node
    TreeNode* nextSibling(TreeNode* node) {
        if (!node || !root) return nullptr;
        TreeNode* parent = nullptr;
        for (TreeNode* n = root; n; n = firstChild(n)) {
            for (int i = 0; i < n->num_children - 1; i++) {
                if (n->children[i] == node) {
                    return n->children[i + 1];
                }
            }
        }
        return nullptr;
    }

    // Insert the first subtree
    void insertFirstSubtree(TreeNode* node, PTR_NTree<T>& subtree) {
        if (!node || !subtree.root) throw invalid_argument("Null node or subtree.");
        if (node->num_children >= degree) throw runtime_error("Maximum number of children reached.");
        for (int i = node->num_children; i > 0; i--) {
            node->children[i] = node->children[i - 1];
        }
        node->children[0] = subtree.root;
        node->num_children++;
        subtree.root = nullptr;
    }

    // Insert a subtree
    void insertSubtree(TreeNode* node, PTR_NTree<T>& subtree) {
        if (!node || !subtree.root) throw invalid_argument("Null node or subtree.");
        if (node->num_children >= degree) throw runtime_error("Maximum number of children reached.");
        node->children[node->num_children++] = subtree.root;
        subtree.root = nullptr;
    }

    // Delete a subtree
    void deleteSubtree(TreeNode* node) {
        if (!node) return;
        auxDeleteSubtree(node);
    }

    // Print the tree
    void printTree() {
        print(root, 0);
    }
};

#endif
