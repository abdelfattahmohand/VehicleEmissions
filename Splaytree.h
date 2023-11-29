#include <iostream>
#include <queue>
#include "registry.h"

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
