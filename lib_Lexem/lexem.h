#pragma once 
#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <functional>

enum TypeLexem {
    Constant,
    Variable,
    Operator,
    ClosedBracket,
    OpenBracket,
    Function,
    UnOperator
};

class Lexem {
private:
    std::string _name;
    TypeLexem _type;
    double _value;
    int _priority;
    std::function<double(double)> _function;

public:
    Lexem() : _name(""), _type(Constant), _value(0.0), _priority(-1), _function(nullptr) {}

    explicit Lexem(double value)
        : _name(std::to_string(value)), _type(Constant), _value(value), _priority(-1), _function(nullptr) {}

    explicit Lexem(const std::string& name, int priority)
        : _name(name), _type(Operator), _value(DBL_MAX), _priority(priority), _function(nullptr) {}

    explicit Lexem(const std::string& name, std::function<double(double)> func)
        : _name(name), _type(Function), _value(DBL_MAX), _priority(0), _function(func) {}

    explicit Lexem(const std::string& name, TypeLexem type)
        : _name(name), _type(type), _value(DBL_MAX), _priority(-1), _function(nullptr)
    {
        if (type == Constant) {
            try {
                _value = std::stod(name);
            }
            catch (...) {
                _value = 0.0;
            }
        }
    }

    explicit Lexem(const std::string& name, TypeLexem type, double value,
        int priority = -1, std::function<double(double)> function = nullptr)
        : _name(name), _type(type), _value(value), _priority(priority), _function(function) {}


    const std::string& get_name() const { return _name; }
    TypeLexem get_type() const { return _type; }
    double get_value() const { return _value; }
    int get_priority() const { return _priority; }

    void set_value(double value) { _value = value; }
    void set_priority(int priority) { _priority = priority; }

    bool is_operator() const { return _type == Operator || _type == UnOperator; }
    bool is_bracket() const { return _type == OpenBracket || _type == ClosedBracket; }
    bool is_function() const { return _type == Function; }
    bool is_variable() const { return _type == Variable; }
    bool is_constant() const { return _type == Constant; }

    double execute_function(double arg) const {
        if (_function) {
            return _function(arg);
        }
        return 0.0;
    }

    std::string to_string() const {
        std::string type_str;
        switch (_type) {
        case Constant: type_str = "Constant"; break;
        case Variable: type_str = "Variable"; break;
        case Operator: type_str = "Operator"; break;
        case OpenBracket: type_str = "OpenBracket"; break;
        case ClosedBracket: type_str = "ClosedBracket"; break;
        case Function: type_str = "Function"; break;
        case UnOperator: type_str = "UnOperator"; break;
        }
        return _name + "(" + type_str + ")";
    }
};