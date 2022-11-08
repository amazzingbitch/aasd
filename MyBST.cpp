//
// Created by Eldo on 07.11.2022.
//

#include <list>
#include "MyBST.h"

template<typename T, typename K>
MyBST<T, K>::MyBST() {
    size = 0;
    root = nullptr;
}

template<typename T, typename K>
bool MyBST<T, K>::IsEmpty() {
    return root == nullptr;
}

template<typename T, typename K>
MyBST<T, K>::~MyBST() {
    Clear(root);
}

template<typename T, typename K>
NodeBST<T, K>* MyBST<T, K>::Insert(NodeBST<T, K>* t, K k, T data, bool* inserted) {
    if (t == nullptr) {
        *inserted = true;
        t = new NodeBST<T,K>(data, k);
        if (root == nullptr) root = t;
        size++;
        return t;
    }
    if (k == t->key) {
        *inserted = false;
        NumOfViews++;
        return t;
    }
    bool* ins = new bool;
    if (k < t->key) {
        t->left = Insert(t->left, k, data, ins);
        inserted = ins;
        NumOfViews++;
        return t;
    } else {
        t->right = Insert(t->right, k, data, ins);
        inserted = ins;
        NumOfViews++;
        return t;
    }
}

template<typename T, typename K>
NodeBST<T, K>* MyBST<T, K>::GetRoot() {
    return root;
}

template<typename T, typename K>
int MyBST<T, K>::GetSize() {
    return size;
}

template<typename T, typename K>
void MyBST<T, K>::Clear(NodeBST<T,K>* t) {
    if (t == nullptr) return;
    Clear(t->left);
    Clear(t->right);
    delete t;
    NumOfViews++;
    size--;
    root = nullptr;
}

template<typename T, typename K>
MyBST<T, K>::MyBST(MyBST *a) {
    Copy(a->root);
}

template<typename T, typename K>
void MyBST<T, K>::Copy(NodeBST<T, K> *t) {
    bool* ins = new bool;
    if (t == nullptr) return;
    Insert(root, t->key, t->value, ins);
    Copy(t->left);
    Copy(t->right);
}

template<typename T, typename K>
NodeBST<T, K> *MyBST<T, K>::Search(NodeBST<T, K> *t, K k) {
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
bool MyBST<T, K>::ReplaceByKey(K k, T data) {
    NodeBST<T,K>* tt = Search(root, k);
    if (tt == nullptr) {
        return false;
    } else {
        tt->value = data;
        return true;
    }

}

template<typename T, typename K>
void MyBST<T, K>::t_L_R(NodeBST<T, K> *t, std::list<K> *list) {
    if (t == nullptr)
        return;
    list->push_back(t->key);
    NumOfViews++;
    t_L_R(t->left, list);
    t_L_R(t->right, list);
}

template<typename T, typename K>
NodeBST<T, K> *MyBST<T, K>::Delete(NodeBST<T, K> *t, K k, bool *deleted) {
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
    NodeBST<T,K>* x;
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
NodeBST<T, K> *MyBST<T, K>::Del(NodeBST<T, K> *t, NodeBST<T, K> *t0, bool* deleted) {
    if (t->left != nullptr) {
        t->left = Del(t->left, t0, deleted);
        return t;
    }
    t0->key = t->key;
    t0->value = t->value;
    NodeBST<T,K>* x = t->right;
    delete t;
    NumOfViews++;
    size--;
    *deleted = true;
    return x;
}

template<typename T, typename K>
void MyBST<T, K>::Show(NodeBST<T, K> *t, int level) {
    if (t == nullptr)
        return;
    Show(t->right, level + 1);
    for(int i = 0; i < 3*level; i++)
        cout << " ";
    cout << t->key << " " << t->value << endl;
    NumOfViews++;
    Show(t->left, level + 1);
}

template<typename T, typename K>
int MyBST<T, K>::Height(NodeBST<T, K> *t) {
    if (t == nullptr) return 0;
    NumOfViews++;
    return 1 + std::max(Height(t->left), Height(t->right));
}

template<typename T, typename K>
int MyBST<T, K>::GetNum() {
    return NumOfViews;
}

template<typename T, typename K>
void MyBST<T, K>::SetNum() {
    NumOfViews = 0;
}

template<typename T, typename K>
NodeBST<T, K> *MyBST<T, K>::Pre(NodeBST<T, K> *t) {
    if (t->left != nullptr) return Max(t->left);
    else return R_Parent(root, t);
}

template<typename T, typename K>
NodeBST<T, K> *MyBST<T, K>::Max(NodeBST<T, K> *t) {
    if (t == nullptr) return nullptr;
    while (t->right != nullptr) t = t->right;
    return t;
}

template<typename T, typename K>
NodeBST<T, K> *MyBST<T, K>::R_Parent(NodeBST<T, K> *t, NodeBST<T, K> *x) {
    if (t == x) return nullptr;
    NodeBST<T,K>* rp = nullptr;
    if (x->key > t->key) {
        rp = R_Parent(t->right, x);
        if (rp != nullptr) return rp;
        else return t;
    } else {
        return R_Parent(t->left, x);
    }
}



