//#ifndef PARSER_H
//#define PARSER_H
//
//#include "../lib_List/list.h"
//#include "../lib_Lexem/lexem.h"
//#include <string>
//
//class Parser {
//private:
//    bool is_digit(char c);
//    bool is_letter(char c);
//    bool is_operator(char c);
//    bool is_bracket(char c);
//
//    std::string read_number(const std::string& expression, size_t& pos);
//    std::string read_identifier(const std::string& expression, size_t& pos);
//    bool is_function(const std::string& name);
//    int get_priority(const std::string& op);
//    bool is_valid_variable_name(const std::string& name);
//
//public:
//    List<Lexem> parse(const std::string& expression);
//    List<Lexem> to_polish(const List<Lexem>& lexems);
//};
//
//#endif