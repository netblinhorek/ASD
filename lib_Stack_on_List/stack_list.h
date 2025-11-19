#pragma once 
#include <iostream>
#include <algorithm> 
#include "../lib_List/list.h" 

template <typename T>
class Stack_List {
private:
	List<T> _list;

public:
	Stack_List() = default;

	void push(const T& value) {
		_list.push_front(value);
	}

	void pop() {
		if (_list.is_empty()) {
			throw std::invalid_argument("Stack is empty");
		}
		_list.pop_front();
	}

	T& top() {
		if (_list.is_empty()) {
			throw std::invalid_argument("Stack is empty");
		}
		return *(_list.begin());
	}

	bool is_empty() const {
		return _list.is_empty();
	}

	size_t size() const {
		return _list.size();
	}
};