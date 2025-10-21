#pragma once
#include <cstddef> 
#include <stdexcept>

template<class T>
class Stack {
    T* _data;
    int _size;      
    int _top;       

public:
    Stack(int size);
    Stack(const Stack& other);
    ~Stack() {
        delete[] _data;
    }

    void push(T val);
    void pop();
    T top() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear() noexcept;
    char peek() const;

};
bool check_of_brackets(const std::string& str);
void number_of_brackets(const std::string& str);


template<class T>
 Stack<T>::Stack(int size) : _size(size), _top(-1)
{
     if (size <= 0) {
         throw std::invalid_argument("Stack size must be positive");
     }
     _data = new T[_size];
}

 template<class T>
 Stack<T>::Stack(const Stack& other) : _size(other._size), _top(other._top) {
     _data = new T[_size];

     for (int i = 0; i <= _top; i++) {
         _data[i] = other._data[i];
     }
 }

template<class T>
void Stack<T>::push(T val) {
    if (is_full()) {
        throw std::logic_error("Stack is full");
    }
    _data[++_top] = val;
}

template<class T>
void Stack<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("Stack is empty");
    }
    --_top;
}

template<class T>
T Stack<T>::top() const {
    if (is_empty()) {
        throw std::logic_error("Stack is empty");
    }
    return _data[_top];
}

template<class T>
inline bool Stack<T>::is_full() const noexcept {
    return _top == _size - 1;  
}

template<class T>
inline bool Stack<T>::is_empty() const noexcept {
    return _top == -1;
}

template<class T>
void Stack<T>::clear() noexcept {
    _top = -1;
}



template<class T>
char Stack<T>::peek() const {
    if (is_empty()) {
        throw std::runtime_error("Stack is empty");
    }
    return _data[_top];
}