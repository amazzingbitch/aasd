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
    bool color = false; // black
};


#endif //UNTITLED11_NODERB_H
