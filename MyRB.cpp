//
// Created by Eldo on 07.11.2022.
//

#include <list>
#include "MyRB.h"

template<typename T, typename K>
MyRB<T, K>::MyRB() { size = 0; root = nullptr; }

template<typename T, typename K>
bool MyRB<T, K>::IsEmpty() { return root == nullptr; }

template<typename T, typename K>
MyRB<T, K>::~MyRB() { Clear(root); }

template<typename T, typename K>
bool* MyRB<T, K>::Insert(K k, T data) {
    /*bool* ins = new bool;
    *ins = false;
    t = Insert1(t, k, data, 0, ins, nullptr);
    t->color = false;
    return ins;*/

    bool* ins = new bool;
    *ins = false;

    if (root == nullptr) {
        root = new NodeRB<T,K>(data, k);
        root->color = false;
        *ins = true;
    } else
        root = insertHelp(root, k, data, ins);

    return ins;
}

template<typename T, typename K>
NodeRB<T, K>* MyRB<T, K>::insertHelp(NodeRB<T, K>* t, K k, T data, bool* inserted) {
    /*if (t == nullptr) {
        t = new NodeRB<T,K>(data, k);
        if (root == nullptr) { root = t ; }
        t->parent = p;
        t->color = true;
        *inserted = true;
        size++;
        *//*Show(GetRoot(), 0);
        cout << endl;*//*
        return t;
    }
    if (k == t->key) {
        *inserted = false;
        NumOfViews++;
        return t;
    }
    if (t->left != nullptr && t->right != nullptr){
        if (t->left->color && t->right->color) {
            t->color = true;
            t->left->color = t->right->color = false;
            *inserted = false;
            NumOfViews++;
            //return t;
        }
    }
    bool* ins = new bool;
    if (k < t->key) {
        t->left = Insert1(t->left, k, data, 0, ins, t);
        if (t->left != nullptr)
        if (t->color && t->left->color && s == 1) { t = R(t); cout << "rt" << k << endl;}
        if (t->left != nullptr)
        if (t->left->left != nullptr) {
            if (t->color && t->left->left->color) {
                t = R(t);
                cout << "rt" << k << endl;
                t->color = false;
                if (t->right != nullptr) t->right->color = true;
            }
        }
        inserted = ins;
        NumOfViews++;
        return t;
    } else {
        t->right = Insert1(t->right, k, data, 1, ins, t);
        if (t->right != nullptr)
        if (t->color && t->right->color && s == 0) {t = L(t); cout << "lt" << k << endl; }
        if (t->right != nullptr)
        if (t->right->right != nullptr) {
            if (t->color && t->right->right->color) {
                t = L(t);
                cout << "lt" << k << endl;
                t->color = false;
                if (t->left != nullptr) t->left->color = true;
            }
        }
        inserted = ins;
        NumOfViews++;
        return t;
    }*/
    bool f = false;
    if (t == nullptr)
        return (new NodeRB<T,K>(data, k));
    else if (k == t->key) {
        *inserted = false;
    }
    else if (k < t->key)
    {
        t->left = insertHelp(t->left, k, data, inserted);
        t->left->parent = t;
        if (t != root) {
            if (t->color && t->left->color)
                f = true;
        }
    } else {
        t->right = insertHelp(t->right, k, data, inserted);
        t->right->parent = t;
        if (t != root) {
            if (t->color && t->right->color)
                f = true;
        }
        // at the same time of insertion, we are also assigning parent nodes
        // also we are checking for RED RED conflicts
    }

    // now lets rotate.
    if (ll) {
        t = rotateLeft(t);
        t->color = false;
        t->left->color = true;
        ll = false;
    } else
        if(rr) // for right rotate
    {
        t = rotateRight(root);
        t->color = false;
        t->right->color = true;
        rr  = false;
    }
    else if(rl)  // for right and then left
    {
        t->right = rotateRight(t->right);
        t->right->parent = t;
        t = rotateLeft(t);
        t->color = false;
        t->left->color = true;

      rl = false;
    }
    else if(lr)  // for left and then right.
    {
        t->left = rotateLeft(t->left);
        t->left->parent = t;
        t = rotateRight(t);
        t->color = false;
        t->right->color = true;
        lr = false;
    }
    // when rotation and recolouring is done flags are reset.
    // Now lets take care of RED RED conflict
    if(f)
    {
        if(t->parent->right == t)  // to check which child is the current node of its parent
        {
            if(t->parent->left== nullptr || !t->parent->left->color)  // case when parent's sibling is black
            {// perform certaing rotation and recolouring. This will be done while backtracking. Hence setting up respective flags.
                if(t->left != nullptr && t->left->color)
                    rl = true;
                else if(t->right != nullptr && t->right->color)
                    ll = true;
            }
            else // case when parent's sibling is red
            {
                t->parent->left->color = false;
                t->color = false;
                if(t->parent!=root)
                    t->parent->color = true;
            }
        } else {
            if (t->parent->right == nullptr || !t->parent->right->color) {
                if (t->left != nullptr && t->left->color)
                    rr = true;
                else if(t->right != nullptr && t->right->color)
                    lr = true;
            } else {
                t->parent->right->color = false;
                t->color = false;
                if(t->parent != root)
                    t->parent->color = true;
            }
        }
        f = false;
    }
    return t;
}

template<typename T, typename K>
NodeRB<T, K>* rotateLeft(NodeRB<T, K>* node) {
    NodeRB<T, K>* x = node->right;
    NodeRB<T, K>* y = x->left;
    x->left = node;
    node->right = y;
    node->parent = x; // parent resetting is also important.
    if (y!= nullptr)
        y->parent = node;
    return(x);
}

template<typename T, typename K>
NodeRB<T, K>* rotateRight(NodeRB<T, K>*node) {
    NodeRB<T, K>* x = node->left;
    NodeRB<T, K>* y = x->right;
    x->right = node;
    node->left = y;
    node->parent = x;
    if(y!= nullptr)
        y->parent = node;
    return(x);
}

template<typename T, typename K>
void MyRB<T, K>::Delete(K k) {
    if (root == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }

    NodeRB<T, K> *v = Search(root, k);
    if (v != nullptr) deleteNode(v);
}

template<typename T, typename K>
NodeRB<T, K> *MyRB<T, K>::Search(NodeRB<T, K> *t, K k) {
    if (t == nullptr) {
        cout << "value with this key wasn't found" << endl;
        return t;
    }
    if (k == t->key) {
        NumOfViews++;
        return t;
    }
    NumOfViews++;
    if (k < t->key) {
        return Search(t->left, k);
    } else {
        return Search(t->right, k);
    }
}

template<typename T, typename K>
void MyRB<T, K>::swapColors(NodeRB<T, K> *x1, NodeRB<T, K> *x2) {
    bool temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
}

template<typename T, typename K>
void MyRB<T, K>::swapValues(NodeRB<T, K> *u, NodeRB<T, K> *v) {
    T temp;
    temp = u->value;
    u->value = v->value;
    v->value = temp;
}

template<typename T, typename K>
void MyRB<T, K>::fixRedRed(NodeRB<T, K> *x) {
    // if x is root color it black and return
    if (x == root) {
        x->color = false;
        return;
    }

    // initialize parent, grandparent, uncle
    NodeRB<T, K> *parent = x->parent, *grandparent = parent->parent,
            *uncle = x->uncle();

    if (parent->color != false) {
        if (uncle != nullptr && uncle->color == true) {
            // uncle red, perform recoloring and recurse
            parent->color = false;
            uncle->color = false;
            grandparent->color = true;
            fixRedRed(grandparent);
        } else {
            // Else perform LR, LL, RL, RR
            if (parent->isOnLeft()) {
                if (x->isOnLeft()) {
                    // for left right
                    swapColors(parent, grandparent);
                } else {
                    rotateLeft(parent);
                    swapColors(x, grandparent);
                }
                // for left left and left right
                rotateRight(grandparent);
            } else {
                if (x->isOnLeft()) {
                    // for right left
                    rotateRight(parent);
                    swapColors(x, grandparent);
                } else {
                    swapColors(parent, grandparent);
                }

                // for right right and right left
                rotateLeft(grandparent);
            }
        }
    }
}

template<typename T, typename K>
// find node that do not have a left child
// in the subtree of the given node
NodeRB<T, K> *MyRB<T, K>::successor(NodeRB<T, K> *x) {
    NodeRB<T, K> *temp = x;

    while (temp->left != nullptr)
        temp = temp->left;

    return temp;
}

template<typename T, typename K>
// find node that replaces a deleted node in BST
NodeRB<T, K> *MyRB<T, K>::BSTreplace(NodeRB<T, K> *x) {
    // when node have 2 children
    if (x->left != nullptr and x->right != nullptr)
        return successor(x->right);

    // when leaf
    if (x->left == nullptr and x->right == nullptr)
        return nullptr;

    // when single child
    if (x->left != nullptr)
        return x->left;
    else
        return x->right;
}

template<typename T, typename K>
// deletes the given node
void MyRB<T, K>::deleteNode(NodeRB<T, K> *v) {
    NodeRB<T, K> *u = BSTreplace(v);

    // True when u and v are both black
    bool uvBlack = ((u == nullptr or u->color == false) and (v->color == false));
    NodeRB<T, K> *parent = v->parent;

    if (u == nullptr) {
        // u is NULL therefore v is leaf
        if (v == root) {
            // v is root, making root null
            root = nullptr;
        } else {
            if (uvBlack) {
                // u and v both black
                // v is leaf, fix double black at v
                fixDoubleBlack(v);
            } else {
                // u or v is red
                if (v->sibling() != nullptr)
                    // sibling is not null, make it red"
                    v->sibling()->color = true;
            }

            // delete v from the tree
            if (v->isOnLeft()) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }
        delete v;
        return;
    }

    if (v->left == nullptr or v->right == nullptr) {
        // v has 1 child
        if (v == root) {
            // v is root, assign the value of u to v, and delete u
            v->value = u->value;
            v->left = v->right = nullptr;
            delete u;
        } else {
            // Detach v from tree and move u up
            if (v->isOnLeft()) {
                parent->left = u;
            } else {
                parent->right = u;
            }
            delete v;
            u->parent = parent;
            if (uvBlack) {
                // u and v both black, fix double black at u
                fixDoubleBlack(u);
            } else {
                // u or v red, color u black
                u->color = false;
            }
        }
        return;
    }

    // v has 2 children, swap values with successor and recurse
    swapValues(u, v);
    deleteNode(u);
}

template<typename T, typename K>
void MyRB<T, K>::fixDoubleBlack(NodeRB<T, K> *x) {
    if (x == root)
        // Reached root
        return;

    NodeRB<T, K> *sibling = x->sibling(), *parent = x->parent;
    if (sibling == nullptr) {
        // No sibiling, double black pushed up
        fixDoubleBlack(parent);
    } else {
        if (sibling->color == true) {
            // Sibling red
            parent->color = true;
            sibling->color = false;
            if (sibling->isOnLeft()) {
                // left case
                rotateRight(parent);
            } else {
                // right case
                rotateLeft(parent);
            }
            fixDoubleBlack(x);
        } else {
            // Sibling black
            if (sibling->hasRedChild()) {
                // at least 1 red children
                if (sibling->left != nullptr and sibling->left->color == true) {
                    if (sibling->isOnLeft()) {
                        // left left
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        rotateRight(parent);
                    } else {
                        // right left
                        sibling->left->color = parent->color;
                        rotateRight(sibling);
                        rotateLeft(parent);
                    }
                } else {
                    if (sibling->isOnLeft()) {
                        // left right
                        sibling->right->color = parent->color;
                        rotateLeft(sibling);
                        rotateRight(parent);
                    } else {
                        // right right
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        rotateLeft(parent);
                    }
                }
                parent->color = false;
            } else {
                // 2 black children
                sibling->color = true;
                if (parent->color == false)
                    fixDoubleBlack(parent);
                else
                    parent->color = false;
            }
        }
    }
}

template<typename T, typename K>
NodeRB<T, K>* MyRB<T, K>::GetRoot() { return root; }

template<typename T, typename K>
int MyRB<T, K>::GetSize() { return size; }

template<typename T, typename K>
void MyRB<T, K>::Clear(NodeRB<T,K>* t) {
    if (t == nullptr) return;
    Clear(t->left);
    Clear(t->right);
    delete t;
    NumOfViews++;
    size--;
    root = nullptr;
}

template<typename T, typename K>
MyRB<T, K>::MyRB(MyRB *a) { Copy(a->root); }

template<typename T, typename K>
void MyRB<T, K>::Copy(NodeRB<T, K> *t) {
    if (t == nullptr) return;
    Insert(t->key, t->value);
    Copy(t->left);
    Copy(t->right);
}

template<typename T, typename K>
bool MyRB<T, K>::ReplaceByKey(K k, T data) {
    NodeRB<T,K>* tt = Search(root, k);
    if (tt == nullptr) {
        return false;
    } else {
        tt->value = data;
        return true;
    }

}

template<typename T, typename K>
void MyRB<T, K>::t_L_R(NodeRB<T, K> *t, std::list<K> *list) {
    if (t == nullptr)
        return;
    list->push_back(t->key);
    NumOfViews++;
    t_L_R(t->left, list);
    t_L_R(t->right, list);
}

template<typename T, typename K>
void MyRB<T, K>::Show(NodeRB<T, K> *t, int level) {
    if (t == nullptr)
        return;
    Show(t->right, level + 1);
    for(int i = 0; i < 3*level; i++)
        cout << " ";
    cout << t->key << " ";
    if (t->color) cout << "red" << endl;
    else cout << "black" << endl;
    NumOfViews++;
    Show(t->left, level + 1);
}

template<typename T, typename K>
int MyRB<T, K>::GetNum() { return NumOfViews; }

template<typename T, typename K>
void MyRB<T, K>::SetNum() { NumOfViews = 0; }


