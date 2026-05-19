#pragma once
#define UNSORTED_ON_BSTree_H

#include <iostream>   
#include <iomanip>
#include <stdexcept>

template<typename TKey, typename TValue, typename TNode>
class BaseBSTree {
protected:
    TNode* _root;
    size_t _size;

    void clear_rec(TNode* node) noexcept {
        if (node == nullptr) return;
        clear_rec(node->_left);
        clear_rec(node->_right);
        delete node;
    }
    TNode* insert_node(const TKey& key, const TValue& value) {
        if (is_empty()) {
            _root = new TNode(key, value);
            _size = 1;
            return _root;
        }

        TNode* cur = _root;
        TNode* parent = nullptr;

        while (cur != nullptr) {
            parent = cur;
            if (key < cur->_data.first) {
                cur = cur->_left;
            }
            else if (key > cur->_data.first) {
                cur = cur->_right;
            }
            else {
                throw std::logic_error("Key already exists in the tree.");
            }
        }

        TNode* new_node = new TNode(key, value);
        new_node->_parent = parent; 

        if (key < parent->_data.first) {
            parent->_left = new_node;
        }
        else {
            parent->_right = new_node;
        }
        _size++;

        return new_node;
    }

    virtual TNode* post_erase_action(TNode* node) {
        return node;
    }

    virtual TNode* erase_recursive(TNode* node, const TKey& key, bool& found) {
        if (!node) return nullptr;

        if (key < node->_data.first) {
            node->_left = erase_recursive(node->_left, key, found);
            if (node->_left) node->_left->_parent = node;
        }
        else if (key > node->_data.first) {
            node->_right = erase_recursive(node->_right, key, found);
            if (node->_right) node->_right->_parent = node;
        }
        else {
            found = true;
            if (node->_left == nullptr) {
                TNode* right = node->_right;
                if (right) right->_parent = node->_parent;
                delete node;
                return right; 
            }
            if (node->_right == nullptr) {
                TNode* left = node->_left;
                if (left) left->_parent = node->_parent;
                delete node;
                return left; 
            }

            TNode* max_left = find_max(node->_left);
            node->_data = max_left->_data;
            node->_left = erase_recursive(node->_left, max_left->_data.first, found);
            if (node->_left) node->_left->_parent = node;
        }
        return post_erase_action(node);
    }

    TNode* find_max(TNode* node) const noexcept {
        while (node && node->_right) {
            node = node->_right;
        }
        return node;
    }

    void print_dlcr_rec(TNode* node) const noexcept {
        if (node == nullptr) return;
        print_dlcr_rec(node->_left);
        std::cout << node->_data.first << node->_data.second ;
        print_dlcr_rec(node->_right);
    }


    void left_rotate(TNode* G) noexcept {
        TNode* P = G->_right;
        G->_right = P->_left;
        if (P->_left) P->_left->_parent = G;
        P->_parent = G->_parent;
        if (!G->_parent) this->_root = P;
        else if (G == G->_parent->_left) G->_parent->_left = P;
        else G->_parent->_right = P;
        P->_left = G;
        G->_parent = P;
    }

    void right_rotate(TNode* G) noexcept {
        TNode* P = G->_left;
        G->_left = P->_right;
        if (P->_right) P->_right->_parent = G;
        P->_parent = G->_parent;
        if (!G->_parent) this->_root = P;
        else if (G == G->_parent->_left) G->_parent->_left = P;
        else G->_parent->_right = P;
        P->_right = G;
        G->_parent = P;
    }

    void LL(TNode* node) noexcept { right_rotate(node); }
    void RR(TNode* node) noexcept { left_rotate(node); }
    void LR(TNode* node) noexcept { left_rotate(node->_left); right_rotate(node); }
    void RL(TNode* node) noexcept { right_rotate(node->_right); left_rotate(node); }

public:
    BaseBSTree() : _root(nullptr), _size(0) {}
    ~BaseBSTree() { clear(); }
    TNode* get_root_ptr() const noexcept { return _root; }
    bool is_empty() const noexcept { return _root == nullptr; }
    size_t size() const noexcept { return _size; }

    void clear() noexcept {
        clear_rec(_root);
        _root = nullptr;
        _size = 0;
    }

    TValue* find(const TKey& key) const {
        if (is_empty()) {
            throw std::out_of_range("Tree is empty");
        }

        TNode* cur = _root;
        while (cur != nullptr) {
            if (key == cur->_data.first) {
                return &cur->_data.second;
            }
            else if (key < cur->_data.first) {
                cur = cur->_left;
            }
            else {
                cur = cur->_right;
            }
        }
        throw std::out_of_range("Key not found in tree");
    }

    void print_dlcr() const noexcept {
        if (_root == nullptr) {
            std::cout << " --- Empty --- \n";
            return;
        }
        print_dlcr_rec(_root);
        std::cout << "\n";
    }

   
};