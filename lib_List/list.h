#pragma once 
#include <iostream>


template <typename T>
struct Node {

	T value;
	Node<T>* next;

public:
	Node(T value_, Node<T>* next_ = nullptr) : value(value_), next(next_) {}
};

template <typename T>
class List {
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
	 while (!is_empty())
		 pop_front();
}
 template<typename T>
 List<T>::List(const List<T>& other) : _head(nullptr), _tail(nullptr), _count(0) {

	 const Node<T>* current = other._head;
	 Node<T>* prev = nullptr;

	 while (current != nullptr) {
		 Node<T>* new_node = new Node<T>(current->value);

		 if (_head == nullptr) {
			 _head = new_node;
			 _tail = new_node;
		 }
		 else {
			 prev->next = new_node;
			 _tail = new_node;
		 }

		 prev = new_node;
		 current = current->next;
		 _count++;
	 }
 }

 template<typename T>
 List<T>& List<T>::operator=(const List<T>& other) {
	 if (this == &other) { 
		 return *this;
	 }

	 while (!is_empty()) {
		 pop_front();
	 }

	 const Node<T>* current_other = other._head;
	 while (current_other != nullptr) {
		 push_back(current_other->value);
		 current_other = current_other->next;
	 }

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
