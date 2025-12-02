#include <iostream>


template <typename T>
struct Node {
	T value;
	Node<T>* next;
	Node<T>* prev;
public:
	Node(T value_, Node<T>* next_ = nullptr, Node<T>* prev_ = nullptr) 
		: value(value_), next(next_), prev(prev_) {}
};

template <typename T>
class Double_List {
	Node<T>* _head;
	Node<T>* _tail;
	size_t _count;

public:
	Double_List();
	~Double_List();
	Double_List(const Double_List<T>& other);
	Node<T>* head();
	Node<T>* tail();
	size_t count() const;
	
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
		bool operator==(const Iterator& other) const {
			return _current == other._current;
		}
		Iterator& operator++() {
			if (_current == nullptr) {
				throw std::invalid_argument("The end list");
			}
			else {
				_current = _current->next;
			}
			return *this;
		};

		Iterator operator++(int) {
			Iterator temp = *this;
			++(*this);
			return temp;
		}
		Iterator& operator--() { 
			if (_current == nullptr) {
				throw std::invalid_argument("Cannot decrement end iterator");
			}
			if (_current->prev == nullptr) {
				throw std::invalid_argument("Cannot decrement begin iterator");
			}
			_current = _current->prev;
			return *this;
		}
		Iterator operator--(int) {
			Iterator tmp = *this;
			--(*this);
			return tmp;
		}
		Iterator& operator-=(int size) {
			for (int i = 0; i < size; ++i) {
				(*this)--;
			}
			return *this;
		}
		bool operator!=(const Iterator& other) {
			return !(_current == other._current);
		}
		T& operator*() {
			if (_current == nullptr) {
				throw std::invalid_argument("The end Double_List");
			}
			return _current->value;
		}
	};
	Iterator begin() {
		return Iterator(_head);
	}

	Iterator end() {
		return Iterator(nullptr);
	}
	bool is_empty();
	void push_front(const T& value)noexcept;
	void push_back(const T& value)noexcept;
	void insert_at(size_t pos, const T& value);
	void insert_after(Node<T>* after_node, const T& value);
	void insert_before(Node<T>* before_node, const T& value);
	void pop_front();
	void pop_back();
	void erase_at(size_t pos);
	void erase(Node<T>* node);

};


template<typename T>
Double_List<T>::Double_List()
{
	_head = nullptr;
	_tail = nullptr;
	_count = 0;
}

template<typename T>
 Double_List<T>::~Double_List()
{
	 while (!is_empty()) {
		 pop_front();
	 }
}

 template<typename T>
 Double_List<T>::Double_List(const Double_List<T>& other): _head(nullptr), _tail(nullptr), _count(0)
 {
	 Node<T>* current = other._head;
	 while (current != nullptr) {
		 push_back(current->value);
		 current = current->next;
	 }
 }

 template<typename T>
 Node<T>* Double_List<T>::head()
 {
	 return _head;
 }

 template<typename T>
 Node<T>* Double_List<T>::tail()
 {
	 return _tail;
 }

template<typename T>
size_t Double_List<T>::count() const
{
	return _count;
}


template <typename T>
bool Double_List<T>::is_empty() {
	return _head == nullptr;
}

template <typename T>
void Double_List<T>::push_front(const T& value) noexcept {
	Node<T>* new_node = new Node<T>(value, _head, nullptr);

	if (_head != nullptr) {
		_head->prev = new_node;
	}
	_head = new_node;

	if (_tail == nullptr) {
		_tail = new_node;
	}

	_count++;
}

template <typename T>
void Double_List<T>::push_back(const T& value) noexcept {
	Node<T>* new_node = new Node<T>(value, nullptr, _tail);

	if (_tail != nullptr) {
		_tail->next = new_node;
	}
	_tail = new_node;

	if (_head == nullptr) {
		_head = new_node;
	}

	_count++;
}

template <typename T>
void Double_List<T>::insert_after(Node<T>* node, const T& value) {
	if (node == nullptr) {
		throw std::invalid_argument("Node cannot be null");
	}

	Node<T>* new_node = new Node<T>(value, node->next, node);

	if (node->next != nullptr) {
		node->next->prev = new_node;
	}
	node->next = new_node;

	if (node == _tail) {
		_tail = new_node;
	}

	_count++;
}

template <typename T>
void Double_List<T>::insert_before(Node<T>* node, const T& value) {
	if (node == nullptr) {
		throw std::invalid_argument("Node cannot be null");
	}

	Node<T>* new_node = new Node<T>(value, node, node->prev);

	if (node->prev != nullptr) {
		node->prev->next = new_node;
	}
	else {
		_head = new_node;
	}
	node->prev = new_node;

	_count++;
}

template<typename T>
void Double_List<T>::pop_front() {
	if (is_empty()) {
		throw std::logic_error("Cannot pop from empty list");
	}

	if (_head == _tail) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
		_count = 0;
		return;
	}

	Node<T>* to_delete = _head;
	_head = _head->next;

	if (_head != nullptr) {
		_head->prev = nullptr;
	}
	else {
		_tail = nullptr;
	}

	delete to_delete;
	_count--;
}

 template <typename T>
 void Double_List<T>::insert_at(size_t pos, const T& value) {
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
	 for (size_t i = 0; i < pos; i++) {
		 current = current->next;
	 }

	 insert_before(current, value);
 }

 template<typename T>
 void Double_List<T>::pop_back() {
	 if (is_empty()) {
		 throw std::logic_error("Cannot pop from empty list");
	 }

	 if (_head == _tail) {
		 delete _tail;
		 _head = nullptr;
		 _tail = nullptr;
		 _count = 0;
		 return;
	 }

	 Node<T>* to_delete = _tail;
	 _tail = _tail->prev;

	 if (_tail != nullptr) {
		 _tail->next = nullptr;
	 }
	 else {
		 _head = nullptr;
	 }

	 delete to_delete;
	 _count--;
 }

 template<typename T>
 void Double_List<T>::erase_at(size_t pos){
	 if (is_empty()) {
		 throw std::logic_error("Deletion cannot be performed, the list is empty");
	 }

	 if (pos >= _count) {
		 throw std::out_of_range("Position out of range");
	 }

	 if (pos == 0) {
		 pop_front();
		 return;
	 }

	 Node<T>* current = _head;
	 for (size_t i = 0; i < pos; i++) {
		 current = current->next;
	 }

	 erase(current);
 }

template<typename T>
void Double_List<T>::erase(Node<T>* node)
{
	if (node == nullptr || is_empty()) {
		throw std::logic_error("Node cannot be null or Double_List empty");
	}
	if (node->prev != nullptr) {
		node->prev->next = node->next;
	}
	else {
		_head = node->next;
	}

	if (node->next != nullptr) {
		node->next->prev = node->prev;
	}
	else {
		_tail = node->prev;
	}

	delete node;
	_count--;
}
