#include <gtest/gtest.h>
#include "../lib_Stack/stack.h"
#include <stdexcept>
#include <cmath>


TEST(TestStack, test_constructor) {
    Stack<int> stack(5);
    EXPECT_TRUE(stack.is_empty());  
    EXPECT_FALSE(stack.is_full());
}
TEST(TestStack, test_constructor_throw) {
    EXPECT_THROW(Stack<int> stack(-5),
        std::logic_error);
}
TEST(TestStack, test_constructor_copy_1) {
        Stack<int> stack1(5);
        Stack<int> stack2(stack1);

        EXPECT_TRUE(stack2.is_empty());
        EXPECT_EQ(stack1.is_empty(), stack2.is_empty());
}
TEST(TestStack, test_constructor_copy_2) {
    Stack<int> stack1(3);
    stack1.push(10);
    stack1.push(20);
    stack1.push(30);

    Stack<int> stack2(stack1);
    EXPECT_EQ(stack2.top(), 30);
    stack2.pop();
    EXPECT_EQ(stack2.top(), 20);
    stack2.pop();
    EXPECT_EQ(stack2.top(), 10);

    stack2.pop();
    EXPECT_TRUE(stack2.is_empty());

    EXPECT_FALSE(stack1.is_empty());
    EXPECT_EQ(stack1.top(), 30);
}

TEST(TestStack, test_constructor_copy_throw) {
}
TEST(TestStack, test_is_push) {
    Stack<int> stack(2);
    stack.push(4);
    stack.push(5);
    EXPECT_FALSE(stack.is_empty());
}

TEST(TestStack, test_is_push_throw) {
    Stack<int> stack(2);
    stack.push(4);
    stack.push(5);
    EXPECT_THROW(stack.push(3), std::logic_error);
}
TEST(TestStack, test_is_pop) {
    Stack<int> stack(3);
    stack.push(1);
    stack.push(2);
    stack.pop();
    EXPECT_EQ(stack.top(), 1);
}
TEST(TestStack, test_is_pop_throw) {
    Stack<int> stack(3);
    EXPECT_THROW(stack.pop(), std::logic_error);
}
TEST(TestStack, test_is_top) {
    Stack<int> stack(3);
    stack.push(42);
    EXPECT_EQ(stack.top(), 42);
}

TEST(TestStack, test_is_top_throw) {
    Stack<int> stack(3);
    EXPECT_THROW(stack.top(), std::logic_error);
}

TEST(TestStack, test_is_empty) {
    Stack<int> stack(3);
    EXPECT_TRUE(stack.is_empty());
}

TEST(TestStack, test_is_empty_throw) {
    Stack<int> stack(3);
    stack.push(1);
    EXPECT_FALSE(stack.is_empty());
}

TEST(TestStack, test_is_full) {
    Stack<int> stack(3);

    stack.push(4);
    stack.push(5);
    stack.push(6); 

    EXPECT_TRUE(stack.is_full());
}
TEST(TestStack, test_is_full_throw) {
    Stack<int> stack(3);

    stack.push(4);
    stack.push(5);
    stack.push(6);
    EXPECT_THROW(stack.push(7), std::logic_error);
}
TEST(TestStack, test_is_clear) {
    Stack<int> stack(3);
    stack.push(1);
    stack.push(2);
    stack.clear();
    EXPECT_TRUE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
}