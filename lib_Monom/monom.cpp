#include "../lib_Monom/monom.h"


Monom::Monom(double coeff, int px, int py, int pz) : _coeff(coeff) { 
    _powers[0] = px;
    _powers[1] = py;
    _powers[2] = pz;
}

Monom::Monom(const Monom& other) : _coeff(other._coeff) {
    for (int i = 0; i < VARS_COUNT; ++i) {
        _powers[i] = other._powers[i];
    }
}

double Monom::get_coeff() const {
    return _coeff;
}
int Monom::get_power(int var_idx) const {
    if (var_idx >= 0 && var_idx < VARS_COUNT) {
        return _powers[var_idx];
    }
    throw std::out_of_range("Variable index out of range");
}

void Monom::set_coeff(double coeff) {
    _coeff = coeff;
}

void Monom::set_power(int var_idx, int power) {
    if (var_idx >= 0 && var_idx < VARS_COUNT) {
        _powers[var_idx] = power;
    }
    else {
        throw std::out_of_range("Variable index out of range");
    }
}

std::string Monom::get_variables() const {
    std::string vars_str = "";
    if (_powers[0] > 0) {
        vars_str += "x";
        if (_powers[0] > 1) vars_str += "^" + std::to_string(_powers[0]);
    }
    if (_powers[1] > 0) {
        vars_str += "y";
        if (_powers[1] > 1) vars_str += "^" + std::to_string(_powers[1]);
    }
    if (_powers[2] > 0) {
        vars_str += "z";
        if (_powers[2] > 1) vars_str += "^" + std::to_string(_powers[2]);
    }
    return vars_str;
}


Monom& Monom::operator=(const Monom& other) {
    if (this != &other) {
        _coeff = other._coeff;
        for (int i = 0; i < VARS_COUNT; ++i) {
            _powers[i] = other._powers[i];
        }
    }
    return *this;
}

bool Monom::is_like(const Monom& other) const {
    for (int i = 0; i < VARS_COUNT; ++i) {
        if (_powers[i] != other._powers[i]) {
            return false;
        }
    }
    return true;
}

bool Monom::operator==(const Monom& other) const {
    return _coeff == other._coeff && is_like(other);
}

bool Monom::operator!=(const Monom& other) const {
    return !(*this == other);
}

Monom& Monom::operator+=(const Monom& other) {
    if (is_like(other)) {
        _coeff += other._coeff;
    }
    else {
        throw std::invalid_argument("Cannot add unlike monomials");
    }
    return *this;
}

Monom Monom::operator+(const Monom& other) const {
    Monom result = *this;
    result.operator+=(other);
    return result;
}

Monom& Monom::operator-=(const Monom& other) {
    if (is_like(other)) {
        _coeff -= other._coeff;
    }
    else {
        throw std::invalid_argument("Cannot subtract unlike monomials");
    }
    return *this;
}

Monom Monom::operator-(const Monom& other) const {
    Monom result = *this;
    result.operator-=(other);
    return result;
}

Monom& Monom::operator*=(const Monom& other) {
    _coeff *= other._coeff;
    for (int i = 0; i < VARS_COUNT; ++i) {
        _powers[i] += other._powers[i];
    }
    return *this;
}

Monom Monom::operator*(const Monom& other) const {
    Monom result = *this;
    result.operator*=(other);
    return result;
}

Monom& Monom::operator/=(const Monom& other) {
    if (other._coeff == 0.0) {
        throw std::logic_error("Division by zero monomial");
    }
    for (int i = 0; i < VARS_COUNT; ++i) {
        if (_powers[i] < other._powers[i]) {
            throw std::invalid_argument("Cannot divide: resulting powers would be negative.");
        }
    }

    _coeff /= other._coeff;
    for (int i = 0; i < VARS_COUNT; ++i) {
        _powers[i] -= other._powers[i];
    }
    return *this;
}

Monom Monom::operator/(const Monom& other) const {
    Monom result = *this;
    result.operator/=(other);
    return result;
}

Monom Monom::operator-() const {
    return Monom(-_coeff, _powers[0], _powers[1], _powers[2]);
}

Monom Monom::operator*(double scalar) const {
    return Monom(_coeff * scalar, _powers[0], _powers[1], _powers[2]);
}

Monom& Monom::operator*=(double scalar) {
    _coeff *= scalar;
    return *this;
}

Monom Monom::operator/(double scalar) const {
    if (scalar == 0.0) 
        throw std::invalid_argument("Division by zero");
    return Monom(_coeff / scalar, _powers[0], _powers[1], _powers[2]);
}

Monom& Monom::operator/=(double scalar) {
    if (scalar == 0.0) throw std::invalid_argument("Division by zero");
    _coeff /= scalar;
    return *this;
}

double Monom::evaluate_at_point(double x, double y, double z) const {
    
    double x_pow = 1.0;
    for (int i = 0; i < _powers[0]; i++) {
        x_pow *= x;
    }

    double y_pow = 1.0;
    for (int i = 0; i < _powers[1]; i++) {
        y_pow *= y;
    }


    double z_pow = 1.0;
    for (int i = 0; i < _powers[2]; i++) {
        z_pow *= z;
    }

    return _coeff * x_pow * y_pow * z_pow;
}


bool Monom::operator > (const Monom& other) const{
    for (int i = 0; i < VARS_COUNT; i++) {
        if (_powers[i] != other._powers[i]) {
            return _powers[i] > other._powers[i];
        }
    }
    return false;
}

bool Monom::operator < (const Monom& other) const{
    for (int i = 0; i < VARS_COUNT; i++) {
        if (_powers[i] != other._powers[i]) {
            return _powers[i] < other._powers[i];
        }
    }
    return false;
}