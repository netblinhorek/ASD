#pragma once
#include "../lib_Queue/queue.h"
#include "../lib_TreeUtils/tree_utils.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <windows.h>

template <class TKey, class TValue>
struct Node : public BaseNode<TKey, TValue, Node<TKey, TValue>> {
    using Base = BaseNode<TKey, TValue, Node<TKey, TValue>>;
    using Base::Base;
    Node() : Base(TKey(), TValue()) {}
    ~Node() = default;
};

template <class TKey, class TValue>
class Tree {
protected:
    Node<TKey, TValue>* _root;
    void set_root_ptr(Node<TKey, TValue>* node) noexcept { _root = node; }

public:
    Tree();
    ~Tree();

    Node<TKey, TValue>* get_root_ptr() const noexcept;
    void insert(const TKey& key, const TValue& value);
    void erase(const TKey& key);
    Node<TKey, TValue>* find(const TKey& key) const;
    bool is_empty() const noexcept;
    void clear() noexcept;

    void print_w() const noexcept;
    void print_dlcr() const noexcept;
    void print_dlrc() const noexcept;
    void print_dclr() const noexcept;

private:
    void delete_node(Node<TKey, TValue>* parent, Node<TKey, TValue>* node);

    void print_prefix(std::ostream& os, const std::string& prefix, int depth,
        bool is_left, const char* left_symbol, const char* right_symbol) const noexcept;

    void print_dlcr_rec(Node<TKey, TValue>* node, int depth, bool is_left,
        const std::string& prefix) const noexcept;
    void print_dlrc_rec(Node<TKey, TValue>* node, int depth, bool is_left,
        const std::string& prefix) const noexcept;
    void print_dclr_rec(Node<TKey, TValue>* node, int depth, bool is_left,
        const std::string& prefix) const noexcept;

    void clear_rec(Node<TKey, TValue>* node) noexcept;
};


template <class TKey, class TValue>
Tree<TKey, TValue>::Tree() : _root(nullptr) {}

template <class TKey, class TValue>
Tree<TKey, TValue>::~Tree() { 
    clear(); 
}

template <class TKey, class TValue>
bool Tree<TKey, TValue>::is_empty() const noexcept {
    return _root == nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear() noexcept {
    clear_rec(_root);
    _root = nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear_rec(Node<TKey, TValue>* node) noexcept {
    if (node == nullptr) 
        return;
    clear_rec(node->_left);  
    clear_rec(node->_right); 
    delete node;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_prefix(
    std::ostream& os, const std::string& prefix, int depth,
    bool is_left, const char* left_symbol, const char* right_symbol) const noexcept
{
    os << prefix;

    if (depth > 0) {
        if (is_left) {
            os << left_symbol;
        }
        else {
            os << right_symbol;
        }
    }
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_w() const noexcept {
    if (_root == nullptr) {
        std::cout << " --- Empty --- \n";
        return;
    }

    Queue<Node<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        Node<TKey, TValue>* cur = q.head();
        q.pop();

        if (cur == nullptr) continue;

        std::cout << "(" << cur->_data.first << ", " << cur->_data.second << ") "; 

        if (cur->_left) q.push(cur->_left);   
        if (cur->_right) q.push(cur->_right); 
    }
    std::cout << "\n";
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_dlcr() const noexcept {
    if (_root == nullptr) {
        std::cout << " --- Empty --- \n";
        return;
    }
    print_dlcr_rec(_root, 0, false, "");
    std::cout << "\n";
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_dlcr_rec(
    Node<TKey, TValue>* node, int depth, bool is_left,
    const std::string& prefix) const noexcept
{
    if (node == nullptr) {
        return;
    }

    if (node->_left != nullptr) {
        std::string new_prefix = prefix;
        if (depth > 0) {
            new_prefix += "    ";
        }
        else {
            new_prefix += " ";
        }
        print_dlcr_rec(node->_left, depth + 1, true, new_prefix);
    }

    print_prefix(std::cout, prefix, depth, is_left, "|-- ", "`-- ");

    std::cout << "(" << node->_data.first << ", "
        << node->_data.second << ")\n";

    if (node->_right != nullptr) {

        std::string new_prefix = prefix;

        if (depth > 0) {
            new_prefix += "    ";
        }
        else {
            new_prefix += " ";
        }
        print_dlcr_rec(node->_right, depth + 1, false, new_prefix);
    }
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_dlrc() const noexcept {
    if (_root == nullptr) {
        std::cout << " --- Empty --- \n";
        return;
    }
    print_dlrc_rec(_root, 0, false, "");
    std::cout << "\n";
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_dlrc_rec(
    Node<TKey, TValue>* node, int depth, bool is_left,
    const std::string& prefix) const noexcept
{
    if (node == nullptr) {
        return;
    }

    if (node->_left != nullptr) {
        std::string new_prefix = prefix;
        if (depth > 0) {
            if (is_left) {
                new_prefix += "    ";
            }
            else {
                new_prefix += "    ";
            }
        }
        print_dlrc_rec(node->_left, depth + 1, true, new_prefix);
    }

    if (node->_right != nullptr) {
        std::string new_prefix = prefix;
        if (depth > 0) {
            new_prefix += "    ";
        }
        print_dlrc_rec(node->_right, depth + 1, false, new_prefix);
    }

    if (depth > 0) {
        std::cout << prefix;
        if (depth > 0) {
            std::cout << prefix;
            if (is_left) {
                std::cout << "|-- ";
            }
            else {
                std::cout << ",-- ";
            }
        }
    }
    std::cout << "(" << node->_data.first << ", "
        << node->_data.second << ")\n";
}template <class TKey, class TValue>
void Tree<TKey, TValue>::print_dclr() const noexcept {
    if (_root == nullptr) {
        std::cout << " --- Empty --- \n";
        return;
    }
    print_dclr_rec(_root, 0, false, "");
    std::cout << "\n";
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_dclr_rec(Node<TKey, TValue>* node, int depth, bool is_left,
    const std::string& prefix) const noexcept {
    if (node == nullptr) return;

    print_prefix(std::cout, prefix, depth, is_left, "|-- ", "`-- ");
    std::cout << "(" << node->_data.first << ", " << node->_data.second << ")\n";  

    std::string new_prefix = prefix;
    if (depth == 0) {
        new_prefix += " ";
    }
    if (is_left) {
                new_prefix += "|   ";
    }
    else {
        new_prefix += "    ";
    }

    if (node->_left)   
        print_dclr_rec(node->_left, depth + 1, true, new_prefix);
    if (node->_right)  
        print_dclr_rec(node->_right, depth + 1, false, new_prefix);
}

template <class TKey, class TValue>
Node<TKey, TValue>* Tree<TKey, TValue>::find(const TKey& key) const {
    if (is_empty())
        throw std::out_of_range("Tree is empty");  
    Queue<Node<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        Node<TKey, TValue>* cur = q.head();
        q.pop();

        if (cur == nullptr) continue;

        if (cur->_data.first == key) {  
            return cur;
        }

        if (cur->_left) q.push(cur->_left);   
        if (cur->_right) q.push(cur->_right); 
    }

    throw std::out_of_range("Key not found in tree");
}



template <class TKey, class TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& value) {

    Queue<Node<TKey, TValue>*> check_q;
    check_q.push(_root);
    while (!check_q.is_empty()) {
        Node<TKey, TValue>* cur = check_q.head();
        check_q.pop();
        if (cur != nullptr) {
            if (cur->_data.first == key) {
                throw std::logic_error("Key already exist");
            }
            check_q.push(cur->_left);
            check_q.push(cur->_right);
        }
    }

    Node<TKey, TValue>* node = new Node<TKey, TValue>(key, value);
    if (is_empty()) {
        _root = node;
        return;
    }

    Queue<Node<TKey, TValue>*> q;
    q.push(_root);
    while (!q.is_empty()) {
        Node<TKey, TValue>* cur = q.head();
        q.pop();
        if (cur->_left == nullptr) {
            cur->_left = node;
            return;
        }
        else {
            q.push(cur->_left);
        }
        if (cur->_right == nullptr) {
            cur->_right = node;
            return;
        }
        else {
            q.push(cur->_right);
        }
    }
}

template <class TKey, class TValue>
Node<TKey, TValue>* Tree<TKey, TValue>::get_root_ptr() const noexcept {
    return _root;
}
template <class TKey, class TValue>
void Tree<TKey, TValue>::delete_node(Node<TKey, TValue>* parent, Node<TKey, TValue>* node) {
    if (!parent) {
        delete _root;
        _root = nullptr;
    }
    else if (parent->_left == node) {
        delete parent->_left;
        parent->_left = nullptr;
    }
    else {
        delete parent->_right;
        parent->_right = nullptr;
    }
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::erase(const TKey& key) {
    if (is_empty()) {
        throw std::out_of_range("Tree is empty");
    }

    Node<TKey, TValue>* node_to_delete = nullptr;
    Node<TKey, TValue>* last_parent = nullptr;
    Node<TKey, TValue>* last = _root;

    Queue<Node<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        Node<TKey, TValue>* cur = q.head();
        q.pop();

        if (cur->_data.first == key)  
            node_to_delete = cur;

        if (cur->_left) {  
            last_parent = cur;
            last = cur->_left;  
            q.push(cur->_left);
        }
        if (cur->_right) {  
            last_parent = cur;
            last = cur->_right;  
            q.push(cur->_right);
        }
    }

    if (!node_to_delete) {
        throw std::out_of_range("Key not found in tree");
    }

    if (node_to_delete == last) {
        delete_node(last_parent, last);
        return;
    }

    node_to_delete->_data = last->_data;
    delete_node(last_parent, last);
}