//
// Created by Eldo on 07.11.2022.
//

#include <list>
#include "MyRB.h"

template<typename T, typename K>
MyRB<T, K>::MyRB() {
    size = 0;
    root = nullptr;
}

template<typename T, typename K>
bool MyRB<T, K>::IsEmpty() {
    return root == nullptr;
}

template<typename T, typename K>
MyRB<T, K>::~MyRB() {
    Clear(root);
}

template<typename T, typename K>
bool* MyRB<T, K>::Insert(NodeRB<T, K>* t, K k, T data) {
    bool* ins = new bool;
    *ins = false;
    t = Insert1(t, k, data, 0, ins, nullptr);
    t->color = false;
    return ins;
}

template<typename T, typename K>
NodeRB<T, K>* MyRB<T, K>::Insert1(NodeRB<T, K>* t, K k, T data, int s, bool* inserted, NodeRB<T, K>* p) {
    if (t == nullptr) {
        t = new NodeRB<T,K>(data, k);
        if (root == nullptr) { root = t ; }
        t->parent = p;
        t->color = true;
        *inserted = true;
        size++;
        /*Show(GetRoot(), 0);
        cout << endl;*/
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
    }
}

template<typename T, typename K>
NodeRB<T, K>* MyRB<T, K>::R(NodeRB<T, K>* t) {
    NodeRB<T, K>* parent = t->parent;
    NodeRB<T, K>* leftChild = t->left;

    t->left = leftChild->right;
    if (leftChild->right != nullptr) {
        leftChild->right->parent = t;
    }

    leftChild->right = t;
    t->parent = leftChild;

    replaceParentsChild(parent, t, leftChild);
    return t;
}

template<typename T, typename K>
void MyRB<T, K>::replaceParentsChild(NodeRB<T, K>* parent, NodeRB<T, K>* oldChild, NodeRB<T, K>* newChild) {
    if (parent == nullptr) {
        root = newChild;
    } else if (parent->left == oldChild) {
        parent->left = newChild;
    } else if (parent->right == oldChild) {
        parent->right = newChild;
    } else {
        cout << "Node is not a child of its parent" << endl;
    }
    if (newChild != nullptr) {
        newChild->parent = parent;
    }
}

template<typename T, typename K>
NodeRB<T, K>* MyRB<T, K>::L(NodeRB<T, K>* t) {
    NodeRB<T, K>* parent = t->parent;
    NodeRB<T, K>* rightChild = t->right;

    t->right = rightChild->left;
    if (rightChild->left != nullptr) {
        rightChild->left->parent = t;
    }

    rightChild->left = t;
    t->parent = rightChild;

    replaceParentsChild(parent, t, rightChild);

    return t;
}

template<typename T, typename K>
NodeRB<T, K>* MyRB<T, K>::GetRoot() {
    return root;
}

template<typename T, typename K>
int MyRB<T, K>::GetSize() {
    return size;
}

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
MyRB<T, K>::MyRB(MyRB *a) {
    Copy(a->root);
}

template<typename T, typename K>
void MyRB<T, K>::Copy(NodeRB<T, K> *t) {
    if (t == nullptr) return;
    Insert(root, t->key, t->value);
    Copy(t->left);
    Copy(t->right);
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
NodeRB<T, K> *MyRB<T, K>::Delete(NodeRB<T, K> *t, K k, bool *deleted) {
    if (t == nullptr) {
        *deleted = false;
        return t;
    }
    if (k < t->key) {
        t->left = Delete(t->left, k, deleted);
        NumOfViews++;
        return t;
    }
    if (k > t->key) {
        t->right = Delete(t->right, k, deleted);
        NumOfViews++;
        return t;
    }
    *deleted = true;
    if (t->left == nullptr && t->right == nullptr) {
        delete t;
        size--;
        NumOfViews++;
        *deleted = true;
        return nullptr;
    }
    NodeRB<T,K>* x;
    if (t->left == nullptr) {
        x = t->right;
        size--;
        delete t;
        *deleted = true;
        return x;
    }
    if (t->right == nullptr) {
        x = t->left;
        delete t;
        size--;
        *deleted = true;
        return x;
    }
    t->right = Del(t->right, t, deleted);
    return t;
}

template<typename T, typename K>
NodeRB<T, K> *MyRB<T, K>::Del(NodeRB<T, K> *t, NodeRB<T, K> *t0, bool* deleted) {
    if (t->left != nullptr) {
        t->left = Del(t->left, t0, deleted);
        return t;
    }
    t0->key = t->key;
    t0->value = t->value;
    NodeRB<T,K>* x = t->right;
    delete t;
    NumOfViews++;
    size--;
    *deleted = true;
    return x;
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
int MyRB<T, K>::GetNum() {
    return NumOfViews;
}

template<typename T, typename K>
void MyRB<T, K>::SetNum() {
    NumOfViews = 0;
}



