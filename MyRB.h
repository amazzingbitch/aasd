
#ifndef UNTITLED11_MYRB_H
#define UNTITLED11_MYRB_H
#include <iostream>
#include "NodeRB.h"

using std::cout;
using std::endl;


template <typename T, typename K>
class MyRB {
public:
    MyRB();
    explicit MyRB(MyRB* a);
    ~MyRB();
    int GetSize();
    void Clear(NodeRB<T,K>* t);
    bool IsEmpty();
    bool* Insert(K k, T data);
    NodeRB<T,K>* insertHelp(NodeRB<T,K>* t, K k, T data, bool* inserted);
    void t_L_R(NodeRB<T, K> *t, std::list<K> *list);
    NodeRB<T,K>* GetRoot();
    void Copy(NodeRB<T,K>* t);
    NodeRB<T,K>* Search(NodeRB<T,K>* t, K k);
    bool ReplaceByKey(K k, T data);
    void Delete(K k);
    void Show(NodeRB<T, K> *t, int level);
    int GetNum();
    void SetNum();
    void swapColors(NodeRB<T, K> *x1, NodeRB<T, K> *x2);
    void swapValues(NodeRB<T, K> *u, NodeRB<T, K> *v);
    void fixRedRed(NodeRB<T, K> *x);
    NodeRB<T, K> *successor(NodeRB<T, K> *x);
    NodeRB<T, K> *BSTreplace(NodeRB<T, K> *x);
    void deleteNode(NodeRB<T, K> *v);
    void fixDoubleBlack(NodeRB<T, K> *x);
    NodeRB<T, K> *rotateLeft(NodeRB<T, K> *node);
    NodeRB<T, K> *rotateRight(NodeRB<T, K> *node);

    class Iterator {
        MyRB* p;
        NodeRB<T,K>* cur;
    public:
        explicit Iterator(NodeRB<T,K>* cur_, MyRB* p_): cur(cur_), p(p_) {};
        T& operator* () { return cur->value; }
        Iterator& operator++() { if (cur->right != nullptr) cur = cur->right; return *this; }
        Iterator& operator--() { cur = cur->parent; return *this; }
        bool operator==(const Iterator& it) { return cur == it.cur; }
        bool operator!=(const Iterator& it) { return cur != it.cur; }
    };

    class ReverseIterator {
        MyRB* p;
        NodeRB<T,K>* cur;
    public:
        ReverseIterator(NodeRB<T,K>* cur_, MyRB* p_): cur(cur_), p(p_) {};
        T& operator* () { return cur->value; }
        ReverseIterator& operator++() { cur = cur->parent; return *this; }
        ReverseIterator& operator--() { if (cur->right != nullptr) cur = cur->right; return *this; }
        bool operator==(const ReverseIterator& it) { return cur == it.cur; }
        bool operator!=(const ReverseIterator& it) { return cur != it.cur; }
    };

    Iterator begin() {
        NodeRB<T,K>* t = root;
        while (t->left != nullptr) t = t->left;
        return Iterator(t, this);
    }
    Iterator end() {
        NodeRB<T,K>* t = root;
        while (t->right != nullptr) t = t->right;
        return Iterator(t, this);
    }

    ReverseIterator rbegin() {
        NodeRB<T,K>* t = root;
        while (t->right != nullptr) t = t->right;
        return ReverseIterator(t, this);
    }
    ReverseIterator rend() {
        NodeRB<T,K>* t = root;
        while (t->left != nullptr) t = t->left;
        return ReverseIterator(t, this);
    }

private:
    int size = 0;
    NodeRB<T,K>* root;
    int NumOfViews = 0;
    bool ll = false;
    bool rr = false;
    bool lr = false;
    bool rl = false;

    void leftRotate(NodeRB<T, K> *x);

    void rightRotate(NodeRB<T, K> *x);
};


template
class MyRB<int, int>;
typedef unsigned long long INT_64;
template
class MyRB<INT_64, int>;

#endif //UNTITLED11_MYRB_H
