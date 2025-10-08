#pragma once
#include <cstddef> 
#include <stdlib.h> 
#include <time.h> 
#include <stdexcept>
#include <iostream>
#include <algorithm>

#define STEP_OF_CAPACITY 15

template<typename T> class TVector;

template<typename T>
int find_first(const TVector<T>& vec, const T& value);

template<typename T>
int find_last(const TVector<T>& vec, const T& value);

template<typename T>
int* find_elems(const TVector<T>& vec, const T& value);

template<typename T>
void swap(T* a, T* b);

template<typename T>
void randomize(const TVector<T>& vec);

template<typename T>
void hoara_sort_rec(const TVector<T>& vec, int left, int right);

template<typename T>
void hoara_sort(const TVector<T>& vec);

enum State { empty, busy, deleted };

template<class T>
class TVector {
    T* _data;
    size_t _capacity;
    size_t _size;
    size_t deleted_count_;
    State* _states;
public:
    TVector();
    TVector(size_t);
    TVector(const T*, size_t);
    TVector(const TVector<T>&);

    ~TVector();

    size_t capacity() const noexcept;
    size_t size() const noexcept;

    inline bool is_empty() const noexcept;
    T& get(size_t index);
    const T& get(size_t index) const;
    void set(size_t index, const T& value);

    inline T& front() ;
    inline T& back() ;

    inline T* begin() noexcept;
    inline T* end() noexcept;


    inline const T* data() const noexcept;
    inline const State* states() const noexcept;


    void push_front(const T&);
    void push_back(const T&);
    void insert(const T&, size_t);
    void insert_front(T* values, size_t count);
    void insert_back(T* values, size_t count);
    void insert_range(size_t pos, T* values, size_t count);

    void pop_front();
    void pop_back();
    void erase(size_t);
    void erase_front(size_t count);
    void erase_back(size_t count);
    void erase_range(size_t pos, size_t count);

    template <typename... Args>
    void emplace(size_t pos, Args&&... args);

    void clear() noexcept;
    void reserve(size_t new_capacity);
    void assign(size_t count, const T& value);
    T& at(size_t pos);
    void shrink_to_fit();
    void resize(size_t new_size, const T& value);
    void resize(size_t new_size);

    TVector<T>& operator=(const TVector<T>& other);
    bool operator==(const TVector<T>& other) const;
    bool operator!=(const TVector<T>& other) const;
    const T& operator[](size_t pos) const;
    T& operator[](size_t index);
    inline bool is_full() const noexcept;

    void print_elems();
    void print_states();

    friend int find_first<T>(const TVector<T>&, const T&);
    friend int find_last<T>(const TVector<T>&, const T&);
    friend int* find_elems<T>(const TVector<T>&, const T&);

    friend void swap<T>(T* a, T* b);
    friend void randomize<T>(const TVector<T>& vec);

    friend void hoara_sort_rec<T>(const TVector<T>& vec, int left, int right);
    friend void hoara_sort<T>(const TVector<T>& vec);

private:
    
    void allocate(size_t);
    void reallocate(size_t);
    void compact_and_reallocate();
    void free_memory() noexcept;
};



template<class T>
TVector<T>::TVector() {
    _data = nullptr;
    _capacity = 0;
    _size = 0;
    deleted_count_ = 0;
    _states = nullptr;
}

template<class T>
TVector<T>::TVector(size_t size) :
    _data(size > 0 ? new T[size]() : nullptr), 
    _size(size),
    _capacity(size),
    deleted_count_(0),
    _states(size > 0 ? new State[size] : nullptr)
{
    for (size_t i = 0; i < _size; ++i) {
        _states[i] = State::busy;
    }
}
template<class T>
TVector<T>::TVector(const T* arr, size_t size) {
    _capacity = 0;
    _data = nullptr;
    _size = size;
    deleted_count_ = 0;
    _states = nullptr;

    if (_size > 0) {
        _capacity = ((size - 1) / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
        _data = new T[_capacity];
        _states = new State[_capacity];

        for (size_t i = 0; i < _size; ++i) {
            _data[i] = arr[i];
            _states[i] = State::busy;
        }
        for (size_t i = _size; i < _capacity; ++i) {
            _states[i] = State::empty;
        }
    }
    else {
        _capacity = 0;
        _data = nullptr;
        _states = nullptr;
    }
}
template<class T>
TVector<T>::TVector(const TVector<T>& other) {
    _capacity = other._capacity;
    _size = other._size;
    deleted_count_ = other.deleted_count_;
    _data = nullptr;
    _states = nullptr;

    if (_capacity > 0 && other._data != nullptr && other._states != nullptr) {
        _data = new T[_capacity];
        _states = new State[_capacity];

        for (size_t i = 0; i < _capacity; i++) {
            _data[i] = other._data[i];
            _states[i] = other._states[i];
        }
    }
    else {
        _capacity = 0;
        _size = 0;
        deleted_count_ = 0;
        _data = nullptr;
        _states = nullptr;
    }
}
template<class T>
TVector<T>::~TVector() {
    if (_data != nullptr) {
        delete[] _data; 
    }
    if (_states != nullptr) {
        delete[] _states;
    }
}

template<class T>
inline const T* TVector<T>::data() const noexcept { return _data; }

template<class T>
inline const State* TVector<T>::states() const noexcept { return _states; }

template<class T>
size_t TVector<T>::capacity() const noexcept { return _capacity; }

template<class T>
size_t TVector<T>::size() const noexcept {
    return _size - deleted_count_;
}

template<class T>
inline T& TVector<T>::front()  {
    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == busy) {
            return _data[i];
        }
    }
    throw std::out_of_range("Vector is empty");
}

template<class T>
inline T& TVector<T>::back()  {
    for (size_t i = _capacity; i > 0; --i) {
        if (_states[i - 1] == busy) {
            return _data[i - 1];
        }
    }
    throw std::out_of_range("Vector is empty");
}

template<class T>
inline T* TVector<T>::begin() noexcept {
    return _data;
}

template<class T>
inline T* TVector<T>::end() noexcept {
    return _data + _capacity;
}

template<class T>
inline bool TVector<T>::is_empty() const noexcept {
    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == busy) {
            return false;
        }
    }
    return true;
}

template<class T>
T& TVector<T>::get(size_t index) {
    size_t busy_count = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == State::busy) {
            if (busy_count == index) return _data[i];
            ++busy_count;
        }
    }
    throw std::out_of_range("Index out of range");
}

template<class T>
const T& TVector<T>::get(size_t index) const {
    size_t busy_count = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == State::busy) {
            if (busy_count == index) return _data[i];
            ++busy_count;
        }
    }
    throw std::out_of_range("Index out of range");
}

template<class T>
void TVector<T>::set(size_t index, const T& value) {
    size_t busy_count = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == State::busy) {
            if (busy_count == index) {
                _data[i] = value;
                return;
            }
            ++busy_count;
        }
    }
    throw std::out_of_range("Index out of range");
}

template<class T>
void TVector<T>::push_front(const T& value) {
    if (_size >= _capacity) {
        reallocate(_capacity + 15);
    }
    for (size_t i = _size; i > 0; --i) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }

    _data[0] = value;
    _states[0] = busy;

    _size++;
}

template<class T>
void TVector<T>::push_back(const T& value) {
    if (_size >= _capacity) {
        reallocate(_capacity + 15);
    }

    _data[_size] = value;
    _states[_size] = busy;
    _size++;
}

template<class T>
void TVector<T>::insert(const T& value, size_t pos) {
    if (pos > size()) {
        throw std::out_of_range("Insert position out of range");
    }

    if (is_full()) {
        reallocate(_capacity + STEP_OF_CAPACITY);
    }

    size_t physical_pos = 0;
    size_t busy_count = 0;

    for (; physical_pos < _capacity; ++physical_pos) {
        if (_states[physical_pos] == busy) {
            if (busy_count == pos) break;
            busy_count++;
        }
    }
    if (physical_pos >= _capacity) {
        physical_pos = _size;
    }
    for (size_t i = _capacity - 1; i > physical_pos; --i) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }

    _data[physical_pos] = value;
    _states[physical_pos] = busy;
    _size++;
}

template<class T>
void TVector<T>::insert_front(T* values, size_t count) {
    _size += count;
    if (_size >= _capacity) {
        reallocate(_capacity + 15);
    }
    for (int i = _size - 1; i >= count; i--) {
        _data[i] = _data[i - count];
        _states[i] = _states[i - count];
    }
    for (int i = 0; i < count; i++) {
        _data[i] = values[i];
        _states[i] = busy;
    }
}
template<class T>
void TVector<T>::insert_back(T* values, size_t count) {
    if (_size + count >= _capacity) {
        reallocate(_capacity + 15);
    }
    for (int i = _size; i < _size + count; i++) {
        _data[i] = values[i - _size];
        _states[i] = busy;
    }
    _size += count;
}

template<class T>
void TVector<T>::insert_range(size_t pos, T* values, size_t count) {
    if (pos > size()) {  
        throw std::out_of_range("Invalid position");
    }
    size_t physical_pos = 0;
    size_t busy_count = 0;

    for (; physical_pos < _capacity; ++physical_pos) {
        if (_states[physical_pos] == busy) {
            if (busy_count == pos) break;
            busy_count++;
        }
    }
    if (physical_pos >= _capacity) {
        physical_pos = _size;
    }
    if (_size + count > _capacity) {
        reallocate(_size + count + STEP_OF_CAPACITY);
    }
    for (size_t i = _size; i > physical_pos; --i) {
        _data[i + count - 1] = std::move(_data[i - 1]);
        _states[i + count - 1] = _states[i - 1];
    }
    for (size_t i = 0; i < count; ++i) {
        _data[physical_pos + i] = values[i];
        _states[physical_pos + i] = busy;
    }

    _size += count;
}
template<class T>
void TVector<T>::pop_front() {
    if (size() == 0) {
        throw std::out_of_range("Cannot pop from empty vector");
    }

    size_t first_busy = 0;
    while (first_busy < _capacity && _states[first_busy] != State::busy) {
        first_busy++;
    }

    if (first_busy >= _capacity) {
        throw std::logic_error("No busy elements found despite non-zero size");
    }

    for (size_t i = first_busy; i < _capacity - 1; ++i) {
        _data[i] = std::move(_data[i + 1]);
        _states[i] = _states[i + 1];
    }

    _states[_capacity - 1] = State::empty;
    _size--;

}

template<class T>
void TVector<T>::pop_back() {
    if (size() == 0) {
        throw std::out_of_range("Cannot pop from empty vector");
    }

    for (int i = static_cast<int>(_capacity) - 1; i >= 0; --i) {
        if (_states[i] == busy) {
            _states[i] = State::deleted;
            ++deleted_count_;
            break;
        }
    }

    if (deleted_count_ > _capacity * 0.15) {
        compact_and_reallocate();
    }
}

template<class T>
void TVector<T>::erase(size_t index) {
    if (index >= size()) throw std::out_of_range("Index out of range");

    size_t busy_count = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == State::busy) {
            if (busy_count == index) {
                _states[i] = State::deleted;
                deleted_count_++;
                break;
            }
            ++busy_count;
        }
    }
    if (deleted_count_ > _capacity * 0.15) {
        compact_and_reallocate();
    }
}

template<class T>
void TVector<T>::erase_front(size_t count) {
    if (size() == 0) {
        throw std::out_of_range("Cannot pop from empty vector");
    }

    if (count > size()) {
        throw std::invalid_argument("Count cannot be bigger than size");
    }

    size_t deleted_count = 0;
    for (size_t i = 0; i < _size && deleted_count < count; i++) {
        if (_states[i] == busy) {
            _states[i] = deleted;
            deleted_count++;
        }
    }
    deleted_count_ += deleted_count;

    if (deleted_count_ > _capacity * 0.15) {
        compact_and_reallocate();
    }
}

template<class T>
void TVector<T>::erase_back(size_t count) {
    if (size() == 0) {
        throw std::out_of_range("Cannot pop from empty vector");
    }

    if (count > size()) {
        throw std::invalid_argument("Count cannot be bigger than size");
    }

    size_t deleted_count = 0;
    for (int i = static_cast<int>(_size) - 1; i >= 0 && deleted_count < count; i--) {
        if (_states[i] == busy) {
            _states[i] = deleted;
            deleted_count++;
        }
    }
    deleted_count_ += deleted_count;

    if (deleted_count_ > _capacity * 0.15) {
        compact_and_reallocate();
    }
}

template<class T>
void TVector<T>::erase_range(size_t pos, size_t count) {
    if (size() == 0) {
        throw std::out_of_range("Cannot erase from empty vector");
    }

    if (pos >= size() || pos + count > size()) {
        throw std::out_of_range("Invalid position or count");
    }

    if (count == 0) {
        return;
    }

    size_t physical_pos = 0;
    size_t busy_count = 0;
    for (; physical_pos < _capacity; ++physical_pos) {
        if (_states[physical_pos] == busy) {
            if (busy_count == pos) break;
            busy_count++;
        }
    }

    size_t deleted_count = 0;
    for (size_t i = physical_pos; i < _capacity && deleted_count < count; ++i) {
        if (_states[i] == busy) {
            _states[i] = deleted;
            deleted_count++;
            deleted_count_++;
        }
    }

    if (deleted_count_ > _capacity * 0.15) {
        compact_and_reallocate();
    }
}

template <typename T>
template <typename... Args>
void TVector<T>::emplace(size_t pos, Args&&... args) {
    if (pos > size()) {  
        throw std::out_of_range("Position out of range");
    }

    if (is_full()) {
        reallocate(_capacity + STEP_OF_CAPACITY);
    }

    size_t physical_pos = 0;
    size_t busy_count = 0;

    for (; physical_pos < _capacity; ++physical_pos) {
        if (_states[physical_pos] == busy) {
            if (busy_count == pos) break;
            busy_count++;
        }
    }

    if (physical_pos >= _capacity) {
        physical_pos = _size;  
    }
    else {
        for (size_t i = _capacity - 1; i > physical_pos; --i) {
            _data[i] = std::move(_data[i - 1]);
            _states[i] = _states[i - 1];
        }

        _states[physical_pos] = empty;
    }

    new (&_data[physical_pos]) T(std::forward<Args>(args)...);
    _states[physical_pos] = busy;
    _size++;
}


template <typename T>
void TVector<T>::clear() noexcept {
    delete[] _data;
    delete[] _states;

    _size = 0;
    deleted_count_ = 0;
    _capacity = STEP_OF_CAPACITY;

    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template<class T>
void TVector<T>::reserve(size_t new_capacity) {
    if (new_capacity <= _capacity) {
        return;
    }

    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity]();

    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == busy) {
            new (new_data + i) T(std::move(_data[i]));
            new_states[i] = busy;
            _data[i].~T();
        }
    }

    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
}

template <typename T>
void TVector<T>::assign(size_t count, const T& value) {
    clear();
    reserve(count);
    for (size_t i = 0; i < count; i++) {
        push_back(value);
    }
}

template<class T>
T& TVector<T>::at(size_t pos) {
    if (pos >= size()) {
        throw std::out_of_range("Index out of range");
    }

    size_t busy_count = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == State::busy) {
            if (busy_count == pos) {
                return _data[i];
            }
            ++busy_count;
        }
    }
    throw std::out_of_range("Index out of range");
}

template <typename T>
void TVector<T>::shrink_to_fit() {
    if (_size == 0) {
        delete[] _data;
        delete[] _states;
        _data = nullptr;
        _states = nullptr;
        _capacity = 0;
        return;
    }

    T* new_data = new T[_size];
    State* new_states = new State[_size];

    size_t new_index = 0;
    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == busy) {
            new_data[new_index] = _data[i];
            new_states[new_index] = busy;
            new_index++;
            _data[i].~T();
        }
    }

    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _capacity = _size;
    deleted_count_ = 0;
}

template <typename T>
void TVector<T>::resize(size_t new_size) {
    if (new_size < _size) {
        for (size_t i = new_size; i < _size; i++) {
            if (_states[i] == busy) {
                _data[i].~T();
                _states[i] = empty;
            }
        }
        _size = new_size;
    }
    else if (new_size > _size) {
        reserve(new_size);
        for (size_t i = _size; i < new_size; i++) {
            new (_data + i) T();
            _states[i] = busy;
        }
        _size = new_size;
    }
}

template <typename T>
void TVector<T>::resize(size_t new_size, const T& value) {
    if (new_size < _size) {
        for (size_t i = new_size; i < _size; i++) {
            if (_states[i] == busy) {
                _data[i].~T();
                _states[i] = empty;
            }
        }
        _size = new_size;
    }
    else if (new_size > _size) {
        reserve(new_size);
        for (size_t i = _size; i < new_size; i++) {
            new (_data + i) T(value);
            _states[i] = busy;
        }
        _size = new_size;
    }
}

template <typename T>
TVector<T>& TVector<T>::operator=(const TVector<T>& other) {
    if (this != &other) {
        clear();
        reserve(other._capacity);
        for (size_t i = 0; i < other._size; ++i) {
            if (other._states[i] == busy) {
                new (_data + i) T(other._data[i]);
                _states[i] = busy;
            }
        }
        _size = other._size;
        deleted_count_ = other.deleted_count_;
    }
    return *this;
}

template <typename T>
bool TVector<T>::operator==(const TVector<T>& other) const {
    if (this == &other) return true;
    if (size() != other.size()) return false;

    size_t this_count = 0;
    size_t other_count = 0;

    for (size_t i = 0, j = 0; i < _capacity && j < other._capacity; ) {
        while (i < _capacity && _states[i] != busy) i++;
        while (j < other._capacity && other._states[j] != busy) j++;

        if (i < _capacity && j < other._capacity) {
            if (_data[i] != other._data[j]) {
                return false;
            }
            i++;
            j++;
        }
    }

    return true;
}

template <typename T>
bool TVector<T>::operator!=(const TVector<T>& other) const {
    return !(*this == other);
}

template<class T>
const T& TVector<T>::operator[](size_t pos) const{
    size_t busy_count = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == State::busy) {
            if (busy_count == pos) {
                return _data[i];
            }
            ++busy_count;
        }
    }
    throw std::out_of_range("Index out of range");
}

template<class T>
T& TVector<T>::operator[](size_t pos){
    size_t busy_count = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == State::busy) {
            if (busy_count == pos) {
                return _data[i];
            }
            ++busy_count;
        }
    }
    throw std::out_of_range("Index out of range");
}

template<class T>
void TVector<T>::print_elems() {
    int entrance = 0;
    for (size_t i = 0; entrance < _size; i++) {
        if (_states[i] == busy) {
            std::cout << _data[i] << " ";
            entrance++;
        }
    }
    std::cout << std::endl;

}

template<class T>
void TVector<T>::print_states() {
    for (size_t i = 0; i < _capacity; i++) {
        std::cout << _states[i] << " ";
    }
    std::cout << std::endl;
}

template<class T>
inline bool TVector<T>::is_full() const noexcept { return (_size - deleted_count_) >= _capacity; }

template<class T>
void TVector<T>::allocate(size_t new_capacity) {
    T* new_data = static_cast<T*>(operator new[](new_capacity * sizeof(T)));
    State* new_states = new State[new_capacity];

    for (size_t i = 0; i < new_capacity; ++i) {
        new_states[i] = empty;
    }

    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
}

template<class T>
void TVector<T>::compact_and_reallocate() {
    size_t busy_count = _size - deleted_count_;
    size_t new_capacity = (busy_count == 0) ? STEP_OF_CAPACITY :
        ((busy_count / STEP_OF_CAPACITY) + 1) * STEP_OF_CAPACITY;

    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity];

    for (size_t i = 0; i < new_capacity; ++i) {
        new_states[i] = State::empty;
    }

    size_t new_index = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == State::busy) {
            new_data[new_index] = std::move(_data[i]);
            new_states[new_index] = State::busy;
            new_index++;
        }
    }

    delete[] _data;
    delete[] _states;

    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _size = new_index; 
    deleted_count_ = 0;
}

template<class T>
void TVector<T>::reallocate(size_t new_capacity) {
    if (new_capacity <= _capacity) return;

    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity];

    for (size_t i = 0; i < new_capacity; ++i) {
        new_states[i] = empty;
    }

    size_t new_index = 0;
    for (size_t i = 0; i < _capacity; ++i) {
        if (_states[i] == busy) {
            new_data[new_index] = std::move(_data[i]);
            new_states[new_index] = busy;
            new_index++;
        }
    }

    delete[] _data;
    delete[] _states;

    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    deleted_count_ = 0; 
}
template<class T>
void TVector<T>::free_memory() noexcept {

    operator delete[](_data);
    delete[] _states;

    _data = nullptr;
    _states = nullptr;
    _size = 0;
    _capacity = 0;
    deleted_count_ = 0;
}


template <typename T>
int find_first(const TVector<T>& vec, const T& value) {
    int index = 0;
    for (size_t i = 0; i < vec._capacity; ++i) {
        if (vec._states[i] == busy) {
            if (vec._data[i] == value) {
                return index;
            }
            index++;
        }
    }
    return -1;
}


template <typename T>
int find_last(const TVector<T>& vec, const T& value) {
    int last_found = -1;
    int visible_idx = -1;

    if (vec.size() == 0) {
        throw std::invalid_argument("Cannot find from empty vector");
    }

    for (size_t i = 0; i < vec._size; ++i) {
        if (vec._states[i] == busy) {
            visible_idx++;
            if (vec._data[i] == value) {
                last_found = visible_idx;
            }
        }
    }

    return last_found;
}


template<typename T>
int* find_elems(const TVector<T>& vec, const T& value) {
    int size = 0;

    if (vec.size() == 0) {
        throw std::invalid_argument("Cannot find from empty vector");
    }

    for (int i = 0; i < vec._capacity; i++) {
        if (vec._states[i] == busy && vec._data[i] == value) {
            size++;
        }
    }


    if (size == 0) {
        int* result = new int[1];
        result[0] = -1;
        return result;
    }

    int* result = new int[size];
    int index = 0;

    for (int i = 0, j = 0; i < vec._capacity; i++) {
        if (vec._states[i] == busy) {
            if (vec._data[i] == value) {
                result[j] = index; j++;
            }
            index++;
        }
    }

    return result;
}

template <typename T>
void randomize(const TVector<T>& vec) {
    srand(time(NULL));

    for (int i = vec._size; i > 0; i--) {
        if (vec._states[i] == busy) {
            int j = rand() % (i + 1);
            swap(&vec._data[i], &vec._data[j]);
            swap(&vec._states[i], &vec._states[j]);
        }
    }
}

template <typename T>
void swap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T>
void hoara_sort_rec(const TVector<T>& vec, int left, int right) {
    if (left < right) {
        int l = left, r = right;
        int base_pos = (left + right) / 2;
        T base_value = vec._data[base_pos];

        while (l <= r) {
            while (vec._data[l] < base_value) {
                l++;
            }
            while (vec._data[r] > base_value) {
                r--;
            }
            if (l <= r) {
                if (l < r) {
                    swap(&vec._data[l], &vec._data[r]);
                    swap(&vec._states[l], &vec._states[r]);
                }
                l++;
                r--;
            }
        }
        hoara_sort_rec(vec, left, r);
        hoara_sort_rec(vec, l, right);
    }
}

template <typename T>
void hoara_sort(const TVector<T>& vec) {
    hoara_sort_rec(vec, 0, vec._size);
}

