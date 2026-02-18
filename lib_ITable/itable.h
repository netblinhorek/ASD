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
    virtual TValue& found(const TKey& key) const = 0;
    virtual bool is_empty() const noexcept = 0;
    virtual int get_size() const noexcept = 0;

    virtual void reset() = 0;
    virtual bool is_tab_ended() const = 0;
    virtual void go_next() = 0;
    virtual TKey get_key() const = 0;
    virtual TValue get_value() const = 0;

    virtual void print(std::ostream& os = std::cout) = 0;
};
#endif