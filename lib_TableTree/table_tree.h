#pragma once
#define UNSORTED_ON_TREE_H

#include "../lib_ITable/itable.h"
#include "../lib_Tree/tree.h"
#include "../lib_Queue/queue.h"
#include <iomanip>
#include <stdexcept>
#include <iostream>

template <class TKey, class TValue>
class TableTree : public ITable<TKey, TValue> {
private:
    Tree<TKey, TValue> _rows;

public:
    TableTree() {}

    void insert(const TKey& key, const TValue& value) override {
        _rows.insert(key, value);
    }

    void erase(const TKey& key) override {
        _rows.erase(key);
    }

    TValue& found(const TKey& key) override {
        try {
            return _rows.find(key)->_data.second;
        }
        catch (const std::out_of_range&) {
            throw std::logic_error("Key not found");
        }
    }

    bool is_empty() const noexcept override {
        return _rows.is_empty();
    }

    TValue& operator[](const TKey& key) {
        return found(key);
    }

    const TValue& operator[](const TKey& key) const {
        return _rows.find(key)->_data.second;
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

        std::cout << "\n\t *** Table ***\t\n" << std::endl;
        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);
        std::cout << "| " << std::left << std::setw(KEY_WIDTH) << "Key"
            << " | " << std::left << std::setw(VALUE_WIDTH) << "Value" << " |" << std::endl;
        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);

        if (!_rows.is_empty()) {
            Queue<Node<TKey, TValue>*> q;
            q.push(_rows.get_root_ptr());

            while (!q.is_empty()) {
                Node<TKey, TValue>* cur = q.head();
                q.pop();
                if (cur == nullptr) continue;

                std::cout << "| " << std::left << std::setw(KEY_WIDTH) << cur->_data.first
                    << " | " << std::left << std::setw(VALUE_WIDTH) << cur->_data.second << " |" << std::endl;

                if (cur->_left) q.push(cur->_left);
                if (cur->_right) q.push(cur->_right);
            }
        }
        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);
    }
};