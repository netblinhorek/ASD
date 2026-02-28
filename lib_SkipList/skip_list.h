#pragma once
#include "../lib_TVector/tvector.h"
#include "../lib_ITable/itable.h"
#include <iomanip>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

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

    SkipList(size_t maxLevels) {
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

        Node<TKey, TValue>* nearest = find_nearest(key, update);
        Node<TKey, TValue>* next_node;
        if (nearest != nullptr) {
            next_node = nearest->next[0];
        }
        else {
            next_node = _heads[0];
        }

        if (next_node == nullptr || next_node->key != key) {
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
        }

        delete[] update;
    }


    void print() const noexcept {
        if (is_empty()) {
            std::cout << "SkipList: (empty)\n";
            return;
        }

        for (int level = static_cast<int>(_lvl); level >= 0; --level) {
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

    Node<TKey, TValue>* find_nearest(const TKey& key, Node<TKey,
        TValue>** update = nullptr) const noexcept {
        if (_heads[0] == nullptr)
            return nullptr;

        Node<TKey, TValue>* current = nullptr;

        for (int i = static_cast<int>(_lvl); i >= 0; i--) {
            Node<TKey, TValue>* start;
            if (current == nullptr) {
                start = _heads[i];        
            }
            else {
                start = current->next[i]; 
            }
            while (start != nullptr && start->key < key) {
                current = start;
                start = current->next[i];
            }

            if (update != nullptr) {
                update[i] = current;
            }
        }

        Node<TKey, TValue>* result;
        if (current == nullptr) {
            result = _heads[0]; 
        }
        else {
            result = current->next[0];
        }
        if (result != nullptr && result->key == key) {
            return result;
        }

        return nullptr;
    }

};