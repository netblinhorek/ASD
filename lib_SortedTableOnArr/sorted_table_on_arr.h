#pragma once
#define UNSORTED_ON_ARR_H

#include "../lib_TVector/tvector.h"
#include "../lib_ITable/itable.h"
#include<iomanip>

template <class TKey, class TValue>
class SortedTableM : public ITable<TKey, TValue> {
private:
    TVector<TPair> _rows;
    int curr_pos;

public:
    SortedTableM() : curr_pos(0) {}

    void insert(const TKey& key, const TValue& value) override { //+
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key) {
                throw std::logic_error("Such a key is already in the table");
            }
        }

        int pos_insert = 0;

        if (_rows.is_empty() == false) {
            int left = 0;
            int right = _rows.size() - 1;

            while (left <= right) {
                int mid = (left + right) / 2;

                if (_rows[mid].key < key) {
                    left = mid + 1;
                    pos_insert = left;
                }
                else {
                    right = mid - 1;
                    pos_insert = mid;
                }
            }
        }

        _rows.insert({ key, value }, pos_insert);
    }

    void erase(const TKey& key) override { //++++
        int pos_insert = 0;
        if (_rows.is_empty()) {
            throw std::out_of_range("Index out of range");
        }
        else{
            int left = 0;
            int right = _rows.size() - 1;

            while (left <= right) {
                int mid = (left + right) / 2;

                if (_rows[mid].key < key) {
                    left = mid + 1;
                    pos_insert = left;
                }
                else {
                    right = mid - 1;
                    pos_insert = mid;
                }
            }
        }

        _rows.erase(pos_insert);

    }


    TValue& found(const TKey& key) const override {
        int left = 0;
        int right = _rows.size() - 1;

        while (left <= right) {
            int mid = (left + right) / 2;

            if (_rows[mid].key == key) {
                return const_cast<TValue&>(_rows[mid].value);
            }
            else if (_rows[mid].key < key) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        throw std::logic_error("Key not found");
    }

    bool is_empty() const noexcept override {//+ 
        return _rows.size() == 0;
    }

    TValue& operator[](const TKey& key) {
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key)
                return const_cast<TValue&>(_rows[i].value);
        }
        throw std::logic_error("Key not found");
    }

    const TValue& operator[](const TKey& key) const {
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key)
                return const_cast<TValue&>(_rows[i].value);
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
