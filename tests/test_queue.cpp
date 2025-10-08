#include <gtest/gtest.h>
#include "../lib_Queue/queue.h"
#include <stdexcept>
#include <cmath>


TEST(TestQueue, test_constructor) {
    Queue<int> queue(5);
    EXPECT_TRUE(queue.is_empty());
    EXPECT_FALSE(queue.is_full());
}
TEST(TestQueue, test_constructor_throw) {
    EXPECT_THROW(Queue<int> queue(-5),
        std::logic_error);
}
TEST(TestQueue, test_is_push) {
    Queue<int> queue(2);
    queue.push(4);
    queue.push(5);
    EXPECT_FALSE(queue.is_empty());
}

TEST(TestQueue, test_is_push_throw) {
    Queue<int> queue(2);
    queue.push(4);
    queue.push(5);
    EXPECT_THROW(queue.push(3), std::logic_error);
}
TEST(TestQueue, test_is_pop) {
    Queue<int> queue(3);
    queue.push(1);
    queue.push(2);
    queue.pop();
    EXPECT_EQ(queue.top(), 2);
}
TEST(TestQueue, test_is_pop_throw) {
    Queue<int> queue(3);
    EXPECT_THROW(queue.pop(), std::logic_error);
}
TEST(TestQueue, test_is_top) {
    Queue<int> queue(3);
    queue.push(42);
    EXPECT_EQ(queue.top(), 42);
}

TEST(TestQueue, test_is_top_throw) {
    Queue<int> queue(3);
    EXPECT_THROW(queue.top(), std::logic_error);
}

TEST(TestQueue, test_is_empty) {
    Queue<int> queue(3);
    EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueue, test_is_empty_throw) {
    Queue<int> queue(3);
    queue.push(1);
    EXPECT_FALSE(queue.is_empty());
}

TEST(TestQueue, test_is_full) {
    Queue<int> queue(3);

    queue.push(4);
    queue.push(5);
    queue.push(6);

    EXPECT_TRUE(queue.is_full());
}
TEST(TestQueue, test_is_full_throw) {
    Queue<int> queue(3);

    queue.push(4);
    queue.push(5);
    queue.push(6);
    EXPECT_THROW(queue.push(7), std::logic_error);
}
TEST(TestQueue, test_is_clear) {
    Queue<int> queue(3);
    queue.push(1);
    queue.push(2);
    queue.clear();
    EXPECT_TRUE(queue.is_empty());
    EXPECT_FALSE(queue.is_full());
}