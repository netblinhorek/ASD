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

public:
    void print() const noexcept {
        if (this->_root == nullptr) {
            std::cout << "Дерево пустое." << std::endl;
            return;
        }
        print_tree_helper(this->_root, "", true);
    }

private:
    void print_tree_helper(Node* node, std::string indent, bool last) const noexcept {
        if (node != nullptr) {
            std::cout << indent;
            if (last) {
                std::cout << "|-- ";
                indent += "    ";
            }
            else {
                std::cout << "|-- ";
                indent += "|   ";
            }

            std::string color_str;
            if (node->_color == Color::Red) {
                color_str = "[R]";
            }
            else {
                color_str = "[B]";
            }
            std::cout << node->_data.first << " " << color_str << std::endl;

            print_tree_helper(node->_right, indent, false);
            print_tree_helper(node->_left, indent, true);
        }
    }

private:
    void LL(Node* node) noexcept {
        this->right_rotate(node);
    }

    void RR(Node* node) noexcept {
        this->left_rotate(node);
    }

    void LR(Node* node) noexcept {
        if (node != nullptr && node->_left != nullptr) {
            this->left_rotate(node->_left);
            this->right_rotate(node);
        }
    }

    void RL(Node* node) noexcept {
        if (node != nullptr && node->_right != nullptr) {
            this->right_rotate(node->_right);
            this->left_rotate(node);
        }
    }

    void swap_colors(Node* n1, Node* n2) noexcept {
        if (n1 != nullptr && n2 != nullptr) {
            Color temp = n1->_color;
            n1->_color = n2->_color;
            n2->_color = temp;
        }
    }

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

    void handle_erase_case(Node*& x, Node*& P, Node* S, bool is_left) noexcept {
        if (get_color(S) == Color::Red) {
            set_color(S, Color::Black);
            set_color(P, Color::Red);

            if (is_left) {
                this->RR(P);
            }
            else {
                this->LL(P);
            }
            if (x != nullptr) P = x->_parent;

            if (P != nullptr) {
                if (is_left) {
                    S = P->_right;
                }
                else {
                    S = P->_left;
                }
            }
        }

        if (S != nullptr && get_color(S->_left) == Color::Black && get_color(S->_right) == Color::Black) {
            set_color(S, Color::Red);

            if (get_color(P) == Color::Red) {
                set_color(P, Color::Black);
                x = P;
            }
            else {
                set_color(P, Color::BlackBlack);
                x = P;
                if (x != nullptr) P = x->_parent;
            }
        }
        else if (S != nullptr) {
            if (is_left && get_color(S->_right) == Color::Black) {
                set_color(S->_left, Color::Black);
                set_color(S, Color::Red);
                this->LL(S);
                S = P->_right;
            }
            else if (!is_left && get_color(S->_left) == Color::Black) {
                set_color(S->_right, Color::Black);
                set_color(S, Color::Red);
                this->RR(S);
                S = P->_left;
            }

            set_color(S, get_color(P));
            set_color(P, Color::Black);

            if (is_left) {
                set_color(S->_right, Color::Black);
                this->RR(P);
            }
            else {
                set_color(S->_left, Color::Black);
                this->LL(P);
            }

            x = this->_root;
        }
    }

    void recovery_balance_erase(Node* x, Node* P) noexcept {
        Node* current = x;
        while (current != this->_root && (current == nullptr || get_color(current) == Color::Black)) {
            if (P == nullptr)
                break;
            if (current == P->_left) {
                Node* S = P->_right;
                handle_erase_case(current, P, S, true);
            }
            else {
                Node* S = P->_left;
                handle_erase_case(current, P, S, false);
            }

            if (current != nullptr) P = current->_parent;
            else if (P != nullptr) P = P->_parent;
        }
        if (current != nullptr) set_color(current, Color::Black);
    }

    void recovery_balance_insert(Node* node) noexcept {
        while (node != this->_root && get_color(node->_parent) == Color::Red) {
            Node* P = node->_parent;
            Node* G = P->_parent;

            if (G == nullptr) break;

            if (P == G->_left) {
                Node* U = G->_right;
                handle_insert_case(node, P, G, U, true);
            }
            else {
                Node* U = G->_left;
                handle_insert_case(node, P, G, U, false);
            }
        }
        set_color(this->_root, Color::Black);
    }

    void handle_insert_case(Node*& node, Node* P, Node* G, Node* U, bool is_left) noexcept {
        if (get_color(U) == Color::Red) {
            set_color(P, Color::Black);
            set_color(U, Color::Black);
            set_color(G, Color::Red);
            node = G;
        }
        else {
            if (is_left) {
                if (node == P->_right) {
                    this->left_rotate(P);
                    node = P;
                    P = node->_parent;
                }
                this->right_rotate(G);
                set_color(P, Color::Black);
                set_color(G, Color::Red);
            }
            else {
                if (node == P->_left) {
                    this->right_rotate(P);
                    node = P;
                    P = node->_parent;
                }
                this->left_rotate(G);
                set_color(P, Color::Black);
                set_color(G, Color::Red);
            }
        }
    }

public:
    RBTree() : BaseBSTree<TKey, TValue, RBNode<TKey, TValue>>() {}

    Node* get_root_ptr() const noexcept {
        return this->_root;
    }

    Node* find_node(const TKey& key) const noexcept {
        Node* cur = this->_root;
        while (cur != nullptr) {
            if (key == cur->_data.first) {
                return cur;
            }
            if (key < cur->_data.first) {
                cur = cur->_left;
            }
            else {
                cur = cur->_right;
            }
        }
        return nullptr;
    }

    void insert(const TKey& key, const TValue& value) {
        Node* new_node = this->insert_node(key, value);
        if (new_node != nullptr) {
            set_color(new_node, Color::Red);
            recovery_balance_insert(new_node);
        }
    }

    void erase(const TKey& key) {
        if (this->is_empty()) throw std::out_of_range("Tree is empty");
        Node* z = find_node(key);
        if (!z) throw std::out_of_range("Key not found");

        Node* y = z;
        Node* x;
        Node* P;
        Color y_orig = y->_color;

        if (!z->_left) {
            x = z->_right;
            P = z->_parent;
            replace_node(z, z->_right);
        }
        else if (!z->_right) {
            x = z->_left;
            P = z->_parent;
            replace_node(z, z->_left);
        }
        else {
            y = this->find_max(z->_left);
            y_orig = y->_color;
            x = y->_left;

            if (y->_parent == z) {
                P = y;
            }
            else {
                P = y->_parent;
                replace_node(y, y->_left);
                y->_left = z->_left;
                y->_left->_parent = y;
            }

            replace_node(z, y);
            y->_right = z->_right;
            y->_right->_parent = y;
            y->_color = z->_color;
        }

        delete z;
        this->_size--;

        if (y_orig == Color::Black) {
            recovery_balance_erase(x, P);
        }

        if (this->_root) {
            set_color(this->_root, Color::Black);
        }
    }
};