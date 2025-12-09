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
    List& operator=(const List<T>&);
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

    bool has_loop_floyd() const;
    bool has_loop_pointer_reversal();
    Node<T>* find_loop() const;
    void create_loop(int pos);
    void remove_loop_if_exists(); 
    bool has_loop_distance() const;
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const List<U>& list);

    class Iterator {
        Node<T>* _current;
    public:

        Iterator() : _current(nullptr) {}
        Iterator(Node<T>* node) : _current(node) {}
        Iterator& operator=(const Iterator& other) noexcept {
            _current = other._current;
            return *this;
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

        bool operator!=(const Iterator& other) const {
            return (_current != other._current);
        }

        bool operator==(const Iterator& other) const {
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
List<T>& List<T>::operator=(const List<T>& other) {
    if (this == &other) {
        return *this;
    }

    clear();

    Node<T>* cur = other._head;
    while (cur != nullptr) {
        push_back(cur->value);
        cur = cur->next;
    }
    return *this;
}


template <class T>
void List<T>::clear() {
    while (_head != nullptr) {
        Node<T>* temp = _head;
        _head = _head->next;
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
size_t List<T>::count() const {
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
        _count = 0;
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
        _count = 0;
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
        _count = 0;
        return;
    }
    if (node == _head) {
        pop_front();
        return;
    }
    Node <T>* cur = _head;
    while (cur->next != node && cur->next != nullptr) {
        cur = cur->next;
    }
    if (cur == nullptr) {
        throw std::invalid_argument("Position is wrong");
    }
    cur->next = node->next;
    delete node;
    _count -= 1;
};
template <class T>
Node<T>* List<T>::find_loop() const {
    if (_head == nullptr || _head->next == nullptr) {
        return nullptr;
    }
    Node<T>* slow = _head;
    Node<T>* fast = _head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;
        }

    }
    if (slow != fast) {
        return nullptr;
    }
    slow = _head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

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

template <class T>
void List<T>::erase(size_t pos) {
    if (is_empty()) {
        throw std::invalid_argument("List is empty");
    }
    if (_tail == _head) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _count = 0;
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

template <class T>
bool List<T>::has_loop_floyd() const {
    if (_head == nullptr || _head->next == nullptr) {
        return false;
    }
    Node<T>* turtle = _head;
    Node<T>* hare = _head->next;
    while (hare != nullptr && hare->next != nullptr) {
        if (turtle == hare) {
            return true;
        }
        turtle = turtle->next;
        hare = hare->next->next;
    }
    return false;
}

template <class T>
bool List<T>::has_loop_pointer_reversal() {
    if (_head == nullptr)
        return false;

    Node<T>* original_head = _head;
    Node<T>* prev = nullptr;
    Node<T>* current = _head;
    Node<T>* next = nullptr;
    bool has_loop = false;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;

        if (current == original_head) {
            has_loop = true;
            break;
        }
    }

    current = prev;
    prev = nullptr;
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    _head = prev;

    if (_head == nullptr) {
        _tail = nullptr;
    }
    else {
        Node<T>* temp = _head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        _tail = temp;
    }

    return has_loop;
}


template <class T>
void List<T>::remove_loop_if_exists() {
    Node<T>* loop_start = find_loop();
    if (loop_start == nullptr) {
        return;
    }

    Node<T>* current = loop_start;
    while (current->next != loop_start) {
        current = current->next;
    }
    current->next = nullptr;
    _tail = current;
}

template <class T>
void List<T>::create_loop(int pos) {
    if (pos < 0 || pos >= _count) {
        throw std::invalid_argument("Invalid position for creating loop");
    }
    if (_head == nullptr) {
        throw std::logic_error("Cannot create loop in an empty list");
    }
    Node<T>* loop_start_node = _head;
    for (int i = 0; i < pos; ++i) {
        loop_start_node = loop_start_node->next;
    }
    _tail->next = loop_start_node;
}

template <class T>
bool List<T>::has_loop_distance() const {
    if (_head == nullptr) 
        return false;

    Node<T>* current = _head;
    int steps = 0;

    while (current != nullptr && steps <= _count) {
        Node<T>* from_start = _head;
        int search_steps = 0;

        while (from_start != current && search_steps < steps) {
            from_start = from_start->next;
            search_steps++;
        }

        if (from_start == current && search_steps < steps) {
            return true;
        }

        current = current->next;
        steps++;
    }

   
    return false;
}