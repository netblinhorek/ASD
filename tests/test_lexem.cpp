#include <gtest/gtest.h>
#include "../lib_Lexem/lexem.h"

TEST(TestLexem, test_default_constructor) {
    Lexem lexem;
    EXPECT_EQ(lexem.get_name(), "");
    EXPECT_EQ(lexem.get_type(), Constant);
    EXPECT_EQ(lexem.get_value(), 0.0);
    EXPECT_EQ(lexem.get_priority(), -1);
}
double test_func(double x) { return x * 2; }

TEST(TestLexem, test_main_constructor) {
    

    Lexem lexem("test", Function, 5.5, 3, test_func);
    EXPECT_EQ(lexem.get_name(), "test");
    EXPECT_EQ(lexem.get_type(), Function);
    EXPECT_EQ(lexem.get_value(), 5.5);
    EXPECT_EQ(lexem.get_priority(), 3);
}

TEST(TestLexem, test_double_constructor) {
    Lexem lexem(42.7);
    EXPECT_EQ(lexem.get_name(), "42.700000");
    EXPECT_EQ(lexem.get_type(), Constant);
    EXPECT_EQ(lexem.get_value(), 42.7);
    EXPECT_EQ(lexem.get_priority(), -1);
}

TEST(TestLexem, test_string_variable_constructor) {
    Lexem lexem("x", Variable);
    EXPECT_EQ(lexem.get_name(), "x");
    EXPECT_EQ(lexem.get_type(), Variable);
    EXPECT_EQ(lexem.get_value(), DBL_MAX);
    EXPECT_EQ(lexem.get_priority(), -1);
}

TEST(TestLexem, test_operator_constructor) {
    Lexem lexem("*", 2);
    EXPECT_EQ(lexem.get_name(), "*");
    EXPECT_EQ(lexem.get_type(), Operator);
    EXPECT_EQ(lexem.get_value(), DBL_MAX);
    EXPECT_EQ(lexem.get_priority(), 2);
}
double my_sin(double x) { return sin(x); }
TEST(TestLexem, test_function_constructor) {
    

    Lexem lexem("sin", my_sin);
    EXPECT_EQ(lexem.get_name(), "sin");
    EXPECT_EQ(lexem.get_type(), Function);
    EXPECT_EQ(lexem.get_value(), DBL_MAX);
    EXPECT_EQ(lexem.get_priority(), 0);
}

TEST(TestLexem, test_bracket_constructor) {
    Lexem lexem("(", OpenBracket);
    EXPECT_EQ(lexem.get_name(), "(");
    EXPECT_EQ(lexem.get_type(), OpenBracket);
    EXPECT_EQ(lexem.get_value(), DBL_MAX);
    EXPECT_EQ(lexem.get_priority(), -1);

    Lexem lexem2(")", ClosedBracket);
    EXPECT_EQ(lexem2.get_name(), ")");
    EXPECT_EQ(lexem2.get_type(), ClosedBracket);
}