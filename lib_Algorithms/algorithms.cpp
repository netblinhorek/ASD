#include <iostream>
#include "../lib_Stack/stack.h"

bool check_of_brackets(const std::string& str) {
    Stack<char> stack(str.length());

    for (int i = 0; i < str.length(); i++) {
        char c = str[i];

        if (c == '(' || c == '{' || c == '[') {
            stack.push(c);
        }
        else if (c == ')' || c == '}' || c == ']') {
            if (stack.is_empty()) return false;

            char top = stack.peek();
            bool is_match = (c == ')' && top == '(') ||
                (c == '}' && top == '{') ||
                (c == ']' && top == '[');

            if (is_match) {
                stack.pop();
            }
            else {
                return false;
            }
        }
    }

    return stack.is_empty();
}


void number_of_brackets(const std::string& str) {
    int open_brackets = 0;
    int close_brackets = 0;

    for (int i = 0; i < str.length(); i++) {
        char c = str[i];

        if (c == '(' || c == '{' || c == '[') {
            open_brackets++;
        }
        else if (c == ')' || c == '}' || c == ']') {
            close_brackets++;
        }
    }
}