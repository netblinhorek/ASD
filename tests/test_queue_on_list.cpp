#include <gtest/gtest.h>
#include "../lib_Queue_on_List/queue_list.h"

TEST(TestQueueOnList, test_constructor) {
    Queue_List<int> queue;
    EXPECT_TRUE(queue.is_empty_queue());
    EXPECT_EQ(queue.head(), nullptr);
    EXPECT_EQ(queue.tail(), nullptr);
}

TEST(TestQueueOnList, test_enqueue_dequeue) {
    Queue_List<int> queue;

    queue.push_back_queue(1);
    queue.push_back_queue(2);
    queue.push_back_queue(3);

    EXPECT_FALSE(queue.is_empty_queue());
    EXPECT_EQ(queue.size_queue(), 3);
    EXPECT_EQ(queue.front_queue(), 1);

    queue.pop_front_queue();
    EXPECT_EQ(queue.front_queue(), 2);

    queue.pop_front_queue();
    EXPECT_EQ(queue.front_queue(), 3);

    queue.pop_front_queue();
    EXPECT_TRUE(queue.is_empty_queue());
}

TEST(TestQueueOnList, test_empty_operations) {
    Queue_List<int> queue;

    EXPECT_THROW(queue.pop_front_queue(), std::invalid_argument);
    EXPECT_THROW(queue.front_queue(), std::invalid_argument);
}

TEST(TestQueueOnList, test_copy_constructor) {
    Queue_List<int> original;
    original.push_back_queue(10);
    original.push_back_queue(20);
    original.push_back_queue(30);

    Queue_List<int> copied = original;

    EXPECT_EQ(original.size_queue(), copied.size_queue());
    EXPECT_EQ(original.front_queue(), copied.front_queue());

    original.pop_front_queue();
    copied.pop_front_queue();
    EXPECT_EQ(original.front_queue(), copied.front_queue());
}
