#include <iostream>
#include "../lib_List/list.h"
#include "../lib_Lexem/lexem.h"
#include <string>
#include <map>
#include <cmath>

class Parser {
private:
    bool is_digit(char c);
    bool is_letter(char c);
    bool is_operator(char c);
    bool is_bracket(char c);

    std::string read_number(const std::string& expression, size_t& pos);
    std::string read_identifier(const std::string& expression, size_t& pos);
    std::string read_function(const std::string& expression, size_t& pos);

    int get_priority(const std::string& op);
    bool is_function(const std::string& name);

public:
    List<Lexem> parse(const std::string& expression);
    List<Lexem> toPolish(const List<Lexem>& lexems);
};
