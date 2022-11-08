
#ifndef UNTITLED11_MYBST_H
#define UNTITLED11_MYBST_H
#include <iostream>
#include "NodeBST.h"

using std::cout;
using std::endl;


template <typename T, typename K>
class MyBST {
public:
    MyBST();
    explicit MyBST(MyBST* a);
    ~MyBST();
    int GetSize();
    void Clear(NodeBST<T,K>* t);
    bool IsEmpty();
    NodeBST<T,K>* Insert(NodeBST<T,K>* t, K k, T data, bool* inserted);
    void t_L_R(NodeBST<T, K> *t, std::list<K> *list);
    NodeBST<T,K>* GetRoot();
    void Copy(NodeBST<T,K>* t);
    NodeBST<T,K>* Search(NodeBST<T,K>* t, K k);
    bool ReplaceByKey(K k, T data);
    NodeBST<T,K>* Delete(NodeBST<T,K>* t, K k, bool* deleted);
    NodeBST<T,K>* Del(NodeBST<T,K>* t, NodeBST<T,K>* t0, bool* deleted);
    void Show(NodeBST<T, K> *t, int level);
    int Height(NodeBST<T, K> *t);
    int GetNum();
    void SetNum();
    NodeBST<T,K>* Pre(NodeBST<T,K>* t);
    NodeBST<T,K>* Max(NodeBST<T,K>* t);
    NodeBST<T,K>* R_Parent(NodeBST<T,K>* t, NodeBST<T,K>* x);

    class Iterator {
        MyBST* p;
        NodeBST<T,K>* cur;
    public:
        explicit Iterator(NodeBST<T,K>* cur_, MyBST* p_): cur(cur_), p(p_) {};
        T& operator* () { return cur->value; }
        Iterator& operator++() { if (cur->right != nullptr) cur = cur->right; return *this; }
        Iterator& operator--() { cur = p->Pre(cur); return *this; }
        bool operator==(const Iterator& it) { return cur == it.cur; }
        bool operator!=(const Iterator& it) { return cur != it.cur; }
    };

    class ReverseIterator {
        MyBST* p;
        NodeBST<T,K>* cur;
    public:
        ReverseIterator(NodeBST<T,K>* cur_, MyBST* p_): cur(cur_), p(p_) {};
        T& operator* () { return cur->value; }
        ReverseIterator& operator++() { cur = p->Pre(cur); return *this; }
        ReverseIterator& operator--() { if (cur->right != nullptr) cur = cur->right; return *this; }
        bool operator==(const ReverseIterator& it) { return cur == it.cur; }
        bool operator!=(const ReverseIterator& it) { return cur != it.cur; }
    };

    Iterator begin() {
        NodeBST<T,K>* t = root;
        while (t->left != nullptr) t = t->left;
        return Iterator(t, this);
    }
    Iterator end() {
        NodeBST<T,K>* t = root;
        while (t->right != nullptr) t = t->right;
        return Iterator(t, this);
    }

    ReverseIterator rbegin() {
        NodeBST<T,K>* t = root;
        while (t->right != nullptr) t = t->right;
        return ReverseIterator(t, this);
    }
    ReverseIterator rend() {
        NodeBST<T,K>* t = root;
        while (t->left != nullptr) t = t->left;
        return ReverseIterator(t, this);
    }

private:
    int size = 0;
    NodeBST<T,K>* root;
    int NumOfViews = 0;
};


template
class MyBST<int, int>;
typedef unsigned long long INT_64;
template
class MyBST<INT_64, int>;

#endif //UNTITLED11_MYBST_H
