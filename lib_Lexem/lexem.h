#include <iostream>
#include <string>
#include <map>

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

public:
    Lexem(const std::string& name, TypeLexem type, double value = 0);

    const std::string& get_name() const;
    TypeLexem get_type() const;
    double get_value() const;
    void set_value(double value);


    std::string to_string() const;
};
