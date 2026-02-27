#ifndef ITABLE_H
#define ITABLE_H
#include <iostream>

template <class TKey, class TValue>
class ITable {
protected:
    struct TPair {
        TKey key;
        TValue value; 
    };
public:
    virtual ~ITable() {} 

    virtual void insert(const TKey& key, const TValue& value) = 0;
    virtual void erase(const TKey& key) = 0;
    virtual TValue& found(const TKey& key)  = 0;
    virtual bool is_empty() const noexcept = 0;


    virtual void print() = 0;
};
#endif