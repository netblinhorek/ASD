#pragma once
#ifndef MONOM_H
#define MONOM_H

#include <iostream>
#include <string>
#include <cmath>

const int VARS_COUNT = 3;

class Monom {
    double _coeff;
    int _powers[VARS_COUNT];

public:

    Monom::Monom(double coeff = 0.0, int px = 0,
        int py = 0, int pz = 0); //++

    Monom(const Monom& other); //+

    double get_coeff() const; //+
    void set_coeff(double coeff); //+

    int get_power(int var_idx) const; // +
    void set_power(int var_idx, int power); //+

    std::string get_variables() const; //+

    Monom& operator=(const Monom& other); //+

    bool is_like(const Monom& other) const;//++

    bool operator==(const Monom& other) const; //+
    bool operator!=(const Monom& other) const; //+

    Monom& operator+=(const Monom& other); //++
    Monom operator+(const Monom& other) const; //++

    Monom& operator-=(const Monom& other); //++
    Monom operator-(const Monom& other) const; //++

    Monom& operator*=(const Monom& other);//+
    Monom operator*(const Monom& other) const;//+

    Monom& operator/=(const Monom& other); // +++
    Monom operator/(const Monom& other) const; //+++

    Monom operator-() const; //+

    double evaluate_at_point(double x, double y, double z) const; //+

    friend Monom operator*(double value, const Monom& monom) { // +
        return monom * value;
    }
    friend Monom operator/(double value, const Monom& monom) { //++
        if (value == 0.0) {
            throw std::logic_error("Division by zero monomial");
        }
        return monom / value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Monom& m) { //++
        if (m._coeff == 0.0) {
            os << "0";
            return os;
        }
        if (m._coeff != 1.0 || m.get_variables().empty()) {
            os << m._coeff;
        }
        os << m.get_variables();
        return os;
    }

    friend std::istream& operator>>(std::istream& os, Monom& m) { //++
        double coeff;
        int px, py, pz;
        if (os >> coeff >> px >> py >> pz) {
            m = Monom(coeff, px, py, pz);
        }

        return os;
    }
};

#endif  