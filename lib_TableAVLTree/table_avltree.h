#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <iomanip> 
#include "../lib_ITable/itable.h"
#include "../lib_TVector/tvector.h"
#include "../lib_AVLTree/avltree.h"

template <class TKey, class TValue>
class TableAVLTree : public ITable<TKey, TValue> {
private:
    AVLTree<TKey, TValue> _rows;

    const AVLNode<TKey, TValue>* get_node_by_index(
        const AVLNode<TKey, TValue>* node,
        size_t index,
        size_t& current_index) const
    {
        if (node == nullptr) return nullptr;

        const AVLNode<TKey, TValue>* left = get_node_by_index(
            node->_left, index, current_index);
        if (left != nullptr) return left;

        if (current_index == index) return node;
        ++current_index;

        return get_node_by_index(node->_right, index, current_index);
    }
    void print_dlcr_rec(const AVLNode<TKey, TValue>* node, int key_width, int value_width) const noexcept {
        if (node == nullptr) return;

        print_dlcr_rec(node->_left, key_width, value_width);

        std::cout << "| " << std::left << std::setw(key_width) << node->_data.first
            << " | " << std::left << std::setw(value_width) << node->_data.second << " |" << std::endl;

        print_dlcr_rec(node->_right, key_width, value_width);
    }

public:
    TableAVLTree() {}
    TableAVLTree(size_t capacity) {}
    void insert(const TKey& key, const TValue& value) override {
        _rows.insert(key, value);
    }

    void erase(const TKey& key) override {
        _rows.erase(key);
    }

    TValue& found(const TKey& key) override {
        try {
            return *_rows.find(key);
        }
        catch (const std::out_of_range&) {
            throw std::logic_error("Key not found");
        }
    }

    bool is_empty() const noexcept override {
        return _rows.is_empty();
    }

    size_t size() const {
        return _rows.size();
    }

    const TKey& get_key(size_t index) const {
        if (index >= _rows.size())
            throw std::out_of_range("Index out of range");
        size_t current_index = 0;

        const AVLNode<TKey, TValue>* node =
            get_node_by_index(_rows.get_root_ptr(), index, current_index);
        return node->_data.first;
    }

    TValue& operator[](const TKey& key) {
        return found(key);
    }

    const TValue& operator[](const TKey& key) const {
        return *_rows.find(key);
    }

    void print_line(std::ostream& os, int key_width, int value_width) const {
        os << "+";
        for (int i = 0; i < key_width + 2; i++) os << "-";
        os << "+";
        for (int i = 0; i < value_width + 2; i++) os << "-";
        os << "+" << std::endl;
    }

    void print() override {
        const int KEY_WIDTH = 15;
        const int VALUE_WIDTH = 60;

        std::cout << "\n\t *** Sorted Table ***\t\n" << std::endl;

        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);
        std::cout << "| " << std::left << std::setw(KEY_WIDTH) << "Key"
            << " | " << std::left << std::setw(VALUE_WIDTH) << "Value" << " |" << std::endl;
        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);

        if (!_rows.is_empty()) {
            print_dlcr_rec(_rows.get_root_ptr(), KEY_WIDTH, VALUE_WIDTH);
        }
        else {
            std::cout << "| " << std::left << std::setw(KEY_WIDTH) << "---"
                << " | " << std::left << std::setw(VALUE_WIDTH) << "Empty Table" << " |" << std::endl;
        }

        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);
    }
};