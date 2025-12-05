#include <gtest/gtest.h>
#include "../lib_Expression/expression.h"
#include <cmath>
#include <map>

TEST(TestExpression, test_constructor_and_getters) {
    Expression expr1("2 + 3");
    EXPECT_EQ(expr1.get_infix(), "2 + 3");
    EXPECT_EQ(expr1.get_postfix(), "2 3 +");

    Expression expr2("x + y");
    EXPECT_EQ(expr2.get_infix(), "x + y");

    Expression expr3("(a + b) * c");
    EXPECT_EQ(expr3.get_infix(), "(a + b) * c");
}

TEST(TestExpression, test_get_operands) {
    Expression expr1("x");
    auto operands1 = expr1.get_operands();
    EXPECT_EQ(operands1.count(), 1);
    EXPECT_EQ((*operands1.begin()), "x");

    Expression expr2("a + b * c");
    auto operands2 = expr2.get_operands();
    EXPECT_EQ(operands2.count(), 3);

    std::vector<std::string> vars;
    auto it = operands2.begin();
    while (it != operands2.end()) {
        vars.push_back(*it);
        ++it;
    }
    std::sort(vars.begin(), vars.end());
    EXPECT_EQ(vars, (std::vector<std::string>{"a", "b", "c"}));

    Expression expr3("x * x + x");
    auto operands3 = expr3.get_operands();
    EXPECT_EQ(operands3.count(), 1); 
    EXPECT_EQ((*operands3.begin()), "x");

    Expression expr4("2 + 3");
    auto operands4 = expr4.get_operands();
    EXPECT_EQ(operands4.count(), 0); 

    Expression expr5("sin(x) + cos(y)");
    auto operands5 = expr5.get_operands();
    EXPECT_EQ(operands5.count(), 2);
}

TEST(TestExpression, test_calculate_simple) {
    Expression expr1("2 + 3");
    std::map<std::string, double> values1;
    EXPECT_DOUBLE_EQ(expr1.calculate(values1), 5.0);

    Expression expr2("4 * 5");
    std::map<std::string, double> values2;
    EXPECT_DOUBLE_EQ(expr2.calculate(values2), 20.0);

    Expression expr3("2 + 3 * 4");
    std::map<std::string, double> values3;
    EXPECT_DOUBLE_EQ(expr3.calculate(values3), 14.0);

    Expression expr4("(2 + 3) * 4");
    std::map<std::string, double> values4;
    EXPECT_DOUBLE_EQ(expr4.calculate(values4), 20.0);

    Expression expr5("10 / 2");
    std::map<std::string, double> values5;
    EXPECT_DOUBLE_EQ(expr5.calculate(values5), 5.0);

    Expression expr6("10 - 3");
    std::map<std::string, double> values6;
    EXPECT_DOUBLE_EQ(expr6.calculate(values6), 7.0);
}

TEST(TestExpression, test_calculate_with_variables) {
    Expression expr1("x + 5");
    std::map<std::string, double> values1 = { {"x", 3.0} };
    EXPECT_DOUBLE_EQ(expr1.calculate(values1), 8.0);

    Expression expr2("a + b * c");
    std::map<std::string, double> values2 = {
        {"a", 2.0},
        {"b", 3.0},
        {"c", 4.0}
    };
    EXPECT_DOUBLE_EQ(expr2.calculate(values2), 14.0);

    Expression expr3("(x + y) * z");
    std::map<std::string, double> values3 = {
        {"x", 2.0},
        {"y", 3.0},
        {"z", 4.0}
    };
    EXPECT_DOUBLE_EQ(expr3.calculate(values3), 20.0);

    Expression expr4("x ^ y");
    std::map<std::string, double> values4 = {
        {"x", 2.0},
        {"y", 3.0}
    };
    EXPECT_DOUBLE_EQ(expr4.calculate(values4), 8.0);

    Expression expr5("(a + b) * (c - d) / e");
    std::map<std::string, double> values5 = {
        {"a", 1.0},
        {"b", 2.0},
        {"c", 5.0},
        {"d", 3.0},
        {"e", 2.0}
    };
    EXPECT_DOUBLE_EQ(expr5.calculate(values5), 3.0);
}

TEST(TestExpression, test_calculate_with_functions) {
    Expression expr1("sin(0)");
    std::map<std::string, double> values1;
    EXPECT_DOUBLE_EQ(expr1.calculate(values1), 0.0);

    Expression expr2("cos(0)");
    std::map<std::string, double> values2;
    EXPECT_DOUBLE_EQ(expr2.calculate(values2), 1.0);

    Expression expr3("tan(0)");
    std::map<std::string, double> values3;
    EXPECT_DOUBLE_EQ(expr3.calculate(values3), 0.0);

    Expression expr4("ln(1)");
    std::map<std::string, double> values4;
    EXPECT_DOUBLE_EQ(expr4.calculate(values4), 0.0);

    Expression expr5("exp(0)");
    std::map<std::string, double> values5;
    EXPECT_DOUBLE_EQ(expr5.calculate(values5), 1.0);

    Expression expr6("sqrt(4)");
    std::map<std::string, double> values6;
    EXPECT_DOUBLE_EQ(expr6.calculate(values6), 2.0);

    Expression expr7("abs(-5)");
    std::map<std::string, double> values7;
    EXPECT_DOUBLE_EQ(expr7.calculate(values7), 5.0);

    
}

TEST(TestExpression, test_calculate_with_unary_minus) {

    Expression expr1("-5");
    std::map<std::string, double> values1;
    EXPECT_DOUBLE_EQ(expr1.calculate(values1), -5.0);

    Expression expr2("-x");
    std::map<std::string, double> values2 = { {"x", 3.0} };
    EXPECT_DOUBLE_EQ(expr2.calculate(values2), -3.0);

    Expression expr3("5 + -3");
    std::map<std::string, double> values3;
    EXPECT_DOUBLE_EQ(expr3.calculate(values3), 2.0);

    Expression expr4("-(2 + 3)");
    std::map<std::string, double> values4;
    EXPECT_DOUBLE_EQ(expr4.calculate(values4), -5.0);

    Expression expr5("--5");
    std::map<std::string, double> values5;
    EXPECT_DOUBLE_EQ(expr5.calculate(values5), 5.0);
}

TEST(TestExpression, test_calculate_edge_cases) {
    Expression expr1("1 / 0");
    std::map<std::string, double> values1;
    EXPECT_THROW(expr1.calculate(values1), std::runtime_error);

    Expression expr2("x + 1");
    std::map<std::string, double> values2;
    EXPECT_THROW(expr2.calculate(values2), std::runtime_error);

    Expression expr3("");
    std::map<std::string, double> values3;
    EXPECT_THROW(expr3.calculate(values3), std::runtime_error);

    Expression expr4("   ");
    std::map<std::string, double> values4;
    EXPECT_THROW(expr4.calculate(values4), std::runtime_error);
}

TEST(TestExpression, test_calculate_complex_expressions) {
   
    Expression expr2("sin(0) + cos(0) + sqrt(4)");
    std::map<std::string, double> values2;
    EXPECT_DOUBLE_EQ(expr2.calculate(values2), sin(0.0) + cos(0.0) + sqrt(4.0));

    Expression expr3("sin(cos(0))");
    std::map<std::string, double> values3;
    EXPECT_DOUBLE_EQ(expr3.calculate(values3), sin(cos(0)));

    Expression expr4("(a^2 + b^2) / (2*a*b)");
    std::map<std::string, double> values4 = { {"a", 3.0}, {"b", 4.0} };
    EXPECT_DOUBLE_EQ(expr4.calculate(values4), (9.0 + 16.0) / (2.0 * 3.0 * 4.0));
}

TEST(TestExpression, test_calculate_floating_point) {
    Expression expr1("0.1 + 0.2");
    std::map<std::string, double> values1;
    EXPECT_DOUBLE_EQ(expr1.calculate(values1), 0.3);
}

TEST(TestExpression, test_calculate_with_extra_values) {
    Expression expr("x + y");
    std::map<std::string, double> values = {
        {"x", 2.0},
        {"y", 3.0},
        {"z", 10.0},  
        {"w", 20.0}   
    };
    EXPECT_DOUBLE_EQ(expr.calculate(values), 5.0);
}

TEST(TestExpression, test_expression_with_spaces) {
    Expression expr1("  x  +  y  ");
    Expression expr2("x+y");
    Expression expr3(" x + y ");

    std::map<std::string, double> values = { {"x", 2.0}, {"y", 3.0} };

    double result1 = expr1.calculate(values);
    double result2 = expr2.calculate(values);
    double result3 = expr3.calculate(values);

    EXPECT_DOUBLE_EQ(result1, 5.0);
    EXPECT_DOUBLE_EQ(result2, 5.0);
    EXPECT_DOUBLE_EQ(result3, 5.0);
}

TEST(TestExpression, test_copy_constructor_and_assignment) {
    Expression expr1("x + y * z");
    Expression expr2 = expr1;

    std::map<std::string, double> values = { {"x", 1.0}, {"y", 2.0}, {"z", 3.0} };

    EXPECT_DOUBLE_EQ(expr1.calculate(values), 7.0);
    EXPECT_DOUBLE_EQ(expr2.calculate(values), 7.0);

    Expression expr3("a + b");
    expr3 = expr1;
    EXPECT_DOUBLE_EQ(expr3.calculate(values), 7.0);
}