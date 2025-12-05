#include <gtest/gtest.h>
#include "../lib_Parser/parser.h"


TEST(TestParser, test_is_digit) {
    Parser parser;
    EXPECT_TRUE(parser.is_digit('0'));
    EXPECT_TRUE(parser.is_digit('5'));
    EXPECT_TRUE(parser.is_digit('9'));
    EXPECT_FALSE(parser.is_digit('a'));
    EXPECT_FALSE(parser.is_digit('Z'));
    EXPECT_FALSE(parser.is_digit('_'));
    EXPECT_FALSE(parser.is_digit(' '));
}

TEST(TestParser, test_is_letter) {
    Parser parser;
    EXPECT_TRUE(parser.is_letter('a'));
    EXPECT_TRUE(parser.is_letter('z'));
    EXPECT_TRUE(parser.is_letter('A'));
    EXPECT_TRUE(parser.is_letter('Z'));
    EXPECT_FALSE(parser.is_letter('0'));
    EXPECT_FALSE(parser.is_letter('5'));
    EXPECT_FALSE(parser.is_letter('_'));
    EXPECT_FALSE(parser.is_letter('+'));
    EXPECT_FALSE(parser.is_letter(' '));
}

TEST(TestParser, test_is_letter_or_digit) {
    Parser parser;
    EXPECT_TRUE(parser.is_letter_or_digit('a'));
    EXPECT_TRUE(parser.is_letter_or_digit('Z'));
    EXPECT_TRUE(parser.is_letter_or_digit('0'));
    EXPECT_TRUE(parser.is_letter_or_digit('9'));
    EXPECT_FALSE(parser.is_letter_or_digit('_'));
    EXPECT_FALSE(parser.is_letter_or_digit('+'));
    EXPECT_FALSE(parser.is_letter_or_digit(' '));
    EXPECT_FALSE(parser.is_letter_or_digit('.'));
}

TEST(TestParser, test_is_operator) {
    Parser parser;
    EXPECT_TRUE(parser.is_operator_char('+'));
    EXPECT_TRUE(parser.is_operator_char('-'));
    EXPECT_TRUE(parser.is_operator_char('*'));
    EXPECT_TRUE(parser.is_operator_char('/'));
    EXPECT_TRUE(parser.is_operator_char('^'));
    EXPECT_FALSE(parser.is_operator_char('a'));
    EXPECT_FALSE(parser.is_operator_char('5'));
    EXPECT_FALSE(parser.is_operator_char('('));
    EXPECT_FALSE(parser.is_operator_char(' '));
}

TEST(TestParser, test_is_bracket) {
    Parser parser;
    EXPECT_TRUE(parser.is_bracket('('));
    EXPECT_TRUE(parser.is_bracket(')'));
    EXPECT_TRUE(parser.is_bracket('['));
    EXPECT_TRUE(parser.is_bracket(']'));
    EXPECT_TRUE(parser.is_bracket('{'));
    EXPECT_TRUE(parser.is_bracket('}'));
    EXPECT_FALSE(parser.is_bracket('a'));
    EXPECT_FALSE(parser.is_bracket('+'));
    EXPECT_FALSE(parser.is_bracket('5'));
    EXPECT_FALSE(parser.is_bracket(' '));
}

TEST(TestParser, test_read_number) {
    Parser parser;
    std::string expr;
    size_t pos;

    expr = "123.45+abc";
    pos = 0;
    std::string result1 = parser.read_number(expr, pos);
    EXPECT_EQ(result1, "123.45");
    EXPECT_EQ(pos, 6);  

    expr = "0.5*2";
    pos = 0;
    std::string result2 = parser.read_number(expr, pos);
    EXPECT_EQ(result2, "0.5");
    EXPECT_EQ(pos, 3);  

    expr = "42";
    pos = 0;
    std::string result3 = parser.read_number(expr, pos);
    EXPECT_EQ(result3, "42");
    EXPECT_EQ(pos, 2);  

    expr = ".5";
    pos = 0;
    std::string result4 = parser.read_number(expr, pos);
    EXPECT_EQ(result4, "");  
    EXPECT_EQ(pos, 0);  
}
TEST(TestParser, test_read_identifier) {
    Parser parser;
    std::string expr;
    size_t pos;

    expr = "variable123+test";
    pos = 0;
    EXPECT_EQ(parser.read_identifier(expr, pos), "variable123");
    EXPECT_EQ(pos, 11);

    expr = "sin(x)";
    pos = 0;
    EXPECT_EQ(parser.read_identifier(expr, pos), "sin");
    EXPECT_EQ(pos, 3);

    expr = "123var";  
    pos = 0;
    EXPECT_EQ(parser.read_identifier(expr, pos), "");  
    EXPECT_EQ(pos, 0);

    expr = "_test";  
    pos = 0;
    EXPECT_EQ(parser.read_identifier(expr, pos), "");  
    EXPECT_EQ(pos, 0);
}

TEST(TestParser, test_is_function) {
    Parser parser;
    EXPECT_TRUE(parser.is_function("sin"));
    EXPECT_TRUE(parser.is_function("cos"));
    EXPECT_TRUE(parser.is_function("tg"));
    EXPECT_TRUE(parser.is_function("tan"));
    EXPECT_TRUE(parser.is_function("ln"));
    EXPECT_TRUE(parser.is_function("exp"));
    EXPECT_TRUE(parser.is_function("sqrt"));
    EXPECT_TRUE(parser.is_function("abs"));
    EXPECT_FALSE(parser.is_function("sinx"));
    EXPECT_FALSE(parser.is_function("variable"));
    EXPECT_FALSE(parser.is_function("123"));
    EXPECT_FALSE(parser.is_function(""));
}

TEST(TestParser, test_get_priority) {
    Parser parser;
    EXPECT_EQ(parser.get_priority("~"), 4);  
    EXPECT_EQ(parser.get_priority("^"), 3);  
    EXPECT_EQ(parser.get_priority("*"), 2); 
    EXPECT_EQ(parser.get_priority("/"), 2); 
    EXPECT_EQ(parser.get_priority("+"), 1);  
    EXPECT_EQ(parser.get_priority("-"), 1);  
    EXPECT_EQ(parser.get_priority("???"), 0); 
    EXPECT_EQ(parser.get_priority(""), 0);    
}

TEST(TestParser, test_is_valid_variable_name) {
    Parser parser;
    EXPECT_TRUE(parser.is_valid_variable_name("x"));
    EXPECT_TRUE(parser.is_valid_variable_name("variable"));
    EXPECT_TRUE(parser.is_valid_variable_name("var123"));
    EXPECT_TRUE(parser.is_valid_variable_name("temp1"));
    EXPECT_FALSE(parser.is_valid_variable_name(""));  
    EXPECT_FALSE(parser.is_valid_variable_name("123"));  
    EXPECT_FALSE(parser.is_valid_variable_name("1var"));  
    EXPECT_FALSE(parser.is_valid_variable_name("var-name"));  
    EXPECT_FALSE(parser.is_valid_variable_name("var name"));  
    EXPECT_FALSE(parser.is_valid_variable_name("var_name"));  
}

TEST(TestParser, test_is_unary_minus) {
    Parser parser;
    List<Lexem> lexems;
    std::string expr;

    expr = "-5";
    EXPECT_TRUE(parser.is_unary_minus(lexems, 0));

    lexems.push_back(Lexem("(", OpenBracket, 0.0));
    expr = "(-5)";
    EXPECT_TRUE(parser.is_unary_minus(lexems, 1));

    lexems.clear();
    lexems.push_back(Lexem("5", Constant, 5.0));
    lexems.push_back(Lexem("+", Operator, 0.0));
    expr = "5+-3";
    EXPECT_TRUE(parser.is_unary_minus(lexems, 2));

    lexems.clear();
    lexems.push_back(Lexem("x", Variable, 0.0));
    expr = "x-3";
    EXPECT_FALSE(parser.is_unary_minus(lexems, 1));

    lexems.clear();
    lexems.push_back(Lexem("5", Constant, 5.0));
    expr = "5-3";
    EXPECT_FALSE(parser.is_unary_minus(lexems, 1));
}

TEST(TestParser, test_parse_simple_number) {
    Parser parser;
    List<Lexem> lexems;

    lexems = parser.parse("42");
    EXPECT_EQ(lexems.count(), 1);

    auto it = lexems.begin();
    EXPECT_EQ((*it).get_name(), "42");
    EXPECT_EQ((*it).get_type(), Constant);
}
TEST(TestParser, test_parse_simple_unknown) {
    Parser parser;
    List<Lexem> lexems;

    lexems = parser.parse("x");
    EXPECT_EQ(lexems.count(), 1);
    auto it = lexems.begin();
    EXPECT_EQ((*it).get_name(), "x");
    EXPECT_EQ((*it).get_type(), Variable);
}
TEST(TestParser, test_parse_simple_add) {
    Parser parser;
    List<Lexem> lexems;

    lexems = parser.parse("2+2");
    EXPECT_EQ(lexems.count(), 3);

    auto it = lexems.begin();
    EXPECT_EQ((*it).get_name(), "2");
    EXPECT_EQ((*it).get_type(), Constant);

    ++it;
    EXPECT_EQ((*it).get_name(), "+");
    EXPECT_EQ((*it).get_type(), Operator);

    ++it;
    EXPECT_EQ((*it).get_name(), "2");
    EXPECT_EQ((*it).get_type(), Constant);
}


TEST(TestParser, test_parse_with_functions) {
    Parser parser;
    List<Lexem> lexems;

    lexems = parser.parse("sin(x)");
    EXPECT_EQ(lexems.count(), 4);

    auto it = lexems.begin();

    EXPECT_EQ((*it).get_name(), "sin");
    EXPECT_EQ((*it).get_type(), Function);
    ++it;

    EXPECT_EQ((*it).get_name(), "(");
    EXPECT_EQ((*it).get_type(), OpenBracket);
    ++it;

    EXPECT_EQ((*it).get_name(), "x");
    EXPECT_EQ((*it).get_type(), Variable);
    ++it;

    EXPECT_EQ((*it).get_name(), ")");
    EXPECT_EQ((*it).get_type(), ClosedBracket);
}

TEST(TestParser, test_parse_unary_minus) {
    Parser parser;
    List<Lexem> lexems;

    lexems = parser.parse("-5");
    auto it = lexems.begin();
    EXPECT_EQ(lexems.count(), 2);
    EXPECT_EQ((*it).get_name(), "~");
    EXPECT_EQ((*it).get_type(), UnOperator);
    it++;
    EXPECT_EQ((*it).get_name(), "5");
    EXPECT_EQ((*it).get_type(), Constant);
}

TEST(TestParser, test_parse_unary_minus_with_brackets) {
    Parser parser;
    List<Lexem> lexems;

    lexems = parser.parse("(-x)");
    auto it = lexems.begin();
    EXPECT_EQ(lexems.count(), 4);
    EXPECT_EQ((*it).get_name(), "(");
    EXPECT_EQ((*it).get_type(), OpenBracket);
    it++;
    EXPECT_EQ((*it).get_name(), "~");
    EXPECT_EQ((*it).get_type(), UnOperator);
    it++;
    EXPECT_EQ((*it).get_name(), "x");
    EXPECT_EQ((*it).get_type(), Variable);
    it++;
    EXPECT_EQ((*it).get_name(), ")");
    EXPECT_EQ((*it).get_type(), ClosedBracket);
}

TEST(TestParser, test_parse_add_with_unary_minus) {
    Parser parser;
    List<Lexem> lexems;

    lexems = parser.parse("5+-3");
    EXPECT_EQ(lexems.count(), 4);

    auto it = lexems.begin();

    EXPECT_EQ((*it).get_name(), "5");
    EXPECT_EQ((*it).get_type(), Constant);
    it++;
    EXPECT_EQ((*it).get_name(), "+");
    EXPECT_EQ((*it).get_type(), Operator);
    it++;
    EXPECT_EQ((*it).get_name(), "~");
    EXPECT_EQ((*it).get_type(), UnOperator);
    it++;
    EXPECT_EQ((*it).get_name(), "3");
    EXPECT_EQ((*it).get_type(), Constant);
}


TEST(TestParser, test_parse_invalid_expression) {
    Parser parser;

    EXPECT_THROW(parser.parse("12.34.56"), std::runtime_error);
    EXPECT_THROW(parser.parse("x @ y"), std::runtime_error);
}

TEST(TestParser, test_to_polish_exp_with_brackets) {
   
    Parser parser;
   
    List<Lexem> lexems3 = parser.parse("(2+3)*4");
    List<Lexem> polish3 = parser.to_polish(lexems3);
    EXPECT_EQ(polish3.count(), 5);
    auto it = polish3.begin();
    EXPECT_EQ((*it).get_name(), "2");
    it++;
    EXPECT_EQ((*it).get_name(), "3");
    it++;
    EXPECT_EQ((*it).get_name(), "+");
    it++;
    EXPECT_EQ((*it).get_name(), "4");
    it++;
    EXPECT_EQ((*it).get_name(), "*");
}

TEST(TestParser, test_to_polish_with_function) {
    Parser parser;

    List<Lexem> lexems = parser.parse("sin(x+y)");
    List<Lexem> polish = parser.to_polish(lexems);
    EXPECT_EQ(polish.count(), 4);
    auto it = polish.begin();
    EXPECT_EQ((*it).get_name(), "x");
    it++;
    EXPECT_EQ((*it).get_name(), "y");
    it++;
    EXPECT_EQ((*it).get_name(), "+");
    it++;
    EXPECT_EQ((*it).get_name(), "sin");
}
