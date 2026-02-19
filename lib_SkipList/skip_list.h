#pragma once
#include "../lib_TVector/tvector.h"

template <typename T>
struct Node {
    T value;
    Node<T>** _next;
};

template <class TKey, class TValue>
class SkipList {
    size_t _Max_LVLs;
    size_t _lvl;
    List <Node*> _heads;
public:
    SkipList();
    ~SkipList();
    void insert(const TKey&, const TValue&);
    void print() const noexcept;
protected:
    size_t  _coin() const noexcept;
    Node* find_nearest(const TKey&) const noexcept;
};

template<class TKey, class TValue>
SkipList<TKey, TValue>::SkipList() {
    head = new Node(T(), _Max_LVLs);
}

template<class TKey, class TValue>
SkipList<TKey, TValue>::~SkipList() {
    Node* current = _heads->next[0];
    while (current) {
        Node* next = current->next[0];
        delete current;
        current = next;
    }
    delete _heads;
}


template<class TKey, class TValue>
size_t SkipList<TKey, TValue>::_coin() const noexcept {
    bool flag = true;
    do {
        int tmp = rand() % 100;
        if (0 <= tmp <= 50) {
            _lvl++;
            flag = true;
        }
        else {
            flag = false;
        }
        while (true)
    }
    return _lvl;
}

template<class TKey, class TValue>
void SkipList<TKey, TValue>::insert(const TKey&, const TValue&) {
    Node* current = _heads->next[0];
}

template<class TKey, class TValue>
void SkipList<TKey, TValue>::print() const noexcept
{
    for (int i = 0; ) {
    
    
    }

}

//template<class TKey, class TValue>
//Node* SkipList<TKey, TValue>::find_nearest(const TKey&) const noexcept
//{
//}
