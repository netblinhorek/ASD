#include <gtest/gtest.h>
#include "../lib_Queue_on_List/queue_list.h"

TEST(TestQueueOnList, test_queue_list_constructor) {
	Queue_List <int> queue_list;
	EXPECT_TRUE(queue_list.is_empty_queue());
	EXPECT_EQ(queue_list.head(), nullptr);
	EXPECT_EQ(queue_list.tail(), nullptr);
}

TEST(TestQueueOnList, test_queue_list_enqueue_multiple_elements) {
	Queue_List <int> queue_list;
	queue_list.push_back_queue(3);
	EXPECT_FALSE(queue_list.is_empty_queue());
	EXPECT_EQ(queue_list.head()->value, 3);
	EXPECT_EQ(queue_list.tail()->value, 3);

	queue_list.push_back_queue(2);
	EXPECT_FALSE(queue_list.is_empty_queue());
	EXPECT_EQ(queue_list.head()->value, 3);
	EXPECT_EQ(queue_list.tail()->value, 2);

	queue_list.push_back_queue(1);
	EXPECT_FALSE(queue_list.is_empty_queue());
	EXPECT_EQ(queue_list.head()->value, 3);
	EXPECT_EQ(queue_list.tail()->value, 1);
}

TEST(TestQueueOnList, test_queue_list_dequeue_and_front) {
	Queue_List <int> queue_list;

    ASSERT_THROW(queue_list.pop_front_queue(), std::invalid_argument);
    ASSERT_THROW(queue_list.front_queue(), std::invalid_argument);

	queue_list.push_back_queue(3);
	queue_list.push_back_queue(2);
	queue_list.push_back_queue(1);

	EXPECT_EQ(queue_list.front_queue(), 3);
	queue_list.pop_front_queue();

	EXPECT_EQ(queue_list.front_queue(), 2);
	queue_list.pop_front_queue();

	EXPECT_EQ(queue_list.front_queue(), 1);
	queue_list.pop_front_queue();

	EXPECT_TRUE(queue_list.is_empty_queue());
}

TEST(TestQueueOnList, test_queue_list_enqueue) {
	Queue_List<int> queue_list;

	queue_list.push_back_queue(1);
	EXPECT_FALSE(queue_list.is_empty_queue());
	EXPECT_EQ(queue_list.head()->value, 1);
	EXPECT_EQ(queue_list.tail()->value, 1);

	queue_list.push_back_queue(2);
	EXPECT_EQ(queue_list.head()->value, 1);
	EXPECT_EQ(queue_list.tail()->value, 2);
}

TEST(TestQueueOnList, test_queue_list_dequeue) {
	Queue_List <int> queue_list;
	queue_list.push_back_queue(3);
	queue_list.push_back_queue(2);
	queue_list.push_back_queue(1);
	queue_list.pop_front_queue();
	EXPECT_FALSE(queue_list.is_empty_queue());
	EXPECT_EQ(queue_list.head()->value, 2);
	EXPECT_EQ(queue_list.tail()->value, 1);

    queue_list.pop_front_queue();
    EXPECT_FALSE(queue_list.is_empty_queue());
    EXPECT_EQ(queue_list.head()->value, 1);
    EXPECT_EQ(queue_list.tail()->value, 1);

    queue_list.pop_front_queue();
    EXPECT_TRUE(queue_list.is_empty_queue());
    EXPECT_EQ(queue_list.head(), nullptr);
    EXPECT_EQ(queue_list.tail(), nullptr);
}

TEST(TestQueueOnList, test_queue_list_copy_constructor) {
    Queue_List<int> original_queue;
    original_queue.push_back_queue(10);
    original_queue.push_back_queue(20);
    original_queue.push_back_queue(30);

   
    Queue_List<int> copied_queue = original_queue;

    
    EXPECT_EQ(original_queue.size_queue(), copied_queue.size_queue());
    ASSERT_EQ(3, copied_queue.size_queue());

    EXPECT_EQ(original_queue.front_queue(), copied_queue.front_queue());
    copied_queue.pop_front_queue();
    original_queue.pop_front_queue(); 

    EXPECT_EQ(original_queue.front_queue(), copied_queue.front_queue());
    copied_queue.pop_front_queue();
    original_queue.pop_front_queue();

    EXPECT_EQ(original_queue.front_queue(), copied_queue.front_queue());
    copied_queue.pop_front_queue();
    original_queue.pop_front_queue();

    EXPECT_TRUE(copied_queue.is_empty_queue());
    EXPECT_TRUE(original_queue.is_empty_queue());

    original_queue.push_back_queue(100);
    copied_queue.push_back_queue(200);

    EXPECT_NE(original_queue.front_queue(), copied_queue.front_queue());
}

TEST(TestQueueOnList, test_queue_list_assignment_operator) {
    Queue_List<int> original_queue;
    original_queue.push_back_queue(10);
    original_queue.push_back_queue(20);

    Queue_List<int> assigned_queue;
    assigned_queue.push_back_queue(5);
    assigned_queue = original_queue;

    EXPECT_EQ(original_queue.size_queue(), assigned_queue.size_queue());
    ASSERT_EQ(2, assigned_queue.size_queue());
    EXPECT_EQ(original_queue.front_queue(), assigned_queue.front_queue());
    assigned_queue.pop_front_queue();
    original_queue.pop_front_queue();
    EXPECT_EQ(original_queue.front_queue(), assigned_queue.front_queue());
    assigned_queue.pop_front_queue();
    original_queue.pop_front_queue();
    EXPECT_TRUE(assigned_queue.is_empty_queue());

    assigned_queue.push_back_queue(100);
    assigned_queue.push_back_queue(200);
    assigned_queue = assigned_queue;
    ASSERT_EQ(2, assigned_queue.size_queue());
    EXPECT_EQ(100, assigned_queue.front_queue());
    assigned_queue.pop_front_queue();
    EXPECT_EQ(200, assigned_queue.front_queue());
}

