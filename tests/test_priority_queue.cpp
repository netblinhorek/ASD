#include <gtest/gtest.h>
#include "../lib_PriorityQueue/priority_queue.h"

TEST(PriorityQueueTest, test_empty_queue) {
    PriorityQueue<std::string> priority_queue;

    EXPECT_TRUE(priority_queue.is_empty());
    EXPECT_EQ(priority_queue.size(), 0);
}

TEST(PriorityQueueTest, test_push_pop_different_priorities) {
    PriorityQueue<std::string> priority_queue;

    priority_queue.push("three", 3);
    priority_queue.push("one", 1);      
    priority_queue.push("four", 4);
    priority_queue.push("two", 2);

    EXPECT_FALSE(priority_queue.is_empty());
    EXPECT_EQ(priority_queue.size(), 4);

    auto result1 = priority_queue.pop();
    EXPECT_EQ(result1, "one");

    auto result2 = priority_queue.pop();
    EXPECT_EQ(result2, "two");

    auto result3 = priority_queue.pop();
    EXPECT_EQ(result3, "three");

    auto result4 = priority_queue.pop();
    EXPECT_EQ(result4, "four");

    EXPECT_TRUE(priority_queue.is_empty());
}


TEST(PriorityQueueTest, test_clear_method) {
    PriorityQueue<std::string> priority_queue;

    priority_queue.push("ten", 10);
    priority_queue.push("twenty", 20);
    priority_queue.clear();

    EXPECT_TRUE(priority_queue.is_empty());
    EXPECT_EQ(priority_queue.size(), 0);

    priority_queue.push("five", 5);
    EXPECT_FALSE(priority_queue.is_empty());
    EXPECT_EQ(priority_queue.size(), 1);
}

TEST(PriorityQueueTest, test_fifo_for_equal_priorities) {
    PriorityQueue<std::string> priority_queue;

    priority_queue.push("first", 5);
    priority_queue.push("second", 5);
    priority_queue.push("third", 5);

    auto result1 = priority_queue.pop();
    EXPECT_EQ(result1, "first");

    auto result2 = priority_queue.pop();
    EXPECT_EQ(result2, "second");

    auto result3 = priority_queue.pop();
    EXPECT_EQ(result3, "third");
}

TEST(PriorityQueueTest, test_mixed_priorities_with_fifo) {
    PriorityQueue<std::string> priority_queue;

    priority_queue.push("two-A", 2);
    priority_queue.push("three-A", 3);
    priority_queue.push("two-B", 2);
    priority_queue.push("three-B", 3);
    priority_queue.push("one", 1);  

    auto result1 = priority_queue.pop();
    EXPECT_EQ(result1, "one");

    auto result2 = priority_queue.pop();
    EXPECT_EQ(result2, "two-A");

    auto result3 = priority_queue.pop();
    EXPECT_EQ(result3, "two-B");

    auto result4 = priority_queue.pop();
    EXPECT_EQ(result4, "three-A");

    auto result5 = priority_queue.pop();
    EXPECT_EQ(result5, "three-B");
}

TEST(PriorityQueueTest, test_priority_1_is_highest) {
    PriorityQueue<std::string> pq;

    pq.push("low", 5);
    pq.push("high", 1);
    pq.push("medium", 3);
    pq.push("high-medium", 2);

    EXPECT_EQ(pq.pop(), "high");        
    EXPECT_EQ(pq.pop(), "high-medium"); 
    EXPECT_EQ(pq.pop(), "medium");     
    EXPECT_EQ(pq.pop(), "low");        
}

TEST(PriorityQueueTest, test_with_integer_values) {
    PriorityQueue<int> pq;

    pq.push(100, 3);
    pq.push(50, 1);   
    pq.push(75, 2);
    pq.push(200, 4);

    EXPECT_EQ(pq.pop(), 50);
    EXPECT_EQ(pq.pop(), 75);
    EXPECT_EQ(pq.pop(), 100);
    EXPECT_EQ(pq.pop(), 200);
}


TEST(PriorityQueueTest, test_exceptions) {
    PriorityQueue<std::string> pq;

    EXPECT_THROW(pq.pop(), std::logic_error);

    pq.push("test", 1);
    EXPECT_NO_THROW(pq.pop());
    EXPECT_THROW(pq.pop(), std::logic_error);
}


TEST(PriorityQueueTest, test_print) {
    PriorityQueue<std::string> pq;
    pq.push("A", 3);
    pq.push("B", 1);
    pq.push("C", 2);

    EXPECT_NO_THROW(pq.print());
}

TEST(PriorityQueueTest, test_complex_sequence) {
    PriorityQueue<std::string> pq;

    pq.push("first", 2);
    pq.push("second", 1); 

    pq.push("third", 1);  
    EXPECT_EQ(pq.size(), 3);

    EXPECT_EQ(pq.pop(), "second");  
    EXPECT_EQ(pq.pop(), "third");   
    EXPECT_EQ(pq.pop(), "first");   

    EXPECT_TRUE(pq.is_empty());
}

TEST(PriorityQueueTest, test_negative_priorities) {
    PriorityQueue<std::string> pq;

    pq.push("lowest", 10);
    pq.push("highest", -5);   
    pq.push("medium", 0);

    EXPECT_EQ(pq.pop(), "highest"); 
    EXPECT_EQ(pq.pop(), "medium");  
    EXPECT_EQ(pq.pop(), "lowest");  
}

TEST(PriorityQueueTest, test_large_data) {
    PriorityQueue<int> pq;
    const int DATA_SIZE = 1000;

    for (int i = DATA_SIZE; i > 0; --i) {
        pq.push(i, i);
    }

    EXPECT_EQ(pq.size(), DATA_SIZE);

    for (int i = 1; i <= DATA_SIZE; ++i) {
        EXPECT_EQ(pq.pop(), i);
    }

    EXPECT_TRUE(pq.is_empty());
}