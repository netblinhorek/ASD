#pragma once
#include "../lib_List/list.h"
#include "../lib_Lexem/lexem.h"
#include "../lib_Parser/parser.h"
#include <string>
#include <map>
#include <cmath>
#include <stdexcept>

class Expression {
private:
    std::string _infix;
    std::string _postfix;
    List<Lexem> _infix_lexems;
    List<Lexem> _postfix_lexems;
    std::map<std::string, double> _operands;
    std::map<std::string, int> _priority;
    Parser _parser;

    void parse();
    void to_postfix();
    void extract_operands();

public:
    Expression(const std::string& infix);

    std::string get_infix() const { return _infix; }
    std::string get_postfix() const;
    List<std::string> get_operands() const;
    double calculate(const std::map<std::string, double>& values) const;
};


