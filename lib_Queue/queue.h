#pragma once
#include <cstddef> 
#include <stdexcept>

template<class T>
class Queue {
    T* _data;
    int _size;
    int _head = 0;
    int _tail = 0;
    int _count = 0;

public:
    
    Queue(int size);
    ~Queue() {
        delete[] _data;
    }

    void push(T val);
    void pop();
    T top() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear() noexcept;
};

template<class T>
Queue<T>::Queue(int size) : _size(size), _head(0), _tail(0) {
    if (size <= 0) {
        throw std::invalid_argument("Queue size must be positive");
    }
    _data = new T[_size];
}


template<class T>
void Queue<T>::push(T val) {
    if (is_full()) {
        throw std::invalid_argument("Queue is full");
    }
    _data[_tail] = val;
    _tail = (_tail + 1) % _size;
    _count++;
}

template<class T>
void Queue<T>::pop() {
    if (is_empty()) {
        throw std::invalid_argument("Queue is empty");
    }
    _head = (_head + 1) % _size;
    _count--;
}

template<class T>
inline T Queue<T>::top() const
{
    if(is_empty())
        throw std::invalid_argument("Queue is empty");
    return _data[_head];
}

template<class T>
inline bool Queue<T>::is_full() const noexcept {
    return _count == _size;
}


template<class T>
inline bool Queue<T>::is_empty() const noexcept {
    return _count==0;
    
}
template<class T>
inline void Queue<T>::clear() noexcept
{
    _head = 0;
    _tail = 0;
    _count = 0;
}