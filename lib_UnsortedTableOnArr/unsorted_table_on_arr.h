#pragma once
#define UNSORTED_ON_ARR_H

#include "../lib_TVector/tvector.h"
#include "../lib_ITable/itable.h"
#include<iomanip>

template <class TKey, class TValue>
class UnsortedTableM : public ITable<TKey, TValue> {
private:
    TVector<TPair> _rows;
    int curr_pos;

public:
    UnsortedTableM() : curr_pos(0) {}

    void insert(const TKey& key, const TValue& value) override { //++
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key) {
                throw std::logic_error("Such a key is already in the table");
            }
        }
        _rows.push_back({ key, value });
    }

    void erase(const TKey& key) override {
        if (_rows.is_empty()) {
            throw std::out_of_range("Table is empty");
        }

        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key) {
                _rows[i] = _rows[_rows.size() - 1];
                _rows.pop_back();
                return;
            }
        }

        throw std::out_of_range("Key not found in table");
    }

    TValue& found(const TKey& key)  override { //++++
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key)
                return _rows[i].value;
        }
        throw std::logic_error("Key not found");
    }

    bool is_empty() const noexcept override {//+ 
        return _rows.size() == 0; 
    }

    TValue& operator[](const TKey& key) {
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key)
                return _rows[i].value;
        }
        throw std::logic_error("Key not found");
    }

    const TValue& operator[](const TKey& key) const {
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key)
                return _rows[i].value;
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

    void print() override { //++
        const int KEY_WIDTH = 15;
        const int VALUE_WIDTH = 60;

        std::cout << "\n\t *** Table ***\t\n" << std::endl;

        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);

        std::cout << "| " << std::left << std::setw(KEY_WIDTH) << "Key"
            << " | " << std::left << std::setw(VALUE_WIDTH) << "Value" << " |" << std::endl;

        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);

        for (size_t i = 0; i < _rows.size(); i++) {
            std::cout << "| " << std::left << std::setw(KEY_WIDTH) << _rows[i].key
                << " | " << std::left << std::setw(VALUE_WIDTH) << _rows[i].value << " |" << std::endl;
        }

        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);

    }
};
