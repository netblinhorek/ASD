#pragma once
#define UNSORTED_ON_ARR_H

#include "../lib_TVector/tvector.h"
#include "../lib_ITable/itable.h"
#include <iomanip>
#include <utility> 

template <class TKey, class TValue>
class SortedTableM : public ITable<TKey, TValue> {
private:
    TVector<TPair> _rows;
    int curr_pos;

    std::pair<int, bool> binary_search_pos(const TKey& key) const {
        if (_rows.is_empty()) {
            return { 0, false };
        }

        int left = 0;
        int right = static_cast<int>(_rows.size() - 1);
        int pos = 0;

        while (left <= right) {
            int mid = (left + right) / 2;

            if (_rows[mid].key == key) {
                return { mid, true }; 
            }
            else if (_rows[mid].key < key) {
                left = mid + 1;
                pos = left; 
            }
            else {
                right = mid - 1;
                pos = mid; 
            }
        }
        return { pos, false };
    }

public:

    SortedTableM() : curr_pos(0) {}

    void insert(const TKey& key, const TValue& value) override {
        auto [pos, found] = binary_search_pos(key);
        if (found) {
            throw std::logic_error("Such a key is already in the table");
        }
        _rows.insert({ key, value }, pos);
    }

    void erase(const TKey& key) override {
        auto [pos, found] = binary_search_pos(key);
        if (!found) {
            throw std::out_of_range("Key not found");
        }
        _rows.erase(pos);
    }

    TValue& found(const TKey& key) override {
        auto [pos, found] = binary_search_pos(key);
        if (!found) {
            throw std::logic_error("Key not found");
        }
        return _rows[pos].value;
    }

    bool is_empty() const noexcept override {
        return _rows.size() == 0;
    }

    TValue& operator[](const TKey& key) {
        
        auto [pos, found] = binary_search_pos(key);
        if (!found) {
            throw std::logic_error("Key not found");
        }
        return _rows[pos].value;
    }

    const TValue& operator[](const TKey& key) const {
        auto [pos, found] = binary_search_pos(key);
        if (!found) {
            throw std::logic_error("Key not found");
        }
        return _rows[pos].value;
    }
    const TKey& get_key(size_t index) const {
        if (index >= _rows.size()) throw std::out_of_range("Index out of range");
        return _rows[index].key;
    }
    size_t size() const {
        return _rows.size();
    }
    void print_line(std::ostream& os, int key_width, int value_width) {
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

        for (size_t i = 0; i < _rows.size(); i++) {
            std::cout << "| " << std::left << std::setw(KEY_WIDTH) << _rows[i].key
                << " | " << std::left << std::setw(VALUE_WIDTH) << _rows[i].value << " |" << std::endl;
        }

        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);
    }
};