//#include "RBTree.h"
//#include "registry.h"
//
//void RBTree::rotateLeft(RBTreeNode* &root, RBTreeNode* &pt) {
//    RBTreeNode* pt_right = pt->right; // Node to the right of pt
//
//    pt->right = pt_right->left; // pt's new right child is pt_right's left child
//
//    if (pt->right != nullptr) {
//        pt->right->parent = pt; // Update parent
//    }
//
//    pt_right->parent = pt->parent; // Update pt_right's parent
//
//    if (pt->parent == nullptr) {
//        root = pt_right; // pt_right becomes new root if pt was root
//    } else if (pt == pt->parent->left) {
//        pt->parent->left = pt_right; // Update left child of pt's parent
//    } else {
//        pt->parent->right = pt_right; // Update right child of pt's parent
//    }
//
//    pt_right->left = pt; // Complete rotation
//    pt->parent = pt_right; // Update pt's parent
//}
//
//// rotateRight is just inverse of rorateLeft:
//void RBTree::rotateRight(RBTreeNode* &root, RBTreeNode* &pt) {
//    RBTreeNode* pt_left = pt->left; // Node to the left of pt
//
//    pt->left = pt_left->right; // pt's new left child is pt_left's right child
//
//    if (pt->left != nullptr) {
//        pt->left->parent = pt; // Update parent
//    }
//
//    pt_left->parent = pt->parent; // Update pt_left's parent
//
//    if (pt->parent == nullptr) {
//        root = pt_left; // pt_left becomes new root if pt was root
//    } else if (pt == pt->parent->right) {
//        pt->parent->right = pt_left; // Update right child of pt's parent
//    } else {
//        pt->parent->left = pt_left; // Update left child of pt's parent
//    }
//
//    pt_left->right = pt; // Complete rotation
//    pt->parent = pt_left; // Update pt's parent
//}
//
//void RBTree::fixViolation(RBTreeNode* &root, RBTreeNode* &pt) {
//    // Parent and grandparent pointers
//    RBTreeNode *parent_pt = nullptr;
//    RBTreeNode *grand_parent_pt = nullptr;
//
//    while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
//
//        parent_pt = pt->parent;
//        grand_parent_pt = pt->parent->parent;
//
//        // Case A, Parent of pt is left child of Grand-parent of pt
//        if (parent_pt == grand_parent_pt->left) {
//
//            RBTreeNode *uncle_pt = grand_parent_pt->right;
//
//            // Case 1, uncle of pt is also red, only Recoloring
//            if (uncle_pt != nullptr && uncle_pt->color == RED) {
//                grand_parent_pt->color = RED;
//                parent_pt->color = BLACK;
//                uncle_pt->color = BLACK;
//                pt = grand_parent_pt;
//            } else {
//                // Case 2, pt is right child of its parent, Left-rotation required
//                if (pt == parent_pt->right) {
//                    rotateLeft(root, parent_pt);
//                    pt = parent_pt;
//                    parent_pt = pt->parent;
//                }
//
//                // Case 3, pt is left child of its parent Right-rotation required */
//                rotateRight(root, grand_parent_pt);
//                swap(parent_pt->color, grand_parent_pt->color);
//                pt = parent_pt;
//            }
//        } else {
//            // Case B, Parent of pt is right child of Grand-parent of pt
//            RBTreeNode *uncle_pt = grand_parent_pt->left;
//
//            // Case 1, uncle of pt is also red, only Recoloring required
//            if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
//                grand_parent_pt->color = RED;
//                parent_pt->color = BLACK;
//                uncle_pt->color = BLACK;
//                pt = grand_parent_pt;
//            } else {
//                //Case 2, pt is left child of its parent, Right-rotation required
//                if (pt == parent_pt->left) {
//                    rotateRight(root, parent_pt);
//                    pt = parent_pt;
//                    parent_pt = pt->parent;
//                }
//
//                //Case 3, pt is right child of its paren Left-rotation required */
//                rotateLeft(root, grand_parent_pt);
//                swap(parent_pt->color, grand_parent_pt->color);
//                pt = parent_pt;
//            }
//        }
//    }
//
//    root->color = BLACK; // Keep the root always black
//}
//
//void RBTree::insert(const Registry::Vehicle& vehicle) {
//    // Create a new node
//    RBTreeNode *pt = new RBTreeNode(new Registry::Vehicle(vehicle));
//
//    // Step 1: Perform standard BST insert
//    RBTreeNode *parent = nullptr;
//    RBTreeNode *current = root;
//
//    // Find the parent node under which this new node will be inserted
//    while (current != nullptr) {
//        parent = current;
//        if (vehicle.combCO2 <= current->vehicle->combCO2) {  // Allow duplicates on left
//            current = current->left;
//        } else {
//            current = current->right;
//        }
//    }
//
//    // Assign the parent to the new node
//    pt->parent = parent;
//
//    // If the tree is empty, the new node is the root
//    if (parent == nullptr) {
//        root = pt;
//    } else if (vehicle.combCO2 < parent->vehicle->combCO2) {
//        parent->left = pt;
//    } else {
//        parent->right = pt;
//    }
//
//    // Step 2: Fix Red Black Tree violations
//    fixViolation(root, pt);
//}
//
//// BFS for debugging:
//void RBTree::BFS() const {
//    if (root == nullptr) return;
//
//    std::queue<RBTreeNode*> q;
//    q.push(root);
//
//    while (!q.empty()) {
//        RBTreeNode* current = q.front();
//        q.pop();
//
//        // Process the current node
//        std::cout << current->vehicle->combCO2 << " (" << (current->color == RED ? "R" : "B") << ") ";
//
//        // Enqueue left child
//        if (current->left != nullptr) {
//            q.push(current->left);
//        }
//
//        // Enqueue right child
//        if (current->right != nullptr) {
//            q.push(current->right);
//        }
//    }
//
//    std::cout << std::endl;
//}
//
//Registry::Vehicle* RBTree::search(const string& model, const string& transmission) const {
//    RBTreeNode* current = root;
//
//    while (current != nullptr) {
//        if (model == current->vehicle->model && transmission == current->vehicle->transmission) {
//            return current->vehicle;  // Return the Vehicle object
//        }
//            // Decide whether to go left or right, for example, based on model
//        else if (model < current->vehicle->model) {
//            current = current->left;
//        } else {
//            current = current->right;
//        }
//    }
//
//    return nullptr;  // No matching node found
//}
//
//void RBTree::deleteTree(RBTreeNode* node) {
//    if (node != nullptr) {
//        deleteTree(node->left);   // Delete left subtree
//        deleteTree(node->right);  // Delete right subtree
//        delete node->vehicle;     // Delete the vehicle if dynamically allocated
//        delete node;              // Delete the node itself
//    }
//}
//
//RBTree::~RBTree() {
//    deleteTree(root);  // Start the deletion process from the root
//}
//
