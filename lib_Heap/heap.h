#pragma once
#include "../lib_BSTree/bstree.h"  
#include "../lib_TVector/tvector.h"
#include <stdexcept>
#include <utility>


template <typename TKey, typename TValue>
struct NodeTr {
    TKey key;
    TValue value;
    NodeTr<TKey, TValue>* left;
    NodeTr<TKey, TValue>* right;

    NodeTr() : left(nullptr), right(nullptr) {}
    NodeTr(const TKey& k, const TValue& v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

template <typename TKey, typename TValue>
struct NodeHeap {
    std::pair<TKey, TValue> data;

    NodeHeap() {}
    NodeHeap(const TKey& key, const TValue& value) : data(key, value) {}

    bool operator>(const NodeHeap& other) const {
        return data.first > other.data.first;
    }

    bool operator<(const NodeHeap& other) const {
        return data.first < other.data.first;
    }
};

template <typename T>
class Heap {
private:
    TVector<T> _heap;

    size_t left(size_t i) {
        return 2 * i + 1;
    }

    size_t right(size_t i) {
        return 2 * i + 2;
    }

    size_t parent(size_t i) {
        return (i - 1) / 2;
    }

    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    void sift_up(size_t index) {
        while (index > 0) {
            size_t p = parent(index);
            if (_heap[p] > _heap[index]) {
                swap(_heap[p], _heap[index]);
                index = p;
            }
            else {
                break;
            }
        }
    }

    void sift_down(size_t index, size_t heap_size) {
        while (1) {
            size_t smallest = index;
            size_t l = left(index);
            size_t r = right(index);

            if (l < heap_size && _heap[l] < _heap[smallest]) {
                smallest = l;
            }
            if (r < heap_size && _heap[r] < _heap[smallest]) {
                smallest = r;
            }

            if (smallest == index) {
                break;
            }

            swap(_heap[index], _heap[smallest]);
            index = smallest;
        }
    }

public:
    Heap() = default;

    Heap(const TVector<T>& data) : _heap(data) {
        build_heap();
    }

    void build_heap() {
        if (_heap.is_empty())
            return;

        size_t last_parent = (_heap.size() - 1) / 2;

        for (size_t i = last_parent + 1; i-- > 0; ) {
            sift_down(i, _heap.size());
        }
    }

    void insert(const T& value) {
        _heap.push_back(value);
        sift_up(_heap.size() - 1);
    }

    T extract_min() {
        if (_heap.is_empty()) {
            throw std::logic_error("Heap is empty");
        }

        T min = _heap[0];

        _heap[0] = _heap.back();
        _heap.pop_back();

        if (!_heap.is_empty()) {
            sift_down(0, _heap.size());
        }

        return min;
    }

    T erase_root() {
        return extract_min();
    }

    const T& peek_min() const {
        if (_heap.is_empty()) {
            throw std::logic_error("Heap is empty");
        }
        return _heap[0];
    }

    bool is_empty() const {
        return _heap.is_empty();
    }

    size_t size() const {
        return _heap.size();
    }

    void clear() {
        _heap.clear();
    }

    const TVector<T>& get_data() const {
        return _heap;
    }
};

template <typename TKey, typename TValue>
void bypassingHeap(Node<TKey, TValue>* node, TVector<NodeTr<TKey, TValue>>& result) {
    if (node == nullptr) return;

    bypassingHeap(node->_left, result);

    result.push_back(NodeTr<TKey, TValue>(node->_data.first, node->_data.second));

    bypassingHeap(node->_right, result);
}

template <typename TKey, typename TValue>
TVector<NodeHeap<TKey, TValue>> heapSort(const TVector<NodeHeap<TKey, TValue>>& data) {
    Heap<NodeHeap<TKey, TValue>> heap(data);
    TVector<NodeHeap<TKey, TValue>> result;

    while (!heap.is_empty()) {
        NodeHeap<TKey, TValue> delete_node = heap.erase_root();
        result.push_back(delete_node);
    }
    return result;
}
template <typename TKey, typename TValue>
TVector<NodeTr<TKey, TValue>> BSTSort(const TVector<NodeHeap<TKey, TValue>>& data) {
    BSTree<TKey, TValue> bst;

    for (size_t i = 0; i < data.size(); i++) {
        bst.insert(data[i].data.first, data[i].data.second);
    }

    TVector<NodeTr<TKey, TValue>> result;

    bypassingHeap<TKey, TValue>(bst.get_root_ptr(), result);

    return result;
}