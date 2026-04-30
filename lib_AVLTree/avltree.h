#include <iostream>
#include <algorithm>
#include <stdexcept>

template <class TKey, class TValue>
struct ALVNode {
    ALVNode<TKey, TValue>* _left, * _right, * _parent;
    std::pair<TKey, TValue> _data;
    size_t _height;

    ALVNode(const TKey& key, const TValue& value)
        : _left(nullptr), _right(nullptr), _parent(nullptr),
        _data(key, value), _height(1) {}
};

template <class TKey, class TValue>
class ALVTree {
    ALVNode<TKey, TValue>* _root;

private:
    size_t get_height(ALVNode<TKey, TValue>* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->_height;
    }

    int calc_balance(ALVNode<TKey, TValue>* node) {
        if (node == nullptr) {
            return 0;
        }

        int left_h = (int)get_height(node->_left);
        int right_h = (int)get_height(node->_right);

        return left_h - right_h;
    }

    void recalc_height(ALVNode<TKey, TValue>* node) {
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

    void left_rotate(ALVNode<TKey, TValue>* G) {
        ALVNode<TKey, TValue>* P = G->_right;
        G->_right = P->_left;
        if (P->_left) P->_left->_parent = G;

        P->_parent = G->_parent;
        if (!G->_parent) _root = P;
        else if (G == G->_parent->_left) G->_parent->_left = P;
        else G->_parent->_right = P;

        P->_left = G;
        G->_parent = P;

        recalc_height(G);
        recalc_height(P);
    }

    void right_rotate(ALVNode<TKey, TValue>* G) {
        ALVNode<TKey, TValue>* P = G->_left;
        G->_left = P->_right;
        if (P->_right) P->_right->_parent = G;

        P->_parent = G->_parent;
        if (!G->_parent) _root = P;
        else if (G == G->_parent->_left) G->_parent->_left = P;
        else G->_parent->_right = P;

        P->_right = G;
        G->_parent = P;

        recalc_height(G);
        recalc_height(P);
    }

    void LL(ALVNode<TKey, TValue>* node) {
        right_rotate(node);
    }

    void RR(ALVNode<TKey, TValue>* node) {
        left_rotate(node);
    }

    void LR(ALVNode<TKey, TValue>* node) {
        left_rotate(node->_left);
        right_rotate(node);
    }

    void RL(ALVNode<TKey, TValue>* node) {
        right_rotate(node->_right);
        left_rotate(node);
    }

    void recovery_balance(ALVNode<TKey, TValue>* node) {
        int balance = calc_balance(node);
        if (balance > 1) {
            if (calc_balance(node->_left) >= 0)
                LL(node);
            else
                LR(node);
        }
        else if (balance < -1) {
            if (calc_balance(node->_right) <= 0)
                RR(node);
            else
                RL(node);
        }
    }

    void clear_subtree(ALVNode<TKey, TValue>* node) {
        if (node) {
            clear_subtree(node->_left);
            clear_subtree(node->_right);
            delete node;
        }
    }

public:
    ALVTree() : _root(nullptr) {}

    bool is_empty() const {
        return _root == nullptr;
    }

    void clear() {
        clear_subtree(_root);
        _root = nullptr;
    }

    void insert(const TKey& key, const TValue& value) {
        if (!_root) {
            _root = new ALVNode<TKey, TValue>(key, value);
            return;
        }

        ALVNode<TKey, TValue>* cur = _root;
        ALVNode<TKey, TValue>* parent = nullptr;
        while (cur) {
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

        ALVNode<TKey, TValue>* newNode = new ALVNode<TKey, TValue>(key, value);
        newNode->_parent = parent;
        if (key < parent->_data.first)
            parent->_left = newNode;
        else
            parent->_right = newNode;

        ALVNode<TKey, TValue>* temp = parent;
        while (temp) {
            recalc_height(temp);
            if (abs(calc_balance(temp)) > 1) {
                recovery_balance(temp);
            }
            temp = temp->_parent;
        }
    }

    void erase(const TKey& key) {
        ALVNode<TKey, TValue>* z = find(key);
        if (!z) {
            throw std::logic_error("Key not found in the tree.");
        }

        ALVNode<TKey, TValue>* y = z;
        ALVNode<TKey, TValue>* x = nullptr;
        ALVNode<TKey, TValue>* balance_start_node = nullptr;

        if (!z->_left || !z->_right) {
            y = z;
            balance_start_node = y->_parent;
        }
        else {
            y = z->_right;
            while (y->_left) y = y->_left;
            z->_data = y->_data;
            balance_start_node = y->_parent;
        }

        if (y->_left) {
            x = y->_left;
        }
        else {
            x = y->_right;
        }

        if (x) x->_parent = y->_parent;

        if (!y->_parent) {
            _root = x;
        }
        else if (y == y->_parent->_left) {
            y->_parent->_left = x;
        }
        else {
            y->_parent->_right = x;
        }

        delete y;

        ALVNode<TKey, TValue>* cur = balance_start_node;
        while (cur) {
            recalc_height(cur);
            if (abs(calc_balance(cur)) > 1) {
                recovery_balance(cur);
            }
            cur = cur->_parent;
        }
    }

    ALVNode<TKey, TValue>* find(const TKey& key) {
        ALVNode<TKey, TValue>* cur = _root;
        while (cur) {
            if (key == cur->_data.first)
                return cur;
            cur = (key < cur->_data.first) ? cur->_left : cur->_right;
        }
        throw std::out_of_range("Key not found");
    }
};