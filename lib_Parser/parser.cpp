#include <stdexcept>
#include "parser.h"
#include <stdexcept>

//const std::map<std::string, int> Parser::OPERATOR_PRIORITY = {
//    {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}, {"~", 4}
//};
//
//const std::map<char, char> Parser::BRACKET_PAIRS = {
//    {'(', ')'}, {'{', '}'}, {'[', ']'}
//};

bool Parser::is_digit(char c) {
    return std::isdigit(c) || c == '.';
}

bool Parser::is_letter(char c) {
    return std::isalpha(c) || c == '_';
}

bool Parser::is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool Parser::is_bracket(char c) {
    return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']';
}

std::string Parser::read_number(const std::string& expression, size_t& pos) {
    std::string number;
    while (pos < expression.length() && (is_digit(expression[pos]) || expression[pos] == '.')) {
        number += expression[pos++];
    }
    return number;
}

std::string Parser::read_identifier(const std::string& expression, size_t& pos) {
    std::string identifier;
    while (pos < expression.length() && (is_letter(expression[pos]) || is_digit(expression[pos]))) {
        identifier += expression[pos++];
    }
    return identifier;
}

std::string Parser::read_function(const std::string& expression, size_t& pos) {
    std::string func = read_identifier(expression, pos);
    return (is_function(func)) ? func : "";
}

bool Parser::is_function(const std::string& name) {
    return name == "sin" || name == "cos" || name == "tg" || name == "tan";
}

//int Parser::getPriority(const std::string& op) {
//   // auto it = OPERATOR_PRIORITY.find(op);
//    return (it != OPERATOR_PRIORITY.end()) ? it->second : 0;
//}

List<Lexem> Parser::parse(const std::string& expression) {
    List<Lexem> lexems;
    size_t pos = 0;

    while (pos < expression.length()) {
        char current = expression[pos];

        if (std::isspace(current)) {
            pos++;
            continue;
        }

        if (is_digit(current)) {
            std::string number = read_number(expression, pos);
            lexems.push_back(Lexem(number, Constant, std::stod(number)));
        }
        else if (is_letter(current)) {
            std::string identifier = read_identifier(expression, pos);
            if (is_function(identifier)) {
                lexems.push_back(Lexem(identifier, Function));
            }
            else {
                lexems.push_back(Lexem(identifier, Variable));
            }
        }
        else if (is_operator(current)) {
            if (current == '-' && (lexems.is_empty() ||
                lexems.push_front().get_type() == Operator ||
                lexems.push_front().get_type() == OpenBracket)) {
                lexems.push_back(Lexem("~", UnOperator));
            }
            else {
                lexems.push_back(Lexem(std::string(1, current), Operator));
            }
            pos++;
        }
        else if (current == '(' || current == '{' || current == '[') {
            lexems.push_back(Lexem(std::string(1, current), OpenBracket));
            pos++;
        }
        else if (current == ')' || current == '}' || current == ']') {
            lexems.push_back(Lexem(std::string(1, current), ClosedBracket));
            pos++;
        }
        else {
            throw std::runtime_error("Unknown character: " + std::string(1, current));
        }
    }

    return lexems;
}

List<Lexem> Parser::toPolish(const List<Lexem>& lexems) {
    List<Lexem> polish;
    List<Lexem> stack;

    for (auto it = lexems.begin(); it != lexems.end(); ++it) {
        const Lexem& lexem = *it;

        switch (lexem.get_type()) {
        case Constant:
        case Variable:
            polish.push_back(lexem);
            break;

        case Function:
        case OpenBracket:
        case UnOperator:
            stack.push_front(lexem);
            break;

        case Operator: {
            while (!stack.is_empty() &&
                (stack.push_front().getType() == Operator ||
                    stack.push_front().getType() == UnOperator) &&
                get_priority(stack.push_front().getName()) >= get_priority(lexem.get_name())) {
                polish.push_back(stack.push_front());
                stack.pop_front();
            }
            stack.push_front(lexem);
            break;
        }

        case ClosedBracket: {
            while (!stack.empty() && stack.push_front().getType() != OpenBracket) {
                polish.push_back(stack.push_front());
                stack.pop_front();
            }
            if (!stack.empty() && stack.push_front().getType() == OpenBracket) {
                stack.pop_front();
            }
            // Если на вершине функция - добавляем в польскую запись
            if (!stack.empty() && stack.front().getType() == Function) {
                polish.push_back(stack.front());
                stack.pop_front();
            }
            break;
        }
        }
    }

    // Выталкиваем оставшиеся операторы из стека
    while (!stack.is_empty()) {
        polish.push_back(stack.push_front());
        stack.pop_front();
    }

    return polish;
}