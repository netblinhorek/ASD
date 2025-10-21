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
    Queue<int> queue(10);
    queue.push(4);
    queue.push(5);
    queue.pop();
    queue.push(7);

    EXPECT_EQ(7, queue.tail());
    EXPECT_EQ(queue.head(), 5);
    EXPECT_FALSE(queue.is_empty());
}
TEST(TestQueue, test_push_in_full_throw) {
    Queue<int> queue(3);

    queue.push(4);
    queue.push(5);
    queue.push(6);

    EXPECT_TRUE(queue.is_full());
    EXPECT_THROW(queue.push(7), std::logic_error);
}
TEST(TestQueue, test_is_pop) {
    Queue<int> queue(3);
    queue.push(1);
    queue.push(2);
    queue.pop();
    EXPECT_EQ(queue.head(), 2);
}
TEST(TestQueue, test_is_push_throw) {
    Queue<int> queue(2);
    queue.push(4);
    queue.push(5);
    EXPECT_THROW(queue.push(3), std::logic_error);
}


TEST(TestQueue, test_for_empty_object) {
    Queue<int> queue(3);
    EXPECT_TRUE(queue.is_empty());
    EXPECT_THROW(queue.head(), std::logic_error);
    EXPECT_FALSE(queue.is_full());
    EXPECT_THROW(queue.pop(), std::logic_error);

}



TEST(TestQueue, test_is_clear) {
    Queue<int> queue(3);
    queue.push(1);
    queue.push(2);
    queue.clear();
    EXPECT_TRUE(queue.is_empty());
    EXPECT_FALSE(queue.is_full());
    ASSERT_NO_THROW(queue.push(42));
}