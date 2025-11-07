#include <iostream>
#include "../lib_List/list.h"
#include "../lib_Lexem/lexem.h"


class Expression {
	List <Lexem> _lexems;
	List <Lexem> _polish;
public:
	Expression(std::string);
	Expression(const List <Lexem>& list);

	//set_variables();
	double calculate();
};
