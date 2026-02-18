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
                _rows[i].value = value;
                return;
            }
        }
        _rows.push_back({ key, value });
    }

    void erase(const TKey& key) override { //++++
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key) {
                _rows[i] = _rows[_rows.size() - 1];
                _rows.pop_back();
                return;
            }
        }
    }

    TValue& found(const TKey& key) const override { //++++
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key)
                return const_cast<TValue&>(_rows[i].value);
        }
        throw std::logic_error("Key not found");
    }

    bool is_empty() const noexcept override {//+ 
        return _rows.size() == 0; 
    }

    int get_size() const noexcept override {//++ 
        return _rows.size(); 
    } 

    void reset() override {//+
        curr_pos = 0; 
    } 
    bool is_tab_ended() const override {//++
        return curr_pos >= _rows.size(); 
    }
    void go_next() override { //+
        curr_pos++; 
    }
    TKey get_key() const override { //++
        if (curr_pos >= _rows.size()) {
            throw std::out_of_range("Iterator is out of range in get_key()");
        }
        return _rows[curr_pos].key;
    }

    TValue get_value() const override { //++
        if (curr_pos >= _rows.size()) {
            throw std::out_of_range("Iterator is out of range in get_value()");
        }
        return _rows[curr_pos].value;
    }
    void print_line(std::ostream& os, int key_width, int value_width) {
        os << "+";
        for (int i = 0; i < key_width + 2; i++) os << "-";
        os << "+";
        for (int i = 0; i < value_width + 2; i++) os << "-";
        os << "+" << std::endl;
    }

    void print(std::ostream& os) override { //+
        const int KEY_WIDTH = 15;
        const int VALUE_WIDTH = 60;

        os << "\n\t *** Table ***\t\n" << std::endl;

        print_line(os, KEY_WIDTH, VALUE_WIDTH);

        for (reset(); !is_tab_ended(); go_next()) {
            os << "| " << std::left << std::setw(KEY_WIDTH) << get_key()
                << " | " << std::left << std::setw(VALUE_WIDTH) << get_value() << " |" << std::endl;
        }

        print_line(os, KEY_WIDTH, VALUE_WIDTH);

        reset();
    }
};
