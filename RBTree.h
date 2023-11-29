#include <iostream>
#include <queue>
#include "registry.h"

using namespace std;

const bool RED = true;
const bool BLACK = false;

struct RBTreeNode {
    Registry::Vehicle* vehicle;
    bool color;
    RBTreeNode *left, *right, *parent;

    // Constructor
    RBTreeNode(Registry::Vehicle* v) : vehicle(v), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
private:
    RBTreeNode* root;

    // Rotation and violation fixing methods
    void rotateLeft(RBTreeNode* &root, RBTreeNode* &pt);
    void rotateRight(RBTreeNode* &root, RBTreeNode* &pt);
    void fixViolation(RBTreeNode* &root, RBTreeNode* &pt);

public:
    RBTree() : root(nullptr) {}
    ~RBTree();

    // Helper function for destructor
    void deleteTree(RBTreeNode* node);

    // Member functions
    void insert(const Registry::Vehicle& vehicle);
    Registry::Vehicle* search(const string& model, const string& transmission) const;
    void BFS() const;
};