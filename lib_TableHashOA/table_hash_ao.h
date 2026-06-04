#pragma once

#include "../lib_ITable/itable.h"
#include "../lib_TVector/tvector.h"
#include <iomanip>
#include <stdexcept>
#include <string>
#include <iostream>
#include <algorithm>

enum class HashDataStatus {
    empty,
    busy,
    deleted
};

template <class TKey, class TValue>
struct HashData {
    HashDataStatus _state;
    TKey key;
    TValue value;

    HashData() : _state(HashDataStatus::empty), key(), value() {}
    HashData(const TKey& k, const TValue& v, HashDataStatus state = HashDataStatus::busy)
        : _state(state), key(k), value(v) {
    }
};

template <class TKey, class TValue>
class HashTableAO : public ITable<std::string, TValue> {
private:
    TVector<HashData<TKey, TValue>> _rows;
    size_t _size;
    size_t _count;
    size_t _shift;

    size_t h(const std::string& key) const noexcept {
        size_t hash = 0;
        for (unsigned char c : key) {
            hash = (hash * 31 + c) % _size;
        }
        return hash;
    }

    size_t hh(size_t hash) const noexcept {
        return (hash + _shift) % _size;
    }

    void update_shift() {
        _shift = 1;
        for (size_t i = std::max(2, (int)(_size / 15)); i < _size; i++) {
            if (is_simple(i, _size)) {
                _shift = i;
                break;
            }
        }
    }

    void rehash(size_t new_capacity) {
        TVector<HashData<TKey, TValue>> old_rows = _rows;
        size_t old_size = _size;

        _size = new_capacity;
        _rows.clear();
        _rows.resize(_size);
        update_shift();
        _count = 0;

        for (size_t i = 0; i < old_size; i++) {
            if (old_rows[i]._state == HashDataStatus::busy) {
                insert(old_rows[i].key, old_rows[i].value);
            }
        }
    }

public:
    HashTableAO(size_t capacity = 15) : _size(capacity), _count(0), _shift(1) {
        _rows.resize(_size);
        update_shift();
    }

    bool is_simple(size_t a, size_t b) {
        while (b != 0) {
            size_t tmp = b;
            b = a % b;
            a = tmp;
        }
        return a == 1;
    }

    void insert(const std::string& key, const TValue& value) override {
        // ƒл€ открытой адресации порог заполнени€ 70% критичен дл€ сохранени€ скорости O(1)
        if (_count >= _size * 0.7) {
            rehash(_size * 2 + 1);
        }

        size_t hash = h(key);
        size_t first_hash = hash;
        int first_deleted_idx = -1;

        while (1) {
            if (_rows[hash]._state == HashDataStatus::empty) {
                // ≈сли по пути встретили удаленную €чейку, пишем в нее, иначе в текущую пустую
                size_t target_idx = (first_deleted_idx != -1) ? first_deleted_idx : hash;
                _rows[target_idx] = HashData<TKey, TValue>(key, value, HashDataStatus::busy);
                _count++;
                return;
            }

            if (_rows[hash]._state == HashDataStatus::deleted) {
                if (first_deleted_idx == -1) {
                    first_deleted_idx = static_cast<int>(hash);
                }
            }
            else if (_rows[hash]._state == HashDataStatus::busy && _rows[hash].key == key) {
                throw std::logic_error("Such a key is already in the table");
            }

            hash = hh(hash);
            if (first_hash == hash) {
                // ≈сли обошли круг, но нашли удаленное место
                if (first_deleted_idx != -1) {
                    _rows[first_deleted_idx] = HashData<TKey, TValue>(key, value, HashDataStatus::busy);
                    _count++;
                    return;
                }
                throw std::logic_error("Hash table is full");
            }
        }
    }

    bool is_full() const {
        return _count >= _size;
    }

    void erase(const std::string& key) override {
        size_t hash = h(key);
        size_t first_hash = hash;

        while (1) {
            if (_rows[hash]._state == HashDataStatus::empty) {
                throw std::logic_error("Key not found in the table");
            }
            if (_rows[hash]._state == HashDataStatus::busy && _rows[hash].key == key) {
                _rows[hash]._state = HashDataStatus::deleted;
                _count--;
                return;
            }
            hash = hh(hash);
            if (first_hash == hash) {
                throw std::logic_error("Key not found in the table");
            }
        }
    }

    TValue& found(const std::string& key) override {
        size_t hash = h(key);
        size_t first_hash = hash;

        while (1) {
            if (_rows[hash]._state == HashDataStatus::empty) {
                throw std::logic_error("Key not found in the table");
            }
            if (_rows[hash]._state == HashDataStatus::busy && _rows[hash].key == key) {
                return _rows[hash].value;
            }
            hash = hh(hash);
            if (first_hash == hash) {
                throw std::logic_error("Key not found in the table");
            }
        }
    }

    bool is_empty() const noexcept override {
        return _count == 0;
    }

    void clear() {
        for (size_t i = 0; i < _size; i++) {
            _rows[i]._state = HashDataStatus::empty;
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
        size_t hash = h(key);
        size_t first_hash = hash;

        while (1) {
            if (_rows[hash]._state == HashDataStatus::empty) {
                throw std::logic_error("Key not found in the table");
            }
            if (_rows[hash]._state == HashDataStatus::busy && _rows[hash].key == key) {
                return _rows[hash].value;
            }
            hash = hh(hash);
            if (first_hash == hash) {
                throw std::logic_error("Key not found in the table");
            }
        }
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

        std::cout << "\n\t *** Table ***\t\n" << std::endl;
        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);

        std::cout << "| " << std::left << std::setw(KEY_WIDTH) << "Key"
            << " | " << std::left << std::setw(VALUE_WIDTH) << "Value"
            << " |" << std::endl;

        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);

        for (size_t i = 0; i < _size; i++) {
            if (_rows[i]._state == HashDataStatus::busy) {
                std::cout << "| " << std::left << std::setw(KEY_WIDTH) << _rows[i].key
                    << " | " << std::left << std::setw(VALUE_WIDTH) << _rows[i].value
                    << " |" << std::endl;
            }
        }
        print_line(std::cout, KEY_WIDTH, VALUE_WIDTH);
    }
};