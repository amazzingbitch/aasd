#ifndef UNTITLED11_NODERB_H
#define UNTITLED11_NODERB_H

template <typename T, typename K>
class NodeRB {
public:
    NodeRB(): left(nullptr), right(nullptr), parent(nullptr) {}
    NodeRB(T value_, K key_): value(value_), key(key_), left(nullptr), right(nullptr), parent(nullptr) {}
    NodeRB *left = nullptr;
    NodeRB *right = nullptr;
    NodeRB *parent = nullptr;
    T value;
    K key;
    bool color = true; // black


// returns pointer to uncle
    NodeRB *uncle() {
        // If no parent or grandparent, then no uncle
        if (parent == nullptr || parent->parent == nullptr)
            return nullptr;

        if (parent->isOnLeft())
            // uncle on right
            return parent->parent->right;
        else
            // uncle on left
            return parent->parent->left;
    }

// check if node is left child of parent
    bool isOnLeft() { return this == parent->left; }

// returns pointer to sibling
    NodeRB *sibling() {
        // sibling null if no parent
        if (parent == nullptr)
            return nullptr;

        if (isOnLeft())
            return parent->right;

        return parent->left;
    }

    void moveDown(NodeRB *nParent) {
        if (parent != nullptr) {
            if (isOnLeft()) {
                parent->left = nParent;
            } else {
                parent->right = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }

    bool hasRedChild() {
        return (left != nullptr && left->color == true) ||
               (right != nullptr && right->color == true);
    }
};


#endif //UNTITLED11_NODERB_H
