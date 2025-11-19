//#include <stdexcept>
//#include "parser.h"
//#include "../lib_Stack/stack.h"
//#include "../lib_Lexem/lexem.h"
//#include <cctype>
//
//bool Parser::is_digit(char c) {
//    bool result = std::isdigit(static_cast<unsigned char>(c)) || c == '.';
//    return result;
//}
//
//bool Parser::is_letter(char c) {
//    bool result = std::isalpha(static_cast<unsigned char>(c)) || c == '_';
//    return result;
//}
//
//bool Parser::is_operator(char c) {
//    bool result = c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
//    return result;
//}
//
//bool Parser::is_bracket(char c) {
//    return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']';
//}
//
//std::string Parser::read_number(const std::string& expression, size_t& pos) {
//    std::string number;
//    while (pos < expression.length() && (is_digit(expression[pos]) || expression[pos] == '.')) {
//        number += expression[pos++];
//    }
//    return number;
//}
//
//std::string Parser::read_identifier(const std::string& expression, size_t& pos) {
//    std::string identifier;
//    while (pos < expression.length() && (is_letter(expression[pos]) || is_digit(expression[pos]))) {
//        identifier += expression[pos++];
//    }
//    return identifier;
//}
//
//bool Parser::is_function(const std::string& name) {
//    return name == "sin" || name == "cos" || name == "tg" || name == "tan";
//}
//
//int Parser::get_priority(const std::string& op) {
//
//    if (op == "+" || op == "-") return 1;
//    if (op == "*" || op == "/") return 2;
//    if (op == "^") return 3;
//    if (op == "~") return 4; 
//
//    return 0;
//}
//
//bool Parser::is_valid_variable_name(const std::string& name) {
//    if (name.empty()) return false;
//
//    if (!is_letter(name[0])) return false;
//
//    for (size_t i = 0; i < name.length(); i++) {
//        if (!is_letter(name[i])) {
//            return false;
//        }
//    }
//
//    return true;
//}
//
//List<Lexem> Parser::parse(const std::string& expression) {
//    List<Lexem> lexems;
//    size_t pos = 0;
//
//    while (pos < expression.length()) {
//        char current = expression[pos];
//
//        if (std::isspace(current)) {
//            pos++;
//            continue;
//        }
//
//        if (is_digit(current)) {
//            std::string number = read_number(expression, pos);
//            lexems.push_back(Lexem(number, Constant, std::stod(number)));
//        }
//        else if (is_letter(current)) {
//            std::string identifier = read_identifier(expression, pos);
//            if (is_function(identifier)) {
//                lexems.push_back(Lexem(identifier, Function, 0.0));
//            }
//            else {
//                if (!is_valid_variable_name(identifier)) {
//                    throw std::runtime_error("Invalid variable name: '" + identifier +
//                        "'. Variable names should contain only letters");
//                }
//                lexems.push_back(Lexem(identifier, Variable, 0.0));
//            }
//        }
//        else if (is_operator(current)) {
//            if (current == '-' && (lexems.is_empty() ||
//                lexems.head()->value.get_type() == Operator ||
//                lexems.head()->value.get_type() == OpenBracket)) {
//                lexems.push_back(Lexem("~", UnOperator, 0.0));
//            }
//            else {
//                lexems.push_back(Lexem(std::string(1, current), Operator, 0.0));
//            }
//            pos++;
//        }
//        else if (current == '(' || current == '{' || current == '[') {
//            lexems.push_back(Lexem(std::string(1, current), OpenBracket, 0.0));
//            pos++;
//        }
//        else if (current == ')' || current == '}' || current == ']') {
//            lexems.push_back(Lexem(std::string(1, current), ClosedBracket, 0.0));
//            pos++;
//        }
//        else {
//            throw std::runtime_error("Unknown character: " + std::string(1, current));
//        }
//    }
//
//    return lexems;
//}
//
//List<Lexem> Parser::to_polish(const List<Lexem>& lexems) {
//    List<Lexem> result_queue;
//    Stack<Lexem> operator_stack(100);
//
//    Node<Lexem>* current = nullptr; 
//    int step = 0;
//
//    try {
//        current = lexems.head(); 
//        if (current == nullptr) {
//            return result_queue;
//        }
//        while (current != nullptr) {
//
//            const Lexem& lexem = current->value;
//            TypeLexem type = lexem.get_type();
//            std::string name = lexem.get_name();
//
//            if (type == Constant || type == Variable) {
//                result_queue.push_back(lexem);
//            } else if (type == Function) {
//                operator_stack.push(lexem);
//            } else if (type == Operator || type == UnOperator) {
//                while (!operator_stack.is_empty() &&
//                       (operator_stack.top().get_type() == Operator || operator_stack.top().get_type() == UnOperator) &&
//                       ((get_priority(name) <= get_priority(operator_stack.top().get_name())) ||
//                        (get_priority(name) == get_priority(operator_stack.top().get_name()) && name != "^")) &&
//                       (operator_stack.top().get_type() != OpenBracket)) {
//                    
//                    result_queue.push_back(operator_stack.top());
//                    operator_stack.pop();
//                }
//                operator_stack.push(lexem);
//            } else if (type == OpenBracket) {
//                operator_stack.push(lexem);
//            } else if (type == ClosedBracket) {
//                bool open_bracket_found = false;
//                while (!operator_stack.is_empty() && operator_stack.top().get_type() != OpenBracket) {
//                    result_queue.push_back(operator_stack.top());
//                    operator_stack.pop();
//                }
//                if (!operator_stack.is_empty() && operator_stack.top().get_type() == OpenBracket) {
//                    operator_stack.pop();
//                    open_bracket_found = true;
//                } else {
//                    throw std::runtime_error("Mismatched parentheses: No matching open bracket for " + lexem.to_string());
//                }
//
//                if (!operator_stack.is_empty() && operator_stack.top().get_type() == Function) {
//                    result_queue.push_back(operator_stack.top());
//                    operator_stack.pop();
//                }
//            } else {
//                throw std::runtime_error("Unexpected lexem type in toPolish: " + lexem.to_string());
//            }
//            current = current->next;
//            step++;
//        }
//    } catch (const std::exception& e) {
//        std::cerr << "ERROR in toPolish: " << e.what() << std::endl;
//        throw;
//    }
//
//    while (!operator_stack.is_empty()) {
//        if (operator_stack.top().get_type() == OpenBracket || operator_stack.top().get_type() == ClosedBracket) {
//            throw std::runtime_error("Mismatched parentheses: Unclosed bracket left on stack: " + operator_stack.top().to_string());
//        }
//        result_queue.push_back(operator_stack.top());
//        operator_stack.pop();
//    }
//    return result_queue;
//}