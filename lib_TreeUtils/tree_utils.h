#pragma once
#include <utility>

template<typename TKey, typename TValue, typename Derived>
struct BaseNode {
    std::pair<TKey, TValue> _data;
    Derived* _left;     
    Derived* _right;
    Derived* _parent;

    BaseNode(const TKey& k, const TValue& v)
        : _data(k, v), _left(nullptr), _right(nullptr), _parent(nullptr) {}

    virtual ~BaseNode() = default;
};