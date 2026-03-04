#pragma once
#include "../lib_TVector/tvector.h"
#include "../lib_ITable/itable.h"
#include <iomanip>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <stdexcept>

template <typename TKey, typename TValue>
struct Node {
    bool is_owner;
    TKey key;
    TValue* data;
    Node<TKey, TValue>** next;

    Node(const TKey& k, const TValue& value, size_t level)
        : Node(k, new TValue(value), level, true) {}

    Node(const TKey& k, TValue* existing_data, size_t level)
        : Node(k, existing_data, level, false) {}

    ~Node() {
        if (is_owner) {
            delete data;
        }
        delete[] next;
    }

private:
    Node(const TKey& k, TValue* data_ptr, size_t level, bool owner)
        : key(k), data(data_ptr), is_owner(owner) {
        next = new Node<TKey, TValue>* [level + 1];
        for (size_t i = 0; i <= level; i++) {
            next[i] = nullptr;
        }
    }
};

template <class TKey, class TValue>
class SkipList {
    size_t _Max_LVLs;
    size_t _lvl;
    TVector<Node<TKey, TValue>*> _heads;

public:

public:
    SkipList(size_t maxLevels = -1) {
        if (maxLevels == -1) {
            maxLevels = 1000000;  
        }

        if (maxLevels == 0) {
            throw std::invalid_argument("The maximum number of levels must be greater than 0");
        }

        _Max_LVLs = maxLevels;
        _lvl = 0;

        _heads = TVector<Node<TKey, TValue>*>(_Max_LVLs);
        for (size_t i = 0; i < _Max_LVLs; ++i) {
            _heads[i] = nullptr;
        }
    }

    ~SkipList() {
        clear();
    }

    TVector<TKey> get_keys() const {
        TVector<TKey> keys;
        Node<TKey, TValue>* current = _heads[0];
        while (current != nullptr) {
            keys.push_back(current->key);
            current = current->next[0];
        }
        return keys;
    }

    void clear() {
        if (_heads[0] == nullptr) return;

        Node<TKey, TValue>* current = _heads[0];
        while (current != nullptr) {
            Node<TKey, TValue>* next = current->next[0];
            delete current;
            current = next;
        }

        for (size_t i = 0; i < _Max_LVLs; i++) {
            _heads[i] = nullptr;
        }
        _lvl = 0;
    }

    void insert(const TKey& key, const TValue& value) {
        Node<TKey, TValue>** update = new Node<TKey, TValue>* [_Max_LVLs];
        for (size_t i = 0; i < _Max_LVLs; i++) {
            update[i] = nullptr;
        }

        Node<TKey, TValue>* current = nullptr;

        for (size_t i = _lvl + 1; i-- > 0; ) {
            Node<TKey, TValue>* start = (current == nullptr) ? _heads[i] : current;

            while (start != nullptr && start->key < key) {
                current = start;
                start = start->next[i];
            }

            update[i] = current;
        }

        Node<TKey, TValue>* existing_node = nullptr;
        if (current == nullptr) {
            existing_node = _heads[0];
        }
        else {
            existing_node = current->next[0];
        }

        if (existing_node != nullptr && existing_node->key == key) {
            if (existing_node->is_owner) {
                *(existing_node->data) = value;
            }
            else {
                size_t new_level = _coin();

                if (new_level > _lvl) {
                    _lvl = new_level;
                }

                Node<TKey, TValue>* new_node = new Node<TKey, TValue>(key, value, new_level);

                for (size_t i = 0; i <= new_level; i++) {
                    if (update[i] == nullptr) {
                        if (_heads[i] == existing_node) {
                            _heads[i] = new_node;
                            new_node->next[i] = existing_node->next[i];
                        }
                    }
                    else if (update[i]->next[i] == existing_node) {
                        update[i]->next[i] = new_node;
                        new_node->next[i] = existing_node->next[i];
                    }
                }

                delete existing_node;
            }

            delete[] update;
            return;
        }

        size_t new_level = _coin();

        if (new_level > _lvl) {
            for (size_t i = _lvl + 1; i <= new_level; i++) {
                update[i] = nullptr;
            }
            _lvl = new_level;
        }

        Node<TKey, TValue>* new_node = new Node<TKey, TValue>(key, value, new_level);

        for (size_t i = 0; i <= new_level; i++) {
            if (update[i] == nullptr) {
                new_node->next[i] = _heads[i];
                _heads[i] = new_node;
            }
            else {
                new_node->next[i] = update[i]->next[i];
                update[i]->next[i] = new_node;
            }
        }

        delete[] update;
    }

    void print() const noexcept {
        if (is_empty()) {
            std::cout << "SkipList: (empty)\n";
            return;
        }

        for (size_t level = _lvl + 1; level-- > 0; ) {
            std::cout << "Level " << level << ":";

            Node<TKey, TValue>* current = _heads[level];
            while (current != nullptr) {
                std::cout << " " << std::setw(3) << current->key;
                if (current->next[level] != nullptr) {
                    std::cout << " -> ";
                }
                else {
                    std::cout << "    ";
                }
                current = current->next[level];
            }
            std::cout << "\n";
        }
    }

    bool is_empty() const noexcept {
        return _heads[0] == nullptr;
    }

    size_t _coin() const noexcept {
        size_t level = 0;
        while (level < _Max_LVLs - 1) {
            int tmp = rand() % 100;
            if (tmp < 50) {
                level++;
            }
            else {
                break;
            }
        }
        return level;
    }

    Node<TKey, TValue>* find_nearest(const TKey& key, Node<TKey, TValue>** update = nullptr) const noexcept {
        if (_heads[0] == nullptr)
            return nullptr;

        Node<TKey, TValue>* current;

        for (size_t i = _lvl + 1; i-- > 0; ) {
            current = _heads[i];

            while (current != nullptr && current->next[i] != nullptr && current->next[i]->key < key) {
                current = current->next[i];
            }

            if (update != nullptr) {
                update[i] = current;
            }
        }

        if (current != nullptr && current->key == key) {
            return current;
        }

        if (current != nullptr && current->next[0] != nullptr && current->next[0]->key == key) {
            return current->next[0];
        }

        return nullptr;
    }

};