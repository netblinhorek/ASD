#include "../lib_Expression/expression.h"


Expression::Expression(const std::string& infix)
    : _infix(infix), _postfix("") {

    _priority["+"] = 1;
    _priority["-"] = 1;
    _priority["*"] = 2;
    _priority["/"] = 2;
    _priority["^"] = 3;
    _priority["~"] = 4;

    parse();

    to_postfix();

    extract_operands();
}

void Expression::parse() {
    _infix_lexems = _parser.parse(_infix);
}

void Expression::to_postfix() {
    List<Lexem> polish_lexems = _parser.to_polish(_infix_lexems);
    _postfix_lexems = polish_lexems;

    Node<Lexem>* current = polish_lexems.head();
    while (current != nullptr) {
        const Lexem& lex = current->value;
        _postfix += lex.get_name() + " ";
        current = current->next;
    }

    if (!_postfix.empty()) {
        _postfix.pop_back();
    }
}

void Expression::extract_operands() {
    Node<Lexem>* current = _infix_lexems.head();
    while (current != nullptr) {
        const Lexem& lex = current->value;
        if (lex.get_type() == Variable) {
            std::string var_name = lex.get_name();
            if (_operands.find(var_name) == _operands.end()) {
                _operands[var_name] = 0.0; 
            }
        }
        current = current->next;
    }
}

std::string Expression::get_postfix() const {
    return _postfix;
}

List<std::string> Expression::get_operands() const {
    List<std::string> result;
    for (const auto& pair : _operands) {
        result.push_back(pair.first);
    }
    return result;
}

double Expression::calculate(const std::map<std::string, double>& values) const {
    for (const auto& required : _operands) {
        auto it = values.find(required.first);
        if (it == values.end()) {
            throw std::runtime_error("Undefined variable");
        }
    }

    double stack[100];
    int stack_top = -1;

    if (_postfix_lexems.is_empty()) {
        throw std::runtime_error("Invalid expression");
    }

    Node<Lexem>* current = _postfix_lexems.head();
    while (current != nullptr) {
        const Lexem& lex = current->value;

        if (lex.is_constant()) {
            stack[++stack_top] = lex.get_value();
        }
        else if (lex.is_variable()) {
            std::string var_name = lex.get_name();
            auto val_it = values.find(var_name);
            if (val_it == values.end()) {
                throw std::runtime_error("Undefined variable");
            }
            stack[++stack_top] = val_it->second;
        }
        else if (lex.is_function()) {
            if (stack_top < 0) {
                throw std::runtime_error("Stack underflow");
            }
            double arg = stack[stack_top--];
            double result = lex.execute_function(arg);
            stack[++stack_top] = result;
        }
        else if (lex.is_operator()) {
            if (stack_top < 0) {
                throw std::runtime_error("Stack underflow");
            }

            std::string op_name = lex.get_name();

            if (op_name == "~") {
                double operand = stack[stack_top--];
                stack[++stack_top] = -operand;
            }
            else {
                if (stack_top < 1) {
                    throw std::runtime_error("Stack underflow");
                }

                double right = stack[stack_top--];
                double left = stack[stack_top--];
                double result = 0.0;

                if (op_name == "+") {
                    result = left + right;
                }
                else if (op_name == "-") {
                    result = left - right;
                }
                else if (op_name == "*") {
                    result = left * right;
                }
                else if (op_name == "/") {
                    if (right == 0.0) {
                        throw std::runtime_error("Division by zero");
                    }
                    result = left / right;
                }
                else if (op_name == "^") {
                    result = pow(left, right);
                }

                stack[++stack_top] = result;
            }
        }

        current = current->next;
    }

    if (stack_top != 0) {
        throw std::runtime_error("Invalid expression");
    }

    return stack[stack_top];
}