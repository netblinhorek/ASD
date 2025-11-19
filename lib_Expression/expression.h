//#pragma once
//#include <iostream>
//#include <string>
//#include <map>
//#include "../lib_List/list.h"
//#include "../lib_Lexem/lexem.h"
//#include "../lib_Stack/stack.h"
//#include "../lib_Parser/parser.h"
//
//class Expression {
//    List<Lexem> _lexems;
//    List<Lexem> _polish;
//    std::map<std::string, double> _variables;
//    Parser _parser;
//    std::string _expression_string; 
//
//public:
//    Expression(std::string expression);
//    Expression(const List<Lexem>& list);
//    void set_variable(const std::string& name, double value);
//    double calculate() const;
//    const std::map<std::string, double>& variables() const { return _variables; }
//    std::string get_expression_string() const; 
//};
