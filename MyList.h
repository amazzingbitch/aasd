//
// Created by 1 on 14.09.2022.
//

#ifndef ALG_LAB1_MYLIST_H
#define ALG_LAB1_MYLIST_H

#include <iostream>
using std::cout;
using std::endl;
template <typename T>

class MyList {

public:

    MyList();
    MyList(MyList* a);
    ~MyList();
    int GetSize();
    void Clean();
    bool IsEmpty();
    bool IsThere(T value);
    T FindValue(int k);
    bool ChangeValue(int k, T value);
    int FindPos(T value);
    void AddValue(T value);
    bool AddValueToPos(int k, T value);
    T DeleteValue(T value);
    T DeletePos(int k);
    int ShowNumOfViews();
    void PrintList();
    void PrintListReverse();
    void PrintListIt();
    void PrintListReverseIt();

protected:

    class Node {
    public:
        T item;
        Node *next;
        Node *prev;
        Node(): item(0), next(nullptr), prev (nullptr) {}
        explicit Node(T value): item(value), next(nullptr), prev (nullptr) {}
        ~Node() = default;
    };


    class Iterator {
        MyList* p;
        Node* cur;
    public:
        explicit Iterator(Node* cur_, MyList* p_): cur(cur_), p(p_) {};
        T& operator* () { return cur->item; }
        Iterator& operator++() { /*if (cur->next != p->head)*/ cur = cur->next; return *this; }
        Iterator& operator--() { /*if (cur->prev != p->head->prev)*/ cur = cur->prev; return *this; }
        bool operator==(const Iterator& it) { return cur == it.cur; }
        bool operator!=(const Iterator& it) { return cur != it.cur; }
    };


    class ReverseIterator {
        MyList* p;
        Node* cur;
    public:
        ReverseIterator(Node* cur_, MyList* p_): cur(cur_), p(p_) {};
        T& operator* () { return cur->item; }
        ReverseIterator& operator++() { /*if (cur->prev != p->head->prev)*/ cur = cur->prev; return *this; }
        ReverseIterator& operator--() { /*if (cur->next != p->head)*/ cur = cur->next; return *this; }
        bool operator==(const ReverseIterator& it) { return cur == it.cur; }
        bool operator!=(const ReverseIterator& it) { return cur != it.cur; }
    };


    friend class Iterator;
    friend class ReverseIterator;

    Iterator begin() {
        return Iterator(head, this);
    }
    Iterator end() {
        return Iterator(head, this);
    }

    ReverseIterator rbegin() {
        return ReverseIterator(head->prev, this);
    }
    ReverseIterator rend() {
        return ReverseIterator(head->prev, this);
    }


private:

    int NumOfViews = 0;
    int size = 0;
    Node* head;

};

template
class MyList<int>;

#endif //ALG_LAB1_MYLIST_H
