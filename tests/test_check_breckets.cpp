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


TEST(EquationsTest, test_equations) {
    Stack<char> stack(10);

    EXPECT_NO_THROW(algorithms_read_expression("x+y"));
    EXPECT_NO_THROW(algorithms_read_expression("a+b*c"));
    EXPECT_NO_THROW(algorithms_read_expression("x + y")); 
    EXPECT_NO_THROW(algorithms_read_expression("x+y"));
    EXPECT_NO_THROW(algorithms_read_expression("a+b*c"));
    EXPECT_NO_THROW(algorithms_read_expression("x + y"));
    EXPECT_NO_THROW(algorithms_read_expression("(x + y)"));
}
TEST(EquationsTest, test_an_example_with_a_lot_of_parentheses) {
    EXPECT_NO_THROW(algorithms_read_expression("(x + y)+(3+x)"));
    EXPECT_NO_THROW(algorithms_read_expression("3*(15 + (x+y)*(2*x - 7*y^2))"));
}

TEST(EquationsTest, test_equations_throw) {
    EXPECT_THROW(algorithms_read_expression("+ y"), std::logic_error);
    EXPECT_THROW(algorithms_read_expression("x^"), std::logic_error);
    EXPECT_THROW(algorithms_read_expression("a+"), std::logic_error);
    EXPECT_THROW(algorithms_read_expression("x y"), std::logic_error);
    EXPECT_THROW(algorithms_read_expression("x(y + z)"), std::logic_error);
}

TEST(EquationsTest, test_an_example_with_a_lot_of_parentheses_throw) {
    EXPECT_THROW(algorithms_read_expression("3*(15 + (x y)*(2*x - 7*y^2))"), std::logic_error);
    EXPECT_THROW(algorithms_read_expression("3*(15 + (x y)*(2*x - 7*y^))"), std::logic_error);
    EXPECT_THROW(algorithms_read_expression("((x+y)*(x-y)))"), std::logic_error);
    EXPECT_THROW(algorithms_read_expression("(x*x+y^2))*(8+(y-3))"), std::logic_error);
}

