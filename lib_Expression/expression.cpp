#include <stdexcept>
#include <cmath>
#include <iostream>
#include <map>
#include "expression.h"

Expression::Expression(std::string expression) : _expression_string(expression) {  

    _lexems = _parser.parse(expression);
    _polish = _parser.to_polish(_lexems);
}

Expression::Expression(const List<Lexem>& list) : _lexems(list) {
    _polish = _parser.to_polish(_lexems);
}

std::string Expression::get_expression_string() const {
    return _expression_string;
}

void Expression::set_variable(const std::string& name, double value) {
    _variables[name] = value;
}

double Expression::calculate() const {
    if (_polish.size() == 0) {
        throw std::runtime_error("ѕопытка вычислить пустое выражение");
    }
    Stack<double> stack(100);

    auto it = _polish.begin();
    auto end = _polish.end();

    int counter = 0;
    while (it != end) {
        const Lexem& lexem = *it;
        if (lexem.get_type() == Constant) {
            stack.push(lexem.get_value());
        }
        else if (lexem.get_type() == Variable) {
            std::string var_name = lexem.get_name();
            auto var_it = _variables.find(var_name); 
            if (var_it == _variables.end()) {
                throw std::runtime_error("Undefined variable: " + var_name);
            }
            double value = var_it->second; 
            stack.push(value);
        }
        else if (lexem.get_type() == Operator) {
            if (stack.is_empty()) throw std::runtime_error("Not enough operands");
            double right = stack.top(); stack.pop();

            if (stack.is_empty()) throw std::runtime_error("Not enough operands");
            double left = stack.top(); stack.pop();

            double result = 0;
            std::string op = lexem.get_name();

            if (op == "+") result = left + right;
            else if (op == "-") result = left - right;
            else if (op == "*") result = left * right;
            else if (op == "/") {
                if (right == 0) throw std::runtime_error("Division by zero");
                result = left / right;
            }
            else if (op == "^") result = pow(left, right);
            else throw std::runtime_error("Unknown operator: " + op);

            stack.push(result);
        }
        else if (lexem.get_type() == UnOperator) {
            if (stack.is_empty()) throw std::runtime_error("Not enough operands");
            double operand = stack.top(); stack.pop();

            double result = -operand;
            stack.push(result);
        }
        else if (lexem.get_type() == Function) {
            if (stack.is_empty()) throw std::runtime_error("Not enough operands");
            double operand = stack.top(); stack.pop();

            double result = 0;
            std::string func = lexem.get_name();

            if (func == "sin") result = sin(operand);
            else if (func == "cos") result = cos(operand);
            else if (func == "tg" || func == "tan") result = tan(operand);
            else throw std::runtime_error("Unknown function: " + func);

            stack.push(result);
        }
        else {
            throw std::runtime_error("Unexpected lexem type in polish notation");
        }

        ++it;
        ++counter;

        if (counter > 100) { 
            throw std::runtime_error("Calculation took too long");
        }
    }

    if (stack.is_empty()) {
        throw std::runtime_error("No result in stack");
    }

    double final_result = stack.top();
    stack.pop();

    if (!stack.is_empty()) {
        throw std::runtime_error("Too many values in stack");
    }

    return final_result;
}
