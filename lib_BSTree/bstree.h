#pragma once
#include <utility>   
#include <stdexcept>
#include <iostream>
#include <string>
#include <ostream>
#include "../lib_TreeUtils/tree_utils.h"
#include "../lib_BaseBSTree/base_bstree.h"


template<typename TKey, typename TValue>
struct Node : public BaseNode<TKey, TValue, Node<TKey, TValue>> {
    using Base = BaseNode<TKey, TValue, Node<TKey, TValue>>;
    using Base::Base; 
};
template<typename TKey, typename TValue>
class BSTree : public BaseBSTree<TKey, TValue, Node<TKey, TValue>> {
   

public:
    BSTree() : BaseBSTree<TKey, TValue, Node<TKey, TValue>>() {}

    void insert(const TKey& key, const TValue& value);
    void erase(const TKey& key);
    

private:
    Node<TKey, TValue>* find_parent(const TKey& key) const noexcept;
};


template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
    bool found = false;
    this->_root = this->erase_recursive(this->_root, key, found);
    if (!found) throw std::out_of_range("Key not found");
    this->_size--;
}

template<typename TKey, typename TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    this->insert_node(key, value);
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
