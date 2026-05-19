#include <gtest/gtest.h>
#include "heap.h"

TEST(HeapMinTest, test_is_empty_heap) {
    Heap<int> heap;
    EXPECT_TRUE(heap.is_empty());

}

TEST(HeapMinTest, insert_and_extract_min) {
    Heap<int> heap;
    heap.insert(5);
    heap.insert(2);
    heap.insert(8);
    heap.insert(1);

    EXPECT_EQ(heap.peek_min(), 1);
    EXPECT_EQ(heap.extract_min(), 1);
    EXPECT_EQ(heap.extract_min(), 2);
    EXPECT_EQ(heap.extract_min(), 5);
    EXPECT_EQ(heap.extract_min(), 8);
    EXPECT_TRUE(heap.is_empty());
}

TEST(HeapMinTest, heap_sort_ascending_order) {
    TVector<int> data;
    data.push_back(64);
    data.push_back(34);
    data.push_back(25);
    data.push_back(12);
    data.push_back(22);
    data.push_back(11);
    data.push_back(90);

    Heap<int> heap(data);
    TVector<int> sorted;

    while (!heap.is_empty()) {
        sorted.push_back(heap.extract_min());
    }

    EXPECT_EQ(sorted.size(), 7u);
    EXPECT_EQ(sorted[0], 11);
    EXPECT_EQ(sorted[1], 12);
    EXPECT_EQ(sorted[2], 22);
    EXPECT_EQ(sorted[3], 25);
    EXPECT_EQ(sorted[4], 34);
    EXPECT_EQ(sorted[5], 64);
    EXPECT_EQ(sorted[6], 90);
}

TEST(HeapMinTest, build_heap_constructor) {
    TVector<int> data;
    data.push_back(5);
    data.push_back(3);
    data.push_back(8);
    data.push_back(1);
    data.push_back(4);
    data.push_back(7);
    data.push_back(2);

    Heap<int> heap(data);

    EXPECT_EQ(heap.peek_min(), 1);

    EXPECT_EQ(heap.extract_min(), 1);
    EXPECT_EQ(heap.extract_min(), 2);
    EXPECT_EQ(heap.extract_min(), 3);
    EXPECT_EQ(heap.extract_min(), 4);
    EXPECT_EQ(heap.extract_min(), 5);
    EXPECT_EQ(heap.extract_min(), 7);
    EXPECT_EQ(heap.extract_min(), 8);
    EXPECT_TRUE(heap.is_empty());
}

TEST(HeapMinTest, empty_and_single_element) {
    Heap<int> heap;
    EXPECT_TRUE(heap.is_empty());
    EXPECT_THROW(heap.extract_min(), std::logic_error);
    EXPECT_THROW(heap.peek_min(), std::logic_error);

    heap.insert(42);
    EXPECT_FALSE(heap.is_empty());
    EXPECT_EQ(heap.size(), 1u);
    EXPECT_EQ(heap.peek_min(), 42);
    EXPECT_EQ(heap.extract_min(), 42);
    EXPECT_TRUE(heap.is_empty());
}

TEST(HeapMinTest, duplicate_values) {
    Heap<int> heap;
    heap.insert(5);
    heap.insert(2);
    heap.insert(5);
    heap.insert(1);
    heap.insert(2);
    heap.insert(1);

    EXPECT_EQ(heap.extract_min(), 1);
    EXPECT_EQ(heap.extract_min(), 1);
    EXPECT_EQ(heap.extract_min(), 2);
    EXPECT_EQ(heap.extract_min(), 2);
    EXPECT_EQ(heap.extract_min(), 5);
    EXPECT_EQ(heap.extract_min(), 5);
    EXPECT_TRUE(heap.is_empty());
}

TEST(HeapMinTest, clear_heap) {
    Heap<int> heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);

    EXPECT_EQ(heap.size(), 3);
    EXPECT_EQ(heap.peek_min(), 5);

    heap.clear();
    EXPECT_TRUE(heap.is_empty());
    EXPECT_EQ(heap.size(), 0);
    EXPECT_THROW(heap.peek_min(), std::logic_error);

    heap.insert(42);
    EXPECT_EQ(heap.peek_min(), 42);
}

TEST(HeapMinTest, node_heap_sort) {
    TVector<NodeHeap<int, std::string>> data;
    data.push_back(NodeHeap<int, std::string>(5, "five"));
    data.push_back(NodeHeap<int, std::string>(2, "two"));
    data.push_back(NodeHeap<int, std::string>(8, "eight"));
    data.push_back(NodeHeap<int, std::string>(1, "one"));
  /*     1
        / \
       2   8
      /
     5               */
    TVector<NodeHeap<int, std::string>> sorted = heapSort(data);

    EXPECT_EQ(sorted.size(), 4);
    EXPECT_EQ(sorted[0].data.first, 1);
    EXPECT_EQ(sorted[1].data.first, 2);
    EXPECT_EQ(sorted[2].data.first, 5);
    EXPECT_EQ(sorted[3].data.first, 8);
}


TEST(HeapMinTest, bypassing_heap_test) {
    BSTree<int, std::string> tree;

    tree.insert(50, "fifty");
    tree.insert(30, "thirty");
    tree.insert(80, "eighty");
    tree.insert(20, "twenty");
    tree.insert(40, "forty");
    tree.insert(70, "seventy");

//        50
//       /  \
//     30    80
//     / \   /
//   20  40 70
    TVector<NodeTr<int, std::string>> result;
    bypassingHeap(tree.get_root_ptr(), result);

    EXPECT_EQ(result.size(), 6);
    EXPECT_EQ(result[0].key, 20);
    EXPECT_EQ(result[1].key, 30);
    EXPECT_EQ(result[2].key, 40);
    EXPECT_EQ(result[3].key, 50);
    EXPECT_EQ(result[4].key, 70);
    EXPECT_EQ(result[5].key, 80);
}
TEST(HeapMinTest, get_heap_data) {
    TVector<int> data;
    data.push_back(3);
    data.push_back(1);
    data.push_back(4);
    data.push_back(2);

    Heap<int> heap(data);
    const TVector<int>& heapData = heap.get_data();

    EXPECT_EQ(heapData[0], 1);
    EXPECT_EQ(heap.size(), heapData.size());
}