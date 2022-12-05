
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
    bool* Insert(NodeRB<T,K>* t, K k, T data);
    NodeRB<T,K>* Insert1(NodeRB<T,K>* t, K k, T data, int s, bool* inserted);
    NodeRB<T, K>* L(NodeRB<T, K>* t);
    NodeRB<T, K>* R(NodeRB<T, K>* t);
    void replaceParentsChild(NodeRB<T, K> *parent, NodeRB<T, K> *oldChild, NodeRB<T, K> *newChild);
    void t_L_R(NodeRB<T, K> *t, std::list<K> *list);
    NodeRB<T,K>* GetRoot();
    void Copy(NodeRB<T,K>* t);
    NodeRB<T,K>* Search(NodeRB<T,K>* t, K k);
    bool ReplaceByKey(K k, T data);
    NodeRB<T,K>* Delete(NodeRB<T,K>* t, K k, bool* deleted);
    NodeRB<T,K>* Del(NodeRB<T,K>* t, NodeRB<T,K>* t0, bool* deleted);
    void Show(NodeRB<T, K> *t, int level);
    int GetNum();
    void SetNum();

    /*class Iterator {
        MyRB* p;
        NodeRB<T,K>* cur;
    public:
        explicit Iterator(NodeRB<T,K>* cur_, MyRB* p_): cur(cur_), p(p_) {};
        T& operator* () { return cur->value; }
        Iterator& operator++() { if (cur->right != nullptr) cur = cur->right; return *this; }
        Iterator& operator--() { cur = p->Pre(cur); return *this; }
        bool operator==(const Iterator& it) { return cur == it.cur; }
        bool operator!=(const Iterator& it) { return cur != it.cur; }
    };

    class ReverseIterator {
        MyRB* p;
        NodeRB<T,K>* cur;
    public:
        ReverseIterator(NodeRB<T,K>* cur_, MyRB* p_): cur(cur_), p(p_) {};
        T& operator* () { return cur->value; }
        ReverseIterator& operator++() { cur = p->Pre(cur); return *this; }
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
    }*/

private:
    int size = 0;
    NodeRB<T,K>* root;
    int NumOfViews = 0;


};


template
class MyRB<int, int>;
typedef unsigned long long INT_64;
template
class MyRB<INT_64, int>;

#endif //UNTITLED11_MYRB_H
