#include "parser.h"
#include <stdexcept>
#include <cctype>

std::string Parser::read_number(const std::string& expression, size_t& pos) {
    if (pos >= expression.length() || !is_digit(expression[pos])) {
        return "";
    }

    std::string number;
    bool has_dot = false;

    while (pos < expression.length()) {
        char c = expression[pos];
        if (is_digit(c)) {
            number += c;
            pos++;
        }
        else if (c == '.' && !has_dot) {
            if (pos + 1 < expression.length() && is_digit(expression[pos + 1])) {
                number += c;
                has_dot = true;
                pos++;
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }
    return number;
}

std::string Parser::read_identifier(const std::string& expression, size_t& pos) {
    if (pos >= expression.length() || !is_letter(expression[pos])) {
        return "";
    }

    std::string identifier;
    identifier += expression[pos];
    pos++;

    while (pos < expression.length()) {
        char current_char = expression[pos];
        if (!is_letter_or_digit(current_char)) {
            break;
        }
        identifier += current_char;
        pos++;
    }
    return identifier;
}

bool Parser::is_valid_variable_name(const std::string& name) {
    if (name.empty()) return false;
    if (!is_letter(name[0])) return false;

    for (size_t i = 1; i < name.length(); i++) {
        if (!is_letter_or_digit(name[i])) {
            return false;
        }
    }
    return true;
}

bool Parser::is_unary_minus(const List<Lexem>& lexems, size_t char_pos_in_string) {
    if (lexems.is_empty()) {
        return true;
    }

    Node<Lexem>* current = lexems.head();
    if (!current) return true;

    while (current->next != nullptr) {
        current = current->next;
    }

    const Lexem& last_lexem = current->value;
    TypeLexem type = last_lexem.get_type();

    return (type == OpenBracket ||
        type == Operator ||
        type == UnOperator ||
        type == Function);
}

List<Lexem> Parser::parse(const std::string& expression) {
    List<Lexem> lexems;
    size_t pos = 0;
    int bracket_balance = 0;
    TypeLexem prev_type = ClosedBracket; 

    while (pos < expression.length()) {
        char current = expression[pos];

        if (std::isspace(current)) {
            pos++;
            continue;
        }

        if (is_digit(current) || (current == '.' && pos + 1 < expression.length() && is_digit(expression[pos + 1]))) {
            std::string number = read_number(expression, pos);
            try {
                double value = std::stod(number);
                lexems.push_back(Lexem(number, Constant, value));
                prev_type = Constant;

                if (pos < expression.length() && is_letter(expression[pos])) {
                    throw std::runtime_error("Invalid token after number at position");
                }
            }
            catch (const std::exception& e) {
                throw std::runtime_error("Invalid number format");
            }
            continue;
        }

        if (is_letter(current)) {
            std::string identifier = read_identifier(expression, pos);

            if (is_function(identifier)) {
                auto func_it = _functions.find(identifier);
                if (func_it != _functions.end()) {
                    lexems.push_back(Lexem(identifier, func_it->second));
                    prev_type = Function;
                }
                else {
                    lexems.push_back(Lexem(identifier, Function));
                    prev_type = Function;
                }
            }
            else {
                if (!is_valid_variable_name(identifier)) {
                    throw std::runtime_error("Invalid variable name");
                }
                lexems.push_back(Lexem(identifier, Variable));
                prev_type = Variable;
            }
            continue;
        }

        if (is_operator_char(current)) {
            std::string op(1, current);

            if (current == '-' && is_unary_minus(lexems, pos)) {
                lexems.push_back(Lexem("~", UnOperator, 0.0, get_priority("~")));
            }
            else {
                lexems.push_back(Lexem(op, get_priority(op)));
            }
            pos++;
            prev_type = Operator;
            continue;
        }

        if (current == '(' || current == '{' || current == '[') {
            lexems.push_back(Lexem(std::string(1, current), OpenBracket));
            pos++;
            bracket_balance++;
            prev_type = OpenBracket;
            continue;
        }

        if (current == ')' || current == '}' || current == ']') {
            lexems.push_back(Lexem(std::string(1, current), ClosedBracket));
            pos++;
            bracket_balance--;
            if (bracket_balance < 0) {
                throw std::runtime_error("the brackets are different");
            }
            prev_type = ClosedBracket;
            continue;
        }

        throw std::runtime_error("Expected: digit, letter, operator (+, -, *, /, ^), bracket, or space.");
    }

    if (bracket_balance != 0) {
        throw std::runtime_error("the brackets are different");
    }

    return lexems;
}

List<Lexem> Parser::to_polish(const List<Lexem>& lexems) {
    List<Lexem> output;

    const int MAX_STACK = 100;
    Lexem stack[MAX_STACK];
    int stack_top = -1;

    Node<Lexem>* current = lexems.head();

    while (current != nullptr) {
        const Lexem& lex = current->value;

        if (lex.is_constant() || lex.is_variable()) {
            output.push_back(lex);
        }
        else if (lex.is_function()) {
            if (stack_top >= MAX_STACK - 1) {
                throw std::runtime_error("Stack overflow");
            }
            stack[++stack_top] = lex;
        }
        else if (lex.is_operator()) {
            while (stack_top >= 0) {
                const Lexem& top = stack[stack_top];
                bool right_associative = (lex.get_name() == "^" || lex.get_name() == "~");

                if (top.is_function() ||
                    (top.is_operator() &&
                        ((lex.get_priority() < top.get_priority()) ||
                            (!right_associative && lex.get_priority() == top.get_priority())))) {
                    output.push_back(top);
                    stack_top--;
                }
                else {
                    break;
                }
            }

            if (stack_top >= MAX_STACK - 1) {
                throw std::runtime_error("Stack overflow");
            }
            stack[++stack_top] = lex;
        }
        else if (lex.get_type() == OpenBracket) {
            if (stack_top >= MAX_STACK - 1) {
                throw std::runtime_error("Stack overflow");
            }
            stack[++stack_top] = lex;
        }
        else if (lex.get_type() == ClosedBracket) {
            while (stack_top >= 0 && stack[stack_top].get_type() != OpenBracket) {
                output.push_back(stack[stack_top--]);
            }

            if (stack_top < 0) {
                throw std::runtime_error("Mismatched parentheses");
            }

            stack_top--;

            if (stack_top >= 0 && stack[stack_top].is_function()) {
                output.push_back(stack[stack_top--]);
            }
        }

        current = current->next;
    }

    while (stack_top >= 0) {
        if (stack[stack_top].get_type() == OpenBracket) {
            throw std::runtime_error("Unclosed bracket");
        }
        output.push_back(stack[stack_top--]);
    }

    return output;
}