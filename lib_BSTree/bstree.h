#pragma once
#include <utility>   
#include <stdexcept>
#include <iostream>
#include <string>
#include <ostream>
#include "../lib_TreeUtils/tree_utils.h"



template<typename TKey, typename TValue>
struct Node : public BaseNode<TKey, TValue, Node<TKey, TValue>> {
    using Base = BaseNode<TKey, TValue, Node<TKey, TValue>>;
    using Base::Base; 
};
template<typename TKey, typename TValue>
class BSTree {
    Node<TKey, TValue>* _root;
    size_t _size;

public:
    BSTree() : _root(nullptr), _size(0) {}
    ~BSTree();

    Node<TKey, TValue>* get_root_ptr() const noexcept;
    bool is_empty() const noexcept;
    void clear() noexcept;
    void insert(const TKey& key, const TValue& value);
    void erase(const TKey& key);
    TValue* find(const TKey& key) const ;
    void print_dlcr() const noexcept;
    size_t BSTree<TKey, TValue>::size() const noexcept;


private:
    Node<TKey, TValue>* BSTree<TKey, TValue>::erase_recursive
    (Node<TKey, TValue>* node, const TKey& key, bool& found);
        void clear_rec(Node<TKey, TValue>* node) noexcept;
    void print_dlcr_rec(Node<TKey, TValue>* node) const noexcept;
    Node<TKey, TValue>* find_parent(const TKey& key) const noexcept;
    Node<TKey, TValue>* find_max(Node<TKey, TValue>* node);
};


template<typename TKey, typename TValue>
BSTree<TKey, TValue>::~BSTree() {
    clear();
}

template<typename TKey, typename TValue>
size_t BSTree<TKey, TValue>::size() const noexcept {
    return _size;
}
template<typename TKey, typename TValue>
bool BSTree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::clear() noexcept {
    clear_rec(_root);
    _root = nullptr;
    _size = 0;
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::clear_rec(Node<TKey, TValue>* node) noexcept {
    if (node == nullptr) return;

    clear_rec(node->_left);    
    clear_rec(node->_right);   
    delete node;
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
    if (is_empty()) {
        throw std::out_of_range("Cannot erase from empty tree");
    }

    bool found = false;
    _root = erase_recursive(_root, key, found);

    if (!found) {
        throw std::out_of_range("Key not found in tree");
    }
    --_size;
}

template<typename TKey, typename TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::erase_recursive(
    Node<TKey, TValue>* node, const TKey& key, bool& found) {

    if (!node) return nullptr;

    if (key < node->_data.first) {
        node->_left = erase_recursive(node->_left, key, found);
    }
    else if (key > node->_data.first) {
        node->_right = erase_recursive(node->_right, key, found);
    }
    else {
        found = true;  

        if (!node->_left) {
            Node<TKey, TValue>* right = node->_right;
            delete node;
            return right;
        }

        if (!node->_right) {
            Node<TKey, TValue>* left = node->_left;
            delete node;
            return left;
        }

        Node<TKey, TValue>* max_left = find_max(node->_left);

        node->_data = max_left->_data;
        node->_left = erase_recursive(node->_left, max_left->_data.first, found);
    }

    return node;
}

template<typename TKey, typename TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::find_max(Node<TKey, TValue>* node) {
    while (node && node->_right) {  
        node = node->_right;  
    }
    return node;
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    if (is_empty()) {
        _root = new Node<TKey, TValue>(key, value);
        ++_size;
        return;
    }

    Node<TKey, TValue>* cur = _root;
    Node<TKey, TValue>* parent = nullptr;

    while (cur) {
        parent = cur;
        if (key < cur->_data.first) {
            cur = cur->_left;
        }
        else if (key > cur->_data.first) {
            cur = cur->_right;
        }
        else {
            throw std::logic_error("Key already exists");
        }
    }

    if (key < parent->_data.first) {
        parent->_left = new Node<TKey, TValue>(key, value);
    }
    else {
        parent->_right = new Node<TKey, TValue>(key, value);
    }
    ++_size;
}
template <class TKey, class TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::get_root_ptr() const noexcept {
    return _root;
}


template<typename TKey, typename TValue>
TValue* BSTree<TKey, TValue>::find(const TKey& key) const {
    if (is_empty()) {
        throw std::out_of_range("Tree is empty");
    }

    Node<TKey, TValue>* cur = _root;
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

template<typename TKey, typename TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
    if (is_empty() || _root->_data.first == key) { 
        return nullptr;
    }

    Node<TKey, TValue>* cur = _root;
    while (cur != nullptr) {
        if (key < cur->_data.first) {  
            if (cur->_left == nullptr || cur->_left->_data.first == key) { 
                return cur;
            }
            cur = cur->_left;  
        }
        else {
            if (cur->_right == nullptr || cur->_right->_data.first == key) {  
                return cur;
            }
            cur = cur->_right;  
        }
    }
    return nullptr;
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::print_dlcr() const noexcept {
    if (_root == nullptr) {
        std::cout << " --- Empty --- \n";
        return;
    }

    print_dlcr_rec(_root);
    std::cout << "\n";
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::print_dlcr_rec(Node<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_dlcr_rec(node->_left);  
    std::cout << "(" << node->_data.first << ", " << node->_data.second << ") "; 
    print_dlcr_rec(node->_right);  
}