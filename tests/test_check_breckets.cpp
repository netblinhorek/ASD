#include <gtest/gtest.h>
#include "../lib_Stack/stack.h"
#include <stdexcept>
#include <cmath>



TEST(BracketCheckTest, test_pair_removal) {
    Stack<char> stack(10);

    stack.push('(');  

    if (!stack.is_empty()) {
        stack.pop();  
    }

    EXPECT_TRUE(stack.is_empty());
}
TEST(BracketCheckTest, test_simple_pair) {
    EXPECT_TRUE(check_of_brackets("()"));

    EXPECT_TRUE(check_of_brackets("{}"));
    EXPECT_TRUE(check_of_brackets("[]"));
    EXPECT_FALSE(check_of_brackets("("));   
    EXPECT_FALSE(check_of_brackets(")"));   
    EXPECT_FALSE(check_of_brackets("(}"));  
}
TEST(BracketCheckTest, test_combination) {
    EXPECT_TRUE(check_of_brackets("({[([])]})"));
    EXPECT_FALSE(check_of_brackets("((((())})"));
}