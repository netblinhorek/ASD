#pragma once

#include "../lib_TableHashC/table_hash_c.h"
#include "../lib_TableHashOA/table_hash_ao.h"

namespace bench {

template <class HashTable>
struct HashTableFactory;

template <class TValue>
struct HashTableFactory<HashTableC<std::string, TValue>> {
    static HashTableC<std::string, TValue> make(size_t capacity) {
        return HashTableC<std::string, TValue>(capacity);
    }
};

template <class TValue>
struct HashTableFactory<HashTableAO<std::string, TValue>> {
    static HashTableAO<std::string, TValue> make(size_t capacity) {
        return HashTableAO<std::string, TValue>(capacity);
    }
};

}  // namespace bench
