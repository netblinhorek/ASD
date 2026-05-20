#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <utility>
#include "../lib_BaseBSTree/base_bstree.h"

enum class Color { Red, Black, BlackBlack };

template <class TKey, class TValue>
struct RBNode {
    RBNode<TKey, TValue>* _left;
    RBNode<TKey, TValue>* _right;
    RBNode<TKey, TValue>* _parent;
    std::pair<TKey, TValue> _data;
    Color _color;

    RBNode(const TKey& key, const TValue& value, Color color = Color::Red)
        : _left(nullptr), _right(nullptr), _parent(nullptr),
        _data(key, value), _color(color) {}
};

template <class TKey, class TValue>
class RBTree : public BaseBSTree<TKey, TValue, RBNode<TKey, TValue>> {
    using Node = RBNode<TKey, TValue>;

private:
    Color get_color(const Node* node) const noexcept {
        if (node == nullptr) {
            return Color::Black;
        }
        if (node->_color == Color::BlackBlack) {
            return Color::Black;
        }
        return node->_color;
    }

    void set_color(Node* node, Color color) noexcept {
        if (node != nullptr) {
            node->_color = color;
        }
    }

    Node* tree_minimum(Node* node) const noexcept {
        Node* current = node;
        while (current != nullptr && current->_left != nullptr) {
            current = current->_left;
        }
        return current;
    }

    void replace_node(Node* u, Node* v) noexcept {
        if (u->_parent == nullptr) {
            this->_root = v;
        }
        else if (u == u->_parent->_left) {
            u->_parent->_left = v;
        }
        else {
            u->_parent->_right = v;
        }
        if (v != nullptr) {
            v->_parent = u->_parent;
        }
    }

    void handle_erase_case(Node*& x, Node*& x_p, Node* s, bool is_left) noexcept {
        if (get_color(s) == Color::Red) {
            set_color(s, Color::Black);
            set_color(x_p, Color::Red);
            if (is_left) {
                this->left_rotate(x_p);
            }
            else {
                this->right_rotate(x_p);
            }
            x_p = x->_parent;
            if (is_left) {
                s = x_p->_right;
            }
            else {
                s = x_p->_left;
            }
        }

        if (get_color(s->_left) == Color::Black && get_color(s->_right) == Color::Black) {
            set_color(s, Color::Red);
            if (get_color(x_p) == Color::Red) {
                set_color(x_p, Color::Black);
            }
            else {
                set_color(x_p, Color::BlackBlack);
                x = x_p;
                x_p = x->_parent;
            }
        }
        else {
            if (is_left && get_color(s->_right) == Color::Black) {
                set_color(s->_left, Color::Black);
                set_color(s, Color::Red);
                this->right_rotate(s);
                s = x_p->_right;
            }
            else if (!is_left && get_color(s->_left) == Color::Black) {
                set_color(s->_right, Color::Black);
                set_color(s, Color::Red);
                this->left_rotate(s);
                s = x_p->_left;
            }

            set_color(s, get_color(x_p));
            set_color(x_p, Color::Black);
            if (is_left) {
                set_color(s->_right, Color::Black);
                this->left_rotate(x_p);
            }
            else {
                set_color(s->_left, Color::Black);
                this->right_rotate(x_p);
            }
            x = this->_root;
        }
    }

    void recovery_balance_insert(Node* node) noexcept {
        while (node != this->_root && get_color(node->_parent) == Color::Red) {
            Node* P = node->_parent;      
            Node* G = P->_parent;         

            if (P == G->_left) {
                Node* uncle = G->_right;
                if (get_color(uncle) == Color::Red) {
                    set_color(P, Color::Black);
                    set_color(uncle, Color::Black);
                    set_color(G, Color::Red);
                    node = G;
                }
                else {
                    if (node == P->_right) {
                        node = P;
                        this->left_rotate(node);
                        P = node->_parent;    
                    }
                    set_color(P, Color::Black);
                    set_color(G, Color::Red);
                    this->right_rotate(G);
                }
            }
            else {
                Node* uncle = G->_left;
                if (get_color(uncle) == Color::Red) {
                    set_color(P, Color::Black);
                    set_color(uncle, Color::Black);
                    set_color(G, Color::Red);
                    node = G;
                }
                else {
                    if (node == P->_left) {
                        node = P;
                        this->right_rotate(node);
                        P = node->_parent;  
                    }
                    set_color(P, Color::Black);
                    set_color(G, Color::Red);
                    this->left_rotate(G);
                }
            }
        }
        set_color(this->_root, Color::Black);
    }

    void recovery_balance_erase(Node* x, Node* x_parent) noexcept {
        while (x != this->_root && (get_color(x) == Color::Black || 
            get_color(x) == Color::BlackBlack)) {
            if (x == x_parent->_left) {
                handle_erase_case(x, x_parent, x_parent->_right, true);
            }
            else {
                handle_erase_case(x, x_parent, x_parent->_left, false);
            }
            if (x != nullptr) {
                x_parent = x->_parent;
            }
        }
        set_color(x, Color::Black);
        if (x != nullptr && x->_color == Color::BlackBlack) {
            x->_color = Color::Black;
        }
    }

public:
    RBTree() : BaseBSTree<TKey, TValue, RBNode<TKey, TValue>>() {}


    

    void insert(const TKey& key, const TValue& value) {
        Node* new_node = this->insert_node(key, value);
        if (new_node != nullptr) {
            set_color(new_node, Color::Red);
            recovery_balance_insert(new_node);
        }
        set_color(this->_root, Color::Black);
    }

    void erase(const TKey& key) {
        if (this->is_empty()) throw std::out_of_range("Tree is empty");
        Node* z = find_node(key);
        if (!z) throw std::out_of_range("Key not found");

        Node* y = z;
        Node* x;
        Node* x_p;
        Color y_orig = y->_color;

        if (!z->_left) {
            x = z->_right;
            x_p = z->_parent;
            replace_node(z, z->_right);
        }
        else if (!z->_right) {
            x = z->_left;
            x_p = z->_parent;
            replace_node(z, z->_left);
        }
        else {
            y = tree_minimum(z->_right);
            y_orig = y->_color;
            x = y->_right;

            if (y->_parent == z) {
                x_p = y;
            }
            else {
                x_p = y->_parent;
                replace_node(y, y->_right);
                y->_right = z->_right;
                y->_right->_parent = y;
            }

            replace_node(z, y);
            y->_left = z->_left;
            y->_left->_parent = y;
            y->_color = z->_color;
        }

        delete z;
        this->_size--;

        if (y_orig == Color::Black) {
            recovery_balance_erase(x, x_p);
        }
        set_color(this->_root, Color::Black);
    }
};