#pragma once
#include <cstddef> 
#include <stdexcept>
#include <algorithm>  

template<class T>
class Queue {
    T* _data;
    int _size;
    int _head = 0;
    int _count = 0;

public:
    Queue(int size = 100);
    ~Queue();

    void grow();
    void push(T val);
    void pop();
    T head() const;
    T tail() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear() noexcept;
};

template<class T>
Queue<T>::Queue(int size) : _size(size), _head(0), _count(0) {
    if (size <= 0) {
        throw std::invalid_argument("Queue size must be positive");
    }
    _data = new T[_size];

    std::fill(_data, _data + _size, T());
}

template<class T>
Queue<T>::~Queue() {
    if (_data != nullptr) {
        delete[] _data;
        _data = nullptr;
    }
}

template<class T>
void Queue<T>::grow() {
    const int new_size = _size * 2;
    T* new_data = new T[new_size];
    for (int i = 0; i < _count; ++i) {
        new_data[i] = _data[(_head + i) % _size];
    }
    delete[] _data;
    _data = new_data;
    _size = new_size;
    _head = 0;
}

template<class T>
void Queue<T>::push(T val) {
    if (is_full()) {
        grow();
    }
    int tail_index = (_head + _count) % _size;
    _data[tail_index] = val;
    _count++;
}

template<class T>
void Queue<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("Queue is empty");
    }
    _head = (_head + 1) % _size;
    _count--;
}

template<class T>
T Queue<T>::head() const {
    if (is_empty()) {
        throw std::logic_error("Queue is empty");
    }
    return _data[_head];
}

template<class T>
T Queue<T>::tail() const {
    if (is_empty()) {
        throw std::logic_error("Queue is empty");
    }
    int tail_index = (_head + _count - 1) % _size;
    return _data[tail_index];
}

template<class T>
bool Queue<T>::is_full() const noexcept {
    return _count == _size;
}

template<class T>
bool Queue<T>::is_empty() const noexcept {
    return _count == 0;
}

template<class T>
void Queue<T>::clear() noexcept {
    _head = 0;
    _count = 0;
}