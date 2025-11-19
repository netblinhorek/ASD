#include <gtest/gtest.h>
#include "../lib_Stack_on_List/stack_list.h"

TEST(TestStackOnList, test_stack_list_constructor) {
	Stack_List <int> stack_list;
	EXPECT_TRUE(stack_list.is_empty());
	ASSERT_THROW(stack_list.top(), std::invalid_argument);

}

TEST(TestStackOnList, test_stack_list_copy_constructor) {
    Stack_List<int> original_stack;
    original_stack.push(10);
    original_stack.push(20);
    original_stack.push(30); 

    Stack_List<int> copied_stack = original_stack;

    EXPECT_EQ(original_stack.size(), copied_stack.size());
    ASSERT_EQ(3, copied_stack.size());

    EXPECT_EQ(original_stack.top(), copied_stack.top());
    copied_stack.pop();
    original_stack.pop();

    EXPECT_EQ(original_stack.top(), copied_stack.top());
    copied_stack.pop();
    original_stack.pop();

    EXPECT_EQ(original_stack.top(), copied_stack.top());
    copied_stack.pop();
    original_stack.pop();

    EXPECT_TRUE(copied_stack.is_empty());
    EXPECT_TRUE(original_stack.is_empty());

    original_stack.push(100);
    copied_stack.push(200);

    EXPECT_NE(original_stack.top(), copied_stack.top());
}

TEST(TestStackOnList, test_stack_list_assignment_operator) {
    Stack_List<int> original_stack;
    original_stack.push(10);
    original_stack.push(20);

    Stack_List<int> assigned_stack;
    assigned_stack.push(5); 
    assigned_stack = original_stack;


    EXPECT_EQ(original_stack.size(), assigned_stack.size());
    ASSERT_EQ(2, assigned_stack.size());
    EXPECT_EQ(original_stack.top(), assigned_stack.top());
    assigned_stack.pop();
    original_stack.pop();
    EXPECT_EQ(original_stack.top(), assigned_stack.top());
    assigned_stack.pop();
    original_stack.pop();
    EXPECT_TRUE(assigned_stack.is_empty());

    assigned_stack.push(100);
    assigned_stack.push(200);
    assigned_stack = assigned_stack;
    ASSERT_EQ(2, assigned_stack.size());
    EXPECT_EQ(200, assigned_stack.top()); 
    assigned_stack.pop();
    EXPECT_EQ(100, assigned_stack.top());
}

TEST(TestStackOnList, test_list_push_front_stack) {
	Stack_List <int> stack_list;
	stack_list.push(3);
	EXPECT_FALSE(stack_list.is_empty());
	EXPECT_EQ(stack_list.top(), 3);


	stack_list.push(2);
	EXPECT_FALSE(stack_list.is_empty());
	EXPECT_EQ(stack_list.top(), 2);
}

TEST(TestStackOnList, test_list_pop_front_stack_throw) {
	Stack_List <int> stack_list;
	ASSERT_THROW(stack_list.pop(), std::invalid_argument);
	stack_list.push(3);
	stack_list.push(2);
	stack_list.push(1);
	stack_list.pop();
	EXPECT_FALSE(stack_list.is_empty());
	EXPECT_EQ(stack_list.top(), 2);
}