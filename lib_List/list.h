#pragma once 
#include <iostream>
#include <algorithm> 


template <typename T>
struct Node {

	T value;
	Node<T>* next;

public:
	Node(T value_, Node<T>* next_ = nullptr) : value(value_), next(next_) {}
};

template <typename T>
class List {
private: 
	Node<T>* _head;
	Node<T>* _tail;
	size_t _count;

public:
	List();
	~List();
	List(const List<T>& other);
	List<T>& operator=(const List<T>& other);
	Node<T>* head() const;
	Node<T>* tail() const;
	
	class Iterator {
		Node<T>* _current;
	public:
		Iterator() : _current(nullptr) {}
		Iterator(Node<T>* node) : _current(node) {}

		Iterator& operator=(const Iterator& other) {
			if (this != &other) {
				_current = other._current;
			}
			return *this;
		}

		Iterator& operator++() {
			if (_current != nullptr) {
				_current = _current->next;
			}
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		bool operator!=(const Iterator& other) const {
			return _current != other._current;
		}

		bool operator==(const Iterator& other) const {
			return _current == other._current;
		}

		T& operator*() {
			if (_current == nullptr) {
				throw std::invalid_argument("The end list");
			}
			return _current->value;
		}

		const T& operator*() const {
			if (_current == nullptr) {
				throw std::invalid_argument("The end list");
			}
			return _current->value;
		}

		T* operator->() {
			if (_current == nullptr) {
				throw std::invalid_argument("The end list");
			}
			return &(_current->value);
		}

		const T* operator->() const {
			if (_current == nullptr) {
				throw std::invalid_argument("The end list");
			}
			return &(_current->value);
		}
	};
	Iterator begin() const {
		return Iterator(_head);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}
	
	Node<T>* getHead() const { return _head; }
	size_t getCount() const { return _count; }
	
	void push_front(const T& value)noexcept;
	void push_back(const T& value)noexcept;
	void insert_at(size_t pos, const T& value);
	void insert_after(Node<T>* after_node, const T& value);
	void pop_front();
	void pop_back();
	void erase(size_t pos);
	void erase(Node<T>* node);
	bool is_empty() const { return _head == nullptr; }
	size_t size() const { return _count; }
	bool is_looped_the_first(const List<T>& list) const;
	bool is_looped_the_second(const List<T>& list) const;
	Node<T>* find_loop(const List<T>& list) const;
	void create_loop(int pos);

	Node<T>* get_node(size_t index) const {
		if (index >= _count) return nullptr;
		Node<T>* current = _head;
		for (size_t i = 0; i < index; ++i) {
			current = current->next;
		}
		return current;
	}

};


template<typename T>
List<T>::List()
{
	_head = nullptr;
	_tail = nullptr;
	_count = 0;
}

template<typename T>
 List<T>::~List()
{
	 if (_head == nullptr) {
		 return;
	 }

	 Node<T>* slow = _head;
	 Node<T>* fast = _head;
	 Node<T>* loop_start = nullptr;

	 while (fast != nullptr && fast->next != nullptr) {
		 slow = slow->next;
		 fast = fast->next->next;
		 if (slow == fast) {
			 loop_start = _head;
			 while (loop_start != slow) {
				 loop_start = loop_start->next;
				 slow = slow->next;
			 }
			 Node<T>* breaker = loop_start;
			 while (breaker->next != loop_start) {
				 breaker = breaker->next;
			 }
			 breaker->next = nullptr;
			 break; 
		 }
	 }

	 Node<T>* current = _head;
	 while (current != nullptr) {
		 Node<T>* next_node = current->next;
		 delete current;
		 current = next_node;
	 }
	 _head = nullptr;
	 _tail = nullptr;
	 _count = 0;
}
 template<typename T>
 List<T>::List(const List<T>& other) : _head(nullptr), _tail(nullptr), _count(0) {
	 if (other.is_empty()) {
		 return;
	 }
	 const Node<T>* slow = other.getHead();
	 const Node<T>* fast = other.getHead();

	 Node<T>* loop_start = nullptr;
	 bool has_loop = false;

	 while (fast != nullptr && fast->next != nullptr) {
		 slow = slow->next;
		 fast = fast->next->next;

		 if (slow == fast) {
			 has_loop = true;
			 slow = other.getHead();
			 while (slow != fast) {
				 slow = slow->next;
				 fast = fast->next;
			 }
			 loop_start = slow;
			 break;
		 }
	 }

	 const Node<T>* current_other = other.getHead();
	 Node<T>* copied_loop_start = nullptr;

	 while (current_other != nullptr) {
		 Node<T>* new_node = new Node<T>(current_other->value);

		 if (_head == nullptr) {
			 _head = new_node;
			 _tail = new_node;
		 }
		 else {
			 _tail->next = new_node;
			 _tail = new_node;
		 }

		 if (has_loop && current_other == loop_start) {
			 copied_loop_start = new_node;
		 }

		 _count++;
		 current_other = current_other->next;

		 if (has_loop && current_other == loop_start) {
			 _tail->next = copied_loop_start;
			 break;
		 }
	 }
 }

 template<typename T>
 List<T>& List<T>::operator=(const List<T>& other) {
	 List<T> temp(other); 
	 std::swap(_head, temp._head);
	 std::swap(_tail, temp._tail);
	 std::swap(_count, temp._count);
	 return *this;
 }

 template<typename T>
  Node<T>* List<T>::head() const{
	 try {
		 if (_head == nullptr) {
			 return nullptr;
		 }
		 return _head;
	 } catch (const std::exception& e) {
		 throw; 
	 }
 }

 template<typename T>
 Node<T>* List<T>::tail() const
 {
	 return _tail;
 }

template <class T>
void List<T>::push_front(const T& value) noexcept {
	Node<T>* node = new Node<T>(value);
	if (is_empty()) {
		_head = node;
		_tail = node;
	}
	else {
		node->next = _head;
		_head = node;
	}
	_count++; 
}

template <class T>
void List<T>::push_back(const T& value) noexcept {
	Node<T>* node = new Node<T>(value);
	if (is_empty()) {
		_head = node;
		_tail = node;
	}
	else {
		_tail->next = node;
		_tail = node;
	}
	_count++;
}

template <typename T>
void List<T>::insert_after(Node<T>* node, const T& value) {
	if (node == nullptr) {
		throw std::invalid_argument("Node cannot be null");
	}

	Node<T>* new_node = new Node<T>(value, node->next);
	node->next = new_node;

	if (node == _tail) {
		_tail = new_node;
	}

	_count++;
}

template<typename T>
 void List<T>::pop_front(){
	 if (is_empty())
		 throw std::logic_error("Deletion cannot be performed, the sheet is empty");
	 Node<T>* cur = _head;
	 _head = cur->next;
	 delete cur;
	 _count--; 
	 
}

 template <typename T>
 void List<T>::insert_at(size_t pos, const T& value) {
	 if (pos > _count) {
		 throw std::out_of_range("Position out of range");
	 }

	 if (pos == 0) {
		 push_front(value);
		 return;
	 }

	 if (pos == _count) {
		 push_back(value);
		 return;
	 }

	 Node<T>* current = _head;
	 for (size_t i = 0; i < pos - 1; i++) {
		 current = current->next;
	 }

	 insert_after(current, value);
 }

 template<typename T>
 void List<T>::pop_back() {
	 if (is_empty()) {
		 throw std::logic_error("Cannot pop from empty list");
	 }

	 if (_head == _tail) { 
		 delete _head;
		 _head = nullptr;
		 _tail = nullptr;
	 }
	 else {
		 Node<T>* current = _head;
		 while (current->next != _tail) {
			 current = current->next;
		 }

		 delete _tail;
		 _tail = current;
		 _tail->next = nullptr;
	 }

	 _count--;
 }

template<typename T>
void List<T>::erase(size_t pos){
	if(is_empty())
		throw std::logic_error("Deletion cannot be performed, the sheet is empty");
	if (pos == 0) {
		pop_front();
		return;
	}
	Node<T>* cur = _head;
	for (int i = 0; i < pos - 1; i++)
	{
		cur = cur->next;
	}

	Node<T>* to_delete = cur->next;
	cur->next = to_delete->next;
	if (to_delete == _tail)
		_tail = cur;
	delete to_delete;
	_count--;
}

template<typename T>
void List<T>::erase(Node<T>* node)
{
	if (node == nullptr || is_empty()) {
		throw std::logic_error("Node cannot be null or list empty");
	}
	if (node == _head) {
		pop_front();
		return;
	}

	Node<T>* cur = _head;
	while (cur != nullptr && cur->next != node) {
		cur = cur->next;
	}
	if (cur == nullptr) {
		throw std::logic_error("Node not found in list");
	}

	cur->next = node->next;

	if (node == _tail) {
		_tail = cur;
	}

	delete node;
	_count--;
}

template<typename T>
void List<T>::create_loop(int pos) {
	if (pos < 0 || pos >= _count) return;

	Node<T>* current = _head;
	Node<T>* loop_node = nullptr;
	Node<T>* last_node = nullptr;

	for (int i = 0; current != nullptr; i++) {
		if (i == pos) {
			loop_node = current;
		}
		last_node = current;
		current = current->next;
	}

	if (loop_node != nullptr && last_node != nullptr) {
		last_node->next = loop_node;
	}
}

template<typename T>
bool List<T>::is_looped_the_first(const List<T>& list) const {
	if (list.is_empty())
		throw std::logic_error("Cannot check for loop in empty list");

	Node<T>* slow = list.getHead();
	Node<T>* fast = list.getHead();

	while (fast != nullptr && fast->next != nullptr) {
		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast) {
			return true;
		}
	}

	return false;
}

template<typename T>
bool List<T>::is_looped_the_second(const List<T>& list) const {
	if (list.is_empty())
		throw std::logic_error("Cannot check for loop in empty list");

	Node<T>* slow = list.getHead();
	Node<T>* fast = list.getHead();

	while (fast != nullptr && fast->next != nullptr) {
		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast) {
			return true; 
		}
	}
	return false; 
}
template<typename T>
Node<T>* List<T>::find_loop(const List<T>& list) const {
	if (list.is_empty())
		throw std::logic_error("Cannot check for loop in empty list");

	Node<T>* slow = list.getHead();
	Node<T>* fast = list.getHead();

	while (fast != nullptr && fast->next != nullptr) {
		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast) {
			break;
		}
	}

	if (fast == nullptr || fast->next == nullptr) {
		return nullptr;
	}

	slow = list.getHead();
	while (slow != fast) {
		slow = slow->next;
		fast = fast->next;
	}

	return slow; 
}
