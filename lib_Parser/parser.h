#pragma once

#include "../lib_List/list.h"
#include "../lib_Lexem/lexem.h"
#include <string>
#include <map>
#include <functional>

class Parser {
private:
    std::map<std::string, int> _operator_priority = {
        {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}, {"~", 4}
    };

    std::map<std::string, std::function<double(double)>> _functions = {
        {"sin", [](double x) { return sin(x); }},
        {"cos", [](double x) { return cos(x); }},
        {"tg", [](double x) { return tan(x); }},
        {"tan", [](double x) { return tan(x); }},
        {"ln", [](double x) { return log(x); }},
        {"exp", [](double x) { return exp(x); }},
        {"sqrt", [](double x) { return sqrt(x); }},
        {"abs", [](double x) { return fabs(x); }}
    };

public:
    Parser() {}

    bool is_digit(char c) { return c >= '0' && c <= '9'; }
    bool is_letter(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
    bool is_letter_or_digit(char c) { return is_letter(c) || is_digit(c); }

    std::string read_number(const std::string& expression, size_t& pos);
    std::string read_identifier(const std::string& expression, size_t& pos);

    bool is_function(const std::string& name) {
        return _functions.find(name) != _functions.end();
    }

    bool is_operator_char(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }

    bool is_bracket(char c) {
        return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']';
    }

    bool is_valid_variable_name(const std::string& name);
    bool is_unary_minus(const List<Lexem>& lexems, size_t char_pos_in_string);

    int get_priority(const std::string& op) {
        auto it = _operator_priority.find(op);
        return it != _operator_priority.end() ? it->second : 0;
    }

    List<Lexem> parse(const std::string& expression);
    List<Lexem> to_polish(const List<Lexem>& lexems);
};


