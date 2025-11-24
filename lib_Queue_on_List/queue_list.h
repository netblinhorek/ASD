#pragma once 
#include <iostream>
#include <algorithm> 
#include "../lib_List/list.h" 

template <typename T>
class Queue_List {
private:
	List<T> _list;

public:
	Queue_List() = default;

	void push_back_queue(const T& value) {
		_list.push_back(value);
	}

	void pop_front_queue() {
		if (_list.is_empty()) {
			throw std::invalid_argument("Queue is empty");
		}
		_list.pop_front();
	}

	T& front_queue() {
		if (_list.is_empty()) {
			throw std::invalid_argument("Queue is empty");
		}
		return *(_list.begin());
	}

	bool is_empty_queue() const {
		return _list.is_empty();
	}

	size_t size_queue() const {
		return _list.size();
	}

	Node<T>* head() const {
		if (_list.is_empty()) {
			return nullptr;
		}
		return _list.get_head();
	}

	Node<T>* tail() const {
		if (_list.is_empty()) {
			return nullptr;
		}
		return _list.tail();
	}

};