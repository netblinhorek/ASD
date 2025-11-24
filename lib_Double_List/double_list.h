#pragma once

#include <iostream>

template <class T>
class Double_List {
private:
    template <class U>
    struct Node {
        U value;
        Node<U>* next;
        Node<U>* prev;

        Node(U val) : value(val), next(nullptr), prev(nullptr) {}
    };

    Node<T>* _head;
    Node<T>* _tail;
    size_t _count;

public:
    Double_List() : _head(nullptr), _tail(nullptr), _count(0) {}

    ~Double_List() {
        clear();
    }

    Double_List(const Double_List& other) : _head(nullptr), _tail(nullptr), _count(0) {
        Node<T>* current_other = other._head;
        Node<T>* new_node = nullptr;

        while (current_other != nullptr) {
            new_node = new Node<T>(current_other->value);
            if (_head == nullptr) {
                _head = new_node;
                _tail = new_node;
            } else {
                _tail->next = new_node;
                new_node->prev = _tail;
                _tail = new_node;
            }
            _count++;
            current_other = current_other->next;
        }
    }

    Double_List& operator=(const Double_List& other) {
        if (this != &other) {
            clear();
            Node<T>* current = other._head;
            while (current != nullptr) {
                push_back(current->value); 
                current = current->next;
            }
        }
        return *this;
    }

    bool is_empty() const { return _head == nullptr; }
    size_t get_size() const { return _count; }

    void push_back(const T& value) {
        Node<T>* new_node = new Node<T>(value);
        if (is_empty()) {
            _head = new_node;
            _tail = new_node;
        } else {
            _tail->next = new_node;
            new_node->prev = _tail;
            _tail = new_node;
        }
        _count++;
    }

    void push_front(const T& value) {
        Node<T>* new_node = new Node<T>(value);
        if (is_empty()) {
            _head = new_node;
            _tail = new_node;
        } else {
            _head->prev = new_node;
            new_node->next = _head;
            _head = new_node;
        }
        _count++;
    }

    void pop_back() {
        if (is_empty()) {
            throw std::out_of_range("List is empty");
        }
        Node<T>* temp = _tail;
        if (_head == _tail) {
            _head = nullptr;
            _tail = nullptr;
        } else {
            _tail = _tail->prev;
            _tail->next = nullptr;
        }
        delete temp;
        _count--;
    }

    void pop_front() {
        if (is_empty()) {
            throw std::out_of_range("List is empty");
        }
        Node<T>* temp = _head;
        if (_head == _tail) {
            _head = nullptr;
            _tail = nullptr;
        } else {
            _head = _head->next;
            _head->prev = nullptr;
        }
        delete temp;
        _count--;
    }

    const T& head() const {
        if (is_empty()) {
            throw std::out_of_range("List is empty");
        }
        return _head->value;
    }

    const T& tail() const {
        if (is_empty()) {
            throw std::out_of_range("List is empty");
        }
        return _tail->value;
    }

    void clear() {
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

    class Iterator {
    private:
        Node<T>* _current;
    public:
        Iterator(Node<T>* node) : _current(node) {}

        T& operator*() { return _current->value; }
        const T& operator*() const { return _current->value; }

        Iterator& operator++() {
            if (_current) _current = _current->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return _current == other._current;
        }

        bool operator!=(const Iterator& other) const {
            return _current != other._current;
        }

        Node<T>* get_current_node() const {
            return _current;
        }
    };

    inline Iterator begin() const { return Iterator(_head); }
    inline Iterator end() const { return Iterator(nullptr); }

    Iterator erase(Node<T>* node) {
        if (node == nullptr || _head == nullptr) {
            return Iterator(nullptr); 
        }

        Iterator next_it(node->next);

        if (node == _head) {
            _head = node->next;
            if (_head) _head->prev = nullptr;
        } else if (node == _tail) {
            _tail = node->prev;
            if (_tail) _tail->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        delete node;
        _count--;
        return next_it;
    }
};

#endif 
