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
TEST(TestStack, test_is_push) {
    Stack<int> stack(10);
    stack.push(4);
    stack.push(5);
    stack.pop();
    stack.push(7);

    EXPECT_EQ(stack.top(), 7);
    EXPECT_FALSE(stack.is_empty());
}
TEST(TestStack, test_push_in_full_throw) {
    Stack<int> stack(3);

    stack.push(4);
    stack.push(5);
    stack.push(6);

    EXPECT_TRUE(stack.is_full());
    EXPECT_THROW(stack.push(7), std::logic_error);
}
TEST(TestStack, test_is_pop) {
    Stack<int> stack(3);
    stack.push(1);
    stack.push(2);
    stack.pop();
    EXPECT_EQ(stack.top(), 1);
}

TEST(TestStack, test_for_empty_object) {
    Stack<int> stack(3);
    EXPECT_TRUE(stack.is_empty());
    EXPECT_THROW(stack.top(), std::logic_error);
    EXPECT_FALSE(stack.is_full());
    EXPECT_THROW(stack.pop(), std::logic_error);

}

TEST(TestStack, test_is_clear) {
    Stack<int> stack(3);
    stack.push(1);
    stack.push(2);
    stack.clear();
    EXPECT_TRUE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
    ASSERT_NO_THROW(stack.push(42));
}