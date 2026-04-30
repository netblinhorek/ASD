#pragma once

#include "../lib_TVector/tvector.h"      
#include "../lib_TableHashC/table_hash_c.h" 
#include <utility>
#include <string>

template <class TValue>
HashTableC<std::string, TValue> merge_dictionaries(
    const TVector<std::pair<std::string, TValue>>& vec1,
    const TVector<std::pair<std::string, TValue>>& vec2)
{
    HashTableC<std::string, TValue> table(vec1.size() + vec2.size());

    for (size_t i = 0; i < vec1.size(); ++i) {
        const std::string& current_key = vec1[i].first;
        const TValue& current_value = vec1[i].second;

        bool key_exists = true;
        try {
            table.found(current_key);
        }
        catch (const std::logic_error&) {
            key_exists = false;
        }

        if (!key_exists) {
            table.insert(current_key, current_value);
        }
    }

    for (size_t i = 0; i < vec2.size(); ++i) {
        const std::string& current_key = vec2[i].first;
        const TValue& current_value = vec2[i].second;

        bool key_exists = true;
        try {
            table.found(current_key);
        }
        catch (const std::logic_error&) {
            key_exists = false;
        }

        if (!key_exists) {
            table.insert(current_key, current_value);
        }
    }

    return table;
}