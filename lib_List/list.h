#pragma once 
#include <iostream>
#include <algorithm> 
#include <unordered_set>


template <typename T>
struct Node {
    T value;
    Node<T>* next;
public:
    Node(T value_, Node<T>* next_ = nullptr) : value(value_), next(next_) {}
};

template <class T>
class List {
  Node<T>* _head, * _tail;
  size_t _count;

public:
  List();
  List(const List<T>&);
  ~List();

  bool is_empty() const;
  void clear();
  size_t count() const;
  Node <T>* head() const;
  Node <T>* tail() const;

  void push_front(const T& value) noexcept;
  void push_back(const T& value) noexcept;
  void insert(size_t pos, const T& value);
  void insert(Node <T>* node, const T& value);
  void pop_front();
  void pop_back();
  void erase(size_t pos);
  void erase(Node <T>* node);

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const List<U>& list);

  class Iterator {
    Node<T>* _current;
  public:

    Iterator() : _current(nullptr) {}
    Iterator(Node<T>* node) : _current(node) {}
    Iterator& operator=(const Iterator& other) noexcept{
      _current = other._current;
      return *this;
    }

    Iterator& operator++() {
      if (_current != nullptr) {
        _current = _current->next;
      }
      return *this;
    };

    Iterator operator++(int) {
      Iterator temp = *this;
      (*this)++;
      return temp;
    }

    bool operator!=(const Iterator& other) {
      return (_current != other._current);
    }

    bool operator==(const Iterator& other) {
      return (_current == other._current);
    }

    T& operator*() {
      return (_current->value);
    }

  };

  Iterator begin() {
    return Iterator(_head);
  }

  Iterator end() {
    return Iterator(nullptr);
  }

private:

};

template <class T>
List<T>::List() {
  _count = 0;
  _head = nullptr;
  _tail = nullptr;
}

template <class T>
List<T>::List(const List<T>& other) {
    _head = nullptr;
    _tail = nullptr;
    _count = 0;

    Node<T>* cur = other._head;
    while (cur != nullptr) {
        push_back(cur->value);
        cur = cur->next;
    }
}


template <class T>
void List<T>::clear() {
  while (_head != nullptr) {
    Node<T>* temp = _head;
    _head = _head->next;
    temp->next = nullptr; 
    delete temp;
  }
  _tail = nullptr;
  _count = 0;
}

template <class T>
List<T>::~List() {
  clear();
}


template <class T>
size_t List<T>::count() const  {
  return _count;
}

template <class T>
Node<T>* List<T>::head() const {
  return _head;
}

template <class T>
Node<T>* List<T>::tail() const {
  return _tail;
}


template <class T>
bool List<T>::is_empty() const {
  return _head == nullptr;
}

template <class T>
void List<T>::push_front(const T& val) noexcept {
  Node <T>* node = new Node <T>(val);
  if (is_empty()) {
    _count += 1;
    _head = node;
    _tail = node;
    return;
  }
  node->next = _head;
  _head = node;
  _count += 1;
};

template <class T>
void List<T>::push_back(const T& val) noexcept {
  Node <T>* node = new Node <T>(val);
  if (is_empty()) {
    _count += 1;
    _head = node;
    _tail = node;
    return;
  }
  _tail->next = node;
  _tail = node;
  _count += 1;
};

template <class T>
void List<T>::insert(Node <T>* node, const T& val) {
  Node <T>* new_node = new Node <T>(val);
  if (is_empty() || node == nullptr) {
    throw std::invalid_argument("Position is wrong");
  }

  new_node->next = node->next;
  node->next = new_node;
  if (node == _tail) { 
    _tail = new_node;
  }
  _count += 1;
};

template <class T>
void List<T>::insert(size_t pos, const T& val) {
  if (pos == 0) {
    push_front(val);
    return;
  }
  if (pos == _count) {
    push_back(val);
    return;
  }
  Node <T>* cur = _head;
  size_t cur_pos = 0;
  while (cur != nullptr) {
    if (cur_pos == pos - 1) {
      break;
    }
    cur_pos++;
    cur = cur->next;
  }
  if (cur == nullptr) {
    throw std::invalid_argument("Position is wrong");
  }
  insert(cur, val);
};

template <class T>
void List<T>::pop_front() {
  if (is_empty()) {
    throw std::invalid_argument("List is empty");
  }
  if (_tail == _head) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
    return;
  }
  _head = _head->next;
  _count--;
};



template <class T>
void List<T>::pop_back() {
  if (is_empty()) {
    throw std::invalid_argument("List is empty");
  }
  if (_tail == _head) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
    return;
  }
  Node <T>* cur = _head;
  while (cur->next != _tail) {
    cur = cur->next;
  }
  delete _tail;
  _tail = cur;
  cur->next = nullptr;
  _count--;
};

template <class T>
void List<T>::erase(Node <T>* node) {
  if (is_empty()) {
    throw std::invalid_argument("List is empty");
  }
  if (_tail == _head) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
    return;
  }
  if (node == _head) {
    pop_front();
    return;
  }
  Node <T>* cur = _head;
  while (cur ->next != node && cur ->next != nullptr) {
    cur = cur->next;
  }
  if (cur == nullptr) {
    throw std::invalid_argument("Position is wrong");
  }
  cur->next = node->next;
  node->next = nullptr;
  delete node;
  _count -= 1;
};

template <class T>
void List<T>::erase(size_t pos) {
  if (is_empty()) {
    throw std::invalid_argument("List is empty");
  }
  if (_tail == _head) {
    delete _head;
    _head = nullptr;
    _tail = nullptr;
    return;
  }
  Node <T>* cur = _head;
  size_t cur_pos = 0;
  while (cur_pos < pos && cur != nullptr) {
    cur_pos++;
    cur = cur->next;
  }
  if (cur == nullptr) {
    throw std::invalid_argument("Position is wrong");
  }
  erase(cur);
};

//template <class T>
//bool List<T>::has_loop_floyd() const {
//  if (_head == nullptr || _head->next == nullptr) {
//    return false;
//  }
//  Node<T>* slow = _head;
//  Node<T>* fast = _head->next;
//  while (fast != nullptr && fast->next != nullptr) {
//    if (slow == fast) {
//      return true;
//    }
//    slow = slow->next;
//    fast = fast->next->next;
//  }
//  return false;
//}
//
//template <class T>
//bool List<T>::has_loop_pointer_reversal() {
//    if (_head == nullptr)
//        return false;
//
//    Node<T>* original_head = _head;
//    Node<T>* prev = nullptr;
//    Node<T>* current = _head;
//    Node<T>* next = nullptr;
//    bool has_loop = false;
//
//    while (current != nullptr) {
//        next = current->next;
//        current->next = prev;
//        prev = current;
//        current = next;
//
//        if (current == original_head) {
//            has_loop = true;
//            break;
//        }
//    }
//
//    current = prev;
//    prev = nullptr;
//    while (current != nullptr) {
//        next = current->next;
//        current->next = prev;
//        prev = current;
//        current = next;
//    }
//    _head = prev;
//
//    if (_head == nullptr) {
//        _tail = nullptr;
//    }
//    else {
//        Node<T>* temp = _head;
//        while (temp->next != nullptr) {
//            temp = temp->next;
//        }
//        _tail = temp;
//    }
//
//    return has_loop;
//}
//
//
//template <class T>
//Node<T>* List<T>::find_loop() const {
//  if (_head == nullptr || _head->next == nullptr) {
//    return nullptr;
//  }
//  Node<T>* slow = _head;
//  Node<T>* fast = _head;
//  while (fast != nullptr && fast->next != nullptr) {
//    slow = slow->next;
//    fast = fast->next->next;
//    if (slow == fast) {
//      break; 
//    }
//
//  }
//  if (slow != fast) {
//    return nullptr;
//  }
//  slow = _head;
//  while (slow != fast) {
//    slow = slow->next;
//    fast = fast->next;
//  }
//  return slow; 
//}
//
//template <class T>
//void List<T>::create_loop(int pos) {
//  if (pos < 0 || pos >= _count) {
//    throw std::invalid_argument("Invalid position for creating loop");
//  }
//  if (_head == nullptr) {
//    throw std::logic_error("Cannot create loop in an empty list");
//  }
//  Node<T>* loop_start_node = _head;
//  for (int i = 0; i < pos; ++i) {
//    loop_start_node = loop_start_node->next;
//  }
//  _tail->next = loop_start_node;
//}
//
template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list) {
  Node<T>* cur = list.head();
  os << "[";
  while (cur != nullptr) {
    os << cur->value;
    if (cur->next != nullptr) {
      os << " ";
    }
    cur = cur->next;
  }
  os << "]";
  return os;

}
