// Copyright 2024 Marina Usova

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

std::string Lexem::to_string() const
{
   
}

TypeLexem Lexem::get_type() const
{
    return _type;
}

Lexem::Lexem(const std::string& name, TypeLexem type, double value)
    : _name(name), _type(type), _value(value) {}
