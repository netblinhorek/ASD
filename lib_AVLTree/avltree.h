#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <utility>
#include "../lib_BaseBSTree/base_bstree.h"

template <class TKey, class TValue>
struct AVLNode {
    AVLNode<TKey, TValue>* _left;
    AVLNode<TKey, TValue>* _right;
    AVLNode<TKey, TValue>* _parent;
    std::pair<TKey, TValue> _data;
    size_t _height;

    AVLNode(const TKey& key, const TValue& value)
        : _left(nullptr), _right(nullptr), _parent(nullptr),
        _data(key, value), _height(1) {}
};


template <class TKey, class TValue>
class AVLTree : public BaseBSTree<TKey, TValue, AVLNode<TKey, TValue>> {
    using Node = AVLNode<TKey, TValue>;
public:
    AVLTree();
    void insert(const TKey& key, const TValue& value);
    void erase(const TKey& key);
    
private:
    size_t get_height(AVLNode<TKey, TValue>* node) const noexcept;
    int calc_balance(AVLNode<TKey, TValue>* node) const noexcept;
    void recalc_height(AVLNode<TKey, TValue>* node) noexcept;
    AVLNode<TKey, TValue>* left_rotate_avl(AVLNode<TKey, TValue>* G) noexcept;
    AVLNode<TKey, TValue>* right_rotate_avl(AVLNode<TKey, TValue>* G) noexcept;

    AVLNode<TKey, TValue>* LL(AVLNode<TKey, TValue>* node) noexcept;
    AVLNode<TKey, TValue>* RL(AVLNode<TKey, TValue>* node) noexcept;
    AVLNode<TKey, TValue>* LR(AVLNode<TKey, TValue>* node) noexcept;
    AVLNode<TKey, TValue>* RR(AVLNode<TKey, TValue>* node) noexcept;
    AVLNode<TKey, TValue>* recovery_balance(AVLNode<TKey, TValue>* node) noexcept;
protected:
    AVLNode<TKey, TValue>* post_erase_action(AVLNode<TKey, TValue>* node) override;
};

template <class TKey, class TValue>
size_t AVLTree<TKey, TValue>::get_height(AVLNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) {
        return 0;
    }
    return node->_height;
}

template <class TKey, class TValue>
int AVLTree<TKey, TValue>::calc_balance(AVLNode<TKey, TValue>* node) const noexcept {
    if (node == nullptr) {
        return 0;
    }
    int left_h = get_height(node->_left);
    int right_h = get_height(node->_right);

    return left_h - right_h;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::recalc_height(AVLNode<TKey, TValue>* node) noexcept {
    if (node == nullptr) {
        return;
    }
    size_t left_h = get_height(node->_left);
    size_t right_h = get_height(node->_right);
    if (left_h > right_h) {
        node->_height = left_h + 1;
    }
    else {
        node->_height = right_h + 1;
    }
}
template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::left_rotate_avl(AVLNode<TKey, TValue>* G) noexcept {
    Node* P = G->_right;
    this->left_rotate(G);
    recalc_height(G);
    recalc_height(P);
    return P;
}
template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::right_rotate_avl(AVLNode<TKey, TValue>* G) noexcept {
    Node* P = G->_left;
    this->right_rotate(G); 
    recalc_height(G);
    recalc_height(P);
    return P;
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::LL(AVLNode<TKey, TValue>* node) noexcept {
    return right_rotate_avl(node);
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::RR(AVLNode<TKey, TValue>* node) noexcept {
    return left_rotate_avl(node);
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::LR(AVLNode<TKey, TValue>* node) noexcept {
    node->_left = left_rotate_avl(node->_left);
    return right_rotate_avl(node);
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::RL(AVLNode<TKey, TValue>* node) noexcept {
    node->_right = right_rotate_avl(node->_right);
    return left_rotate_avl(node);
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::recovery_balance(AVLNode<TKey, TValue>* node) noexcept {
    int balance = calc_balance(node);
    if (balance > 1) {
        if (calc_balance(node->_left) >= 0) {
            return LL(node);
        }
        else {
            return LR(node); 
        }
    }
    else if (balance < -1) {
        if (calc_balance(node->_right) <= 0) {
            return RR(node); 
        }
        else {
            return RL(node); 
        }
    }
    return node; 
}
template <class TKey, class TValue>
AVLTree<TKey, TValue>::AVLTree() : BaseBSTree<TKey, TValue,
    AVLNode<TKey, TValue>>() {}


template <class TKey, class TValue>
void AVLTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    AVLNode<TKey, TValue>* inserted_node = this->insert_node(key, value);
    if (inserted_node == this->_root) {
        return;
    }

    AVLNode<TKey, TValue>* temp = inserted_node->_parent;
    while (temp != nullptr) {
        recalc_height(temp);
        if (std::abs(calc_balance(temp)) > 1) {
            recovery_balance(temp);
        }
        temp = temp->_parent; 
    }
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::post_erase_action(AVLNode<TKey, TValue>* node) {
    if (!node) 
        return nullptr;
    this->recalc_height(node);
    return this->recovery_balance(node);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::erase(const TKey& key) {
    bool found = false;
    this->_root = this->erase_recursive(this->_root, key, found);
    if (!found) 
        throw std::out_of_range("Key not found");
    this->_size--;
    if (this->_root) 
        this->_root->_parent = nullptr;
}




