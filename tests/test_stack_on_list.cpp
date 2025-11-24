#include <gtest/gtest.h>
#include "../lib_Stack_on_List/stack_list.h"

TEST(TestStackOnList, test_constructor) {
    Stack_List<int> stack;
    EXPECT_TRUE(stack.is_empty());
    ASSERT_THROW(stack.top(), std::invalid_argument);
}

TEST(TestStackOnList, test_push_pop) {
    Stack_List<int> stack;

    stack.push(3);
    stack.push(2);
    stack.push(1);

    EXPECT_FALSE(stack.is_empty());
    EXPECT_EQ(stack.size(), 3);
    EXPECT_EQ(stack.top(), 1);

    stack.pop();
    EXPECT_EQ(stack.top(), 2);

    stack.pop();
    EXPECT_EQ(stack.top(), 3);

    stack.pop();
    EXPECT_TRUE(stack.is_empty());
}

TEST(TestStackOnList, test_empty_operations) {
    Stack_List<int> stack;

    EXPECT_THROW(stack.pop(), std::invalid_argument);
    EXPECT_THROW(stack.top(), std::invalid_argument);
}

TEST(TestStackOnList, test_copy_constructor) {
    Stack_List<int> original;
    original.push(10);
    original.push(20);
    original.push(30);

    Stack_List<int> copied = original;

    EXPECT_EQ(original.size(), copied.size());
    EXPECT_EQ(original.top(), copied.top());

    original.pop();
    copied.pop();
    EXPECT_EQ(original.top(), copied.top());
}

