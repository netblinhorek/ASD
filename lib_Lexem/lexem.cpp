#include <stdexcept>
#include "lexem.h"

const std::string& Lexem::get_name() const
{
    return _name;
}

double Lexem::get_value() const
{
    return _value;
}

void Lexem::set_value(double value)
{
    _value = value;
}

TypeLexem Lexem::get_type() const
{
    return _type;
}

