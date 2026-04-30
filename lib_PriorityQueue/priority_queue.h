#pragma once
#include "../lib_heap/heap.h"
#include <stdexcept>

template<typename T>
struct PriorityElement {
    T _value;
    int _priority;
    int _number;

    bool operator<(const PriorityElement& other) const {
        if (_priority != other._priority) {
            return _priority < other._priority;  
        }
        return _number < other._number;  
    }

    bool operator>(const PriorityElement& other) const {
        if (_priority != other._priority) {
            return _priority > other._priority;
        }
        return _number > other._number;
    }
};

template<typename T>
class PriorityQueue {
    Heap<PriorityElement<T>> heap;
    int last_number = 1;

public:
    PriorityQueue();
    ~PriorityQueue() = default;

    void push(const T& value, int priority);
    T pop();


    bool is_empty() const;
    int size() const;
    void clear();
    void print() const;
};

template<typename T>
PriorityQueue<T>::PriorityQueue() : heap() {}

template<typename T>
void PriorityQueue<T>::push(const T& value, int priority) {
    PriorityElement<T> elem;
    elem._value = value;
    elem._priority = priority;
    elem._number = last_number++;

    heap.insert(elem);  
}

template<typename T>
T PriorityQueue<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("PriorityQueue is empty");
    }
    return heap.extract_min()._value; 
}


template<typename T>
bool PriorityQueue<T>::is_empty() const {
    return heap.is_empty();
}

template<typename T>
int PriorityQueue<T>::size() const {
    return heap.size();
}

template<typename T>
void PriorityQueue<T>::clear() {
    heap.clear();
    last_number = 1;
}

template<typename T>
void PriorityQueue<T>::print() const {
    const auto& data = heap.get_data();
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << "Priority: " << data[i]._priority
            << ", Value: " << data[i]._value
            << ", Number: " << data[i]._number << std::endl;
    }
}