#ifndef UNSORTED_ON_ARR_H
#define UNSORTED_ON_ARR_H
#include "../lib_TVector/tvector.h"
#include "../lib_ITable/itable.h"


template <class TKey, class TValue>
class UnsortedTableM : public ITable<TKey, TValue> {
private:
    TVector<TPair> _rows;
    int curr_pos; 

public:
    UnsortedTableM() : curr_pos(0) {}

    void insert(const TKey& key, const TValue& value) override { //+
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key) {
                _rows[i].value = value;
                return;
            }
        }
        _rows.push_back({ key, value });
    }

    void erase(const TKey& key) override { //+
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key) {
                _rows[i] = _rows[_rows.size() - 1];
                _rows.pop_back();
                return;
            }
        }
    }

    TValue& found(const TKey& key) const override { // ++++
        for (int i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key) return const_cast<TValue&>(_rows[i].value);
        }
        throw std::logic_error("Key not found");
    }

    bool is_empty() const noexcept override { return _rows.size() == 0; }
    int get_size() const noexcept override { return _rows.size(); }

    void reset() override { curr_pos = 0; }
    bool is_tab_ended() const override { return curr_pos >= _rows.size(); }
    void go_next() override { curr_pos++; }
    TKey get_key() const override { return _rows[curr_pos].key; }
    TValue get_value() const override { return _rows[curr_pos].value; }
};

#endif