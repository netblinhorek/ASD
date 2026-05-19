#pragma once  
#include "../lib_ITable/itable.h"
#include "../lib_TVector/tvector.h"
#include "../lib_List/list.h"  
#include <iomanip>
#include <stdexcept>
#include <string>
#include <iostream>

template <class TKey, class TValue>
class HashTableC : public ITable<std::string, TValue> {
private:
    struct HashData {
        std::string key;
        TValue value;

        HashData() : key(""), value(TValue()) {}
        HashData(const std::string& k, const TValue& v) : key(k), value(v) {}
    };

    TVector<List<HashData>> _rows;
    size_t _size;
    size_t _count;

    size_t h(const std::string& key) const noexcept {
        size_t hash = 0;
        for (size_t i = 0; i < key.length(); i++) {
            hash += (key[i]);
        }
        return hash % _size;
    }

public:
    HashTableC(size_t capacity = 15) : _size(capacity), _count(0) {
        _rows.resize(_size);
    }

    void insert(const std::string& key, const TValue& value) override {
        size_t hash = h(key);

        HashData* found = find_in_list(_rows[hash], key);

        if (found != nullptr) {
            throw std::logic_error("Such a key is already in the table");
        }
        _rows[hash].push_back(HashData(key, value));
        _count++;
    }

    void erase(const std::string& key) override {
        size_t hash = h(key);

        HashData* found = find_in_list(_rows[hash], key);

        if (found == nullptr) {
            throw std::logic_error("Key not found in the table");
        }

        size_t pos = 0;
        for (auto it = _rows[hash].begin(); it != _rows[hash].end(); ++it, ++pos) {
            if (it.get_node()->value.key == key) {
                _rows[hash].erase(pos);
                _count--;
                return;
            }
        }
    }
   
    HashData* find_in_list(List<HashData>& list, const std::string& key) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it.get_node()->value.key == key) {
                return &(it.get_node()->value);
            }
        }
        return nullptr;
    }

    TValue& found(const std::string& key) override {
        size_t hash = h(key);
        HashData* found = find_in_list(_rows[hash], key);
        if (found == nullptr) {
            throw std::logic_error("Key not found in the table");
        }

        return found->value;
    }

    bool is_empty() const noexcept override {
        return _count == 0;
    }

    void clear() {
        for (size_t i = 0; i < _size; i++) {
            _rows[i].clear();
        }
        _count = 0;
    }

    size_t size() const {
        return _count;
    }

    TValue& operator[](const std::string& key) {
        try {
            return found(key);
        }
        catch (const std::logic_error&) {
            insert(key, TValue());
            return found(key);
        }
    }

    const TValue& operator[](const std::string& key) const {
        return found(key);
    }
    void print_line(std::ostream& os, int key_width, int value_width) const {
        os << "+";
        for (int i = 0; i < key_width + 2; i++) os << "-";
        os << "+";
        for (int i = 0; i < value_width + 2; i++) os << "-";
        os << "+" << std::endl;
    }

    void print() override {
        const int KEY_WIDTH = 20;
        const int VALUE_WIDTH = 50;

        std::cout << "\n\t *** Hash Table (Chaining) ***\t\n" << std::endl;

        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);

        std::cout << "| " << std::left << std::setw(KEY_WIDTH) << "Key"
            << " | " << std::left << std::setw(VALUE_WIDTH) << "Value"
            << " |" << std::endl;

        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);

        for (size_t i = 0; i < _size; i++) {
            for (auto it = _rows[i].begin(); it != _rows[i].end(); ++it) {
                std::cout << "| " << std::left << std::setw(KEY_WIDTH) << it.get_node()->value.key
                    << " | " << std::left << std::setw(VALUE_WIDTH) << it.get_node()->value.value
                    << " |" << std::endl;
            }
        }

        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);
    }
};