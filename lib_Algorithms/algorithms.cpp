#include <iostream>
#include "../lib_Stack/stack.h"

bool check_of_brackets(const std::string& str) {
    Stack<char> stack(str.length());

    for (int i = 0; i < str.length(); i++) {
        char c = str[i];

        if (c == '(' || c == '{' || c == '[') {
            stack.push(c);
        }
        else if (c == ')') {
            if (stack.is_empty()) return false;
            char top = stack.top();
            if (top != '(') return false;
            stack.pop();
        }
        else if (c == '}') {
            if (stack.is_empty()) return false;
            char top = stack.top();
            if (top != '{') return false;
            stack.pop();
        }
        else if (c == ']') {
            if (stack.is_empty()) return false;
            char top = stack.top();
            if (top != '[') return false;
            stack.pop();
        }
    }

    return stack.is_empty();
}

void algorithms_read_expression(const std::string& str) {
    if (!check_of_brackets(str)) {
        throw std::logic_error("Unbalanced brackets in expression");
    }

    bool expect_operand = true;

    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        if (c == ' ') continue;

        if (c == '(' || c == '{' || c == '[') {
            if (!expect_operand) {
                throw std::logic_error("Unexpected opening bracket after operand");
            }
            expect_operand = true;
            continue;
        }

        if (c == ')' || c == '}' || c == ']') {
            if (expect_operand) {
                throw std::logic_error("Unexpected closing bracket");
            }
            expect_operand = false;
            continue;
        }

        if (expect_operand) {
            if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
                expect_operand = false;
            }
            else if ('0' <= c && c <= '9') {
                while (i + 1 < str.length() && '0' <= str[i + 1] && str[i + 1] <= '9') {
                    i++;
                }
                expect_operand = false;
            }
            else {
                throw std::logic_error("Expected operand but found: " + std::string(1, c));
            }
        }
        else {
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                expect_operand = true;
            }
            else {
                throw std::logic_error("Expected operator but found: " + std::string(1, c));
            }
        }
    }

    if (expect_operand) {
        throw std::logic_error("Expression ends with operator");
    }
}