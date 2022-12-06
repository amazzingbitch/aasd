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
        if (parent == nullptr or parent->parent == nullptr)
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


    bool hasRedChild() {
        return (left != nullptr and left->color == true) or
               (right != nullptr and right->color == true);
    }
};


#endif //UNTITLED11_NODERB_H
