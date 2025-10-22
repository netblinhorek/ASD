#include <iostream>

template <class T>
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
	Node<T>* head();
	Node<T>* tail();

	bool is_empty();
	void push_front(const T& value)noexcept;
	void push_back(const T& value)noexcept;
	void insert_at(size_t pos, const T& value);
	void insert_after(Node<T>* after_node, const T& value);
	void pop_front();
	void pop_back();
	void erase(size_t pos);
	void erase(Node<T>* node);

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
	 delete _head;
	 delete _tail;

}

 template<typename T>
 List<T>::List(const List<T>& other): _head(nullptr), _tail(nullptr), _count(0)
 {
 }

 template<typename T>
 Node<T>* List<T>::head()
 {
	 return _head;
 }

 template<typename T>
 Node<T>* List<T>::tail()
 {
	 return _tail;
 }

template <typename T>
bool List<T>::is_empty() {
	return _head == nullptr;
}

template <class T>
void List<T>::push_front(const T& value) noexcept {
	Node<T>* node = new Node<T>(value);
	if (is_empty()) {
		_head = node;
		_tail = node;
		return;
	}
	node->next = _head;
	_head = node;
}

template <class T>
void List<T>::push_back(const T& value)noexcept {
	Node<T>* node = new Node<T>(value); //
	if (is_empty()) {
		_head = node;
		_tail = node;
		return;
	}
	_tail->next = node;
	_tail = node;
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

