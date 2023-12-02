#pragma once
#include <iostream>
#include <queue>
#include "registry.h"
using namespace std;

struct SplayTreeNode {
    Registry::Vehicle* vehicle;
    SplayTreeNode *left, *right, *parent;

    SplayTreeNode(Registry::Vehicle* v) : vehicle(v), left(nullptr), right(nullptr), parent(nullptr) {}
};

class SplayTree {
private:
    SplayTreeNode* root;

    // Rotations
    void rotateLeft(SplayTreeNode* &node);
    void rotateRight(SplayTreeNode* &node);
    void splay(SplayTreeNode* &node);

public:
    SplayTree() : root(nullptr) {}
    ~SplayTree();

    // Helper function for the destructor
    void deleteTree(SplayTreeNode* node);

    // Member functions
    void insert(Registry::Vehicle* vehicle);
    Registry::Vehicle* search(const string& model, const string& transmission);
    void BFS() const;
};

#include "Splaytree.h"
#include <queue>

void SplayTree::rotateLeft(SplayTreeNode* &node) {
    if (node == nullptr || node->right == nullptr) return;  // Can't rotate left if node or node's right child is null

    SplayTreeNode* rightChild = node->right;   // rightChild is the right child of node
    node->right = rightChild->left;            // rightChild's left subtree becomes node's right subtree

    if (rightChild->left != nullptr) {
        rightChild->left->parent = node;       // Set parent of rightChild's left child (if exists)
    }

    rightChild->parent = node->parent;         // Link node's parent to rightChild

    if (node->parent == nullptr) {             // node is the root
        root = rightChild;
    } else if (node == node->parent->left) {   // node is a left child
        node->parent->left = rightChild;
    } else {                                   // node is a right child
        node->parent->right = rightChild;
    }

    rightChild->left = node;                   // Place node on rightChild's left
    node->parent = rightChild;                 // Update node's parent
}

// Rotate right is mirror of Rotate left
void SplayTree::rotateRight(SplayTreeNode* &node) {
    if (node == nullptr || node->left == nullptr) return;  // Can't rotate right if node or node's left child is null

    SplayTreeNode* leftChild = node->left;  // leftChild is the left child of node
    node->left = leftChild->right;          // leftChild's right subtree becomes node's left subtree

    if (leftChild->right != nullptr) {
        leftChild->right->parent = node;    // Set parent of leftChild's right child (if exists)
    }

    leftChild->parent = node->parent;       // Link node's parent to leftChild

    if (node->parent == nullptr) {          // node is the root
        root = leftChild;
    } else if (node == node->parent->left) { // node is a left child
        node->parent->left = leftChild;
    } else {                                 // node is a right child
        node->parent->right = leftChild;
    }

    leftChild->right = node;                // Place node on leftChild's right
    node->parent = leftChild;               // Update node's parent
}

void SplayTree::splay(SplayTreeNode* &node) {
    if (node == nullptr) return;

    while (node->parent != nullptr) {  // Continue until node is the root
        if (node->parent->parent == nullptr) {
            // Zig step: node has a parent but no grandparent
            if (node->parent->left == node) {
                rotateRight(node->parent);  // Zig rotation
            } else {
                rotateLeft(node->parent);   // Zag rotation
            }
        } else if (node->parent->left == node && node->parent->parent->left == node->parent) {
            // Zig-Zig step
            rotateRight(node->parent->parent);
            rotateRight(node->parent);
        } else if (node->parent->right == node && node->parent->parent->right == node->parent) {
            // Zig-Zig step (symmetric)
            rotateLeft(node->parent->parent);
            rotateLeft(node->parent);
        } else if (node->parent->right == node && node->parent->parent->left == node->parent) {
            // Zig-Zag step
            rotateLeft(node->parent);
            rotateRight(node->parent);
        } else {
            // Zig-Zag step (symmetric)
            rotateRight(node->parent);
            rotateLeft(node->parent);
        }
    }
}

void SplayTree::insert(Registry::Vehicle* vehicle) {
    // Step 1: Perform standard BST insert
    SplayTreeNode* newNode = new SplayTreeNode(vehicle);
    SplayTreeNode* parentNode = nullptr;
    SplayTreeNode* current = root;

    // Find the correct parent for the new node
    while (current != nullptr) {
        parentNode = current;
        if (vehicle->combCO2 < current->vehicle->combCO2) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // parentNode is the parent of the new node
    newNode->parent = parentNode;

    // Determine which child of the parent new node will be
    if (parentNode == nullptr) {
        // The tree was empty, new node is root
        root = newNode;
    } else if (vehicle->combCO2 < parentNode->vehicle->combCO2) {
        parentNode->left = newNode;
    } else {
        parentNode->right = newNode;
    }

    // Step 2: Splay the tree at the newly inserted node
    splay(newNode);
}

Registry::Vehicle* SplayTree::search(const string& model, const string& transmission) {
    SplayTreeNode* current = root;
    SplayTreeNode* lastVisited = nullptr;

    while (current != nullptr) {
        lastVisited = current;

        if (model == current->vehicle->model) {
            if (transmission == current->vehicle->transmission) {
                splay(current);  // Splay at the found node
                return current->vehicle;  // Return the Vehicle object
            } else {
                // Model matches but transmission doesn't; decide direction
                current = (transmission < current->vehicle->transmission) ? current->left : current->right;
            }
        } else {
            // Decide whether to go left or right based on model
            current = (model < current->vehicle->model) ? current->left : current->right;
        }
    }

    // Splay at the last visited node if the exact vehicle isn't found
    if (lastVisited != nullptr) {
        splay(lastVisited);
    }

    return nullptr;  // No matching node found
}

void SplayTree::deleteTree(SplayTreeNode* node) {
    if (node != nullptr) {
        deleteTree(node->left);   // Delete left subtree
        deleteTree(node->right);  // Delete right subtree
        delete node->vehicle;     // Assuming ownership of vehicle, delete it
        delete node;              // Delete the node itself
    }
}

SplayTree::~SplayTree() {
    deleteTree(root);  // Start the recursive deletion from the root
}

void SplayTree::BFS() const {
    if (root == nullptr) {
        return;  // The tree is empty
    }

    std::queue<SplayTreeNode*> queue;
    queue.push(root);

    while (!queue.empty()) {
        SplayTreeNode* current = queue.front();
        queue.pop();

        // Process the current node (e.g., print its value)
        std::cout << "Model: " << current->vehicle->model
                  << ", Transmission: " << current->vehicle->transmission
                  << ", combCO2: " << current->vehicle->combCO2 << std::endl;

        // Add left and right children to the queue
        if (current->left != nullptr) {
            queue.push(current->left);
        }
        if (current->right != nullptr) {
            queue.push(current->right);
        }
    }
}