#pragma once
#define UNSORTED_ON_LIST_H

#include "../lib_List/list.h"  
#include "../lib_ITable/itable.h"
#include <iomanip>

template <class TKey, class TValue>
class UnsortedTableL : public ITable<TKey, TValue> {
private:
    List<TPair> _rows; 

public:
    UnsortedTableL() {}

    void insert(const TKey& key, const TValue& value) override { //++
        for (auto it = _rows.begin(); it != _rows.end(); ++it) {
            if ((*it).key == key) {
                throw std::logic_error("Such a key is already in the table");

            }
        }
        _rows.push_back({ key, value });
    }

    void erase(const TKey& key) override { //++
        if (_rows.is_empty()) {
            throw std::out_of_range("Index out of range");
        }
        for (auto it = _rows.begin(); it != _rows.end(); ++it) {
            if ((*it).key == key) {
                _rows.erase(it.get_node());
                return;
            }
        }
        throw std::out_of_range("Key not found in table");
    }

    TValue& found(const TKey& key) const override { //++
        for (auto it = _rows.begin(); it != _rows.end(); ++it) {
            if ((*it).key == key)
                return const_cast<TValue&>((*it).value);
        }
        throw std::logic_error("Key not found");
    }

    bool is_empty() const noexcept override {
        return _rows.is_empty();  
    }

    TValue& operator[](const TKey& key) {
        for (auto it = _rows.begin(); it != _rows.end(); ++it) {
            if ((*it).key == key)
                return (*it).value;
        }
        throw std::logic_error("Key not found");
    }

    const TValue& operator[](const TKey& key) const {
        for (auto it = _rows.begin(); it != _rows.end(); ++it) {
            if ((*it).key == key)
                return (*it).value;
        }
        throw std::logic_error("Key not found");
    }

    void print_line(std::ostream& os, int key_width, int value_width) {
        os << "+";
        for (int i = 0; i < key_width + 2; i++) os << "-";
        os << "+";
        for (int i = 0; i < value_width + 2; i++) os << "-";
        os << "+" << std::endl;
    }

    void print() override {//++
        const int KEY_WIDTH = 15;
        const int VALUE_WIDTH = 60;

        std::cout << "\n\t *** Table ***\t\n" << std::endl;

        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);

        std::cout << "| " << std::left << std::setw(KEY_WIDTH) << "Key"
            << " | " << std::left << std::setw(VALUE_WIDTH) << "Value" << " |" << std::endl;

        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);

        for (auto it = _rows.begin(); it != _rows.end(); ++it) {
            std::cout << "| " << std::left << std::setw(KEY_WIDTH) << (*it).key
                << " | " << std::left << std::setw(VALUE_WIDTH) << (*it).value << " |" << std::endl;
        }

        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);
    }
};