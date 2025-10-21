//#include <iostream>
//#include "../lib_Stack/stack.h"
//#include "algorithms.cpp"
//
//void algorithms_read_expression(const std::string& str) {
//    Stack<char> stack(str.length());
//
//    for (int i = 0; i < str.length(); i++) {
//        char c = str[i];
//        if (c == '(' || c == '{' || c == '[') {
//            stack.push(c);
//        if (65 <= c || c <= 122 || ) {
//            stack.push(c);
//            if (c == '*' || c == '^' || c == '+' || c == '/' || c == '-') {
//                stack.push(c);
//            }
//            else if(c == ')')
//
//
//
//
//        }
//        else if (') {
//            if (stack.is_empty()) return false;
//
//            char top = stack.peek();
//            bool is_match = (c == ')' && top == '(') ||
//                (c == '}' && top == '{') ||
//                (c == ']' && top == '[');
//
//            if (is_match) {
//                stack.pop();
//            }
//            else {
//                return false;
//            }
//        }
//    }
//
//    return stack.is_empty();
//
//
//}
//
