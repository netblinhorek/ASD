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
            char top = stack.top(); // Сначала смотрим что на вершине
            if (top != '(') return false;
            stack.pop(); // Затем удаляем
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