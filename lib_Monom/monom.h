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

    Monom operator/(double scalar) const; //+
    Monom operator*(double scalar) const; //+

    Monom& operator*=(double scalar); //+
    Monom& operator/=(double scalar); //+


    bool operator > (const Monom& other) const; //++
    bool operator < (const Monom& other) const;//++

    double evaluate_at_point(double x, double y, double z) const; //+

    friend Monom operator*(double value, const Monom& monom) { // +
        return monom * value;
    }
    friend Monom operator/(double value, const Monom& monom) { //++
        if (value == 0.0) {
            throw std::logic_error("Division by zero monomial");
        }
        return Monom(value / monom.get_coeff(),
            -monom.get_power(0),
            -monom.get_power(1),
            -monom.get_power(2));
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
    friend std::istream& operator>>(std::istream& is, Monom& m) { //++
        is >> std::ws;
        if (is.peek() == EOF) return is;

        double coeff = 1.0;
        int p[3] = { 0, 0, 0 };
        int sign = 1;

        if (is.peek() == '+' || is.peek() == '-') {
            char s;
            is >> s;
            if (s == '-') sign = -1;
            is >> std::ws;
        }
        if (std::isdigit(is.peek())) {
            is >> coeff;
        }
        coeff *= sign;

        char c;
        while (is >> std::ws && (is.peek() == 'x' || is.peek() == 'y' || is.peek() == 'z')) {
            is >> c;
            int idx = (c == 'x') ? 0 : (c == 'y') ? 1 : 2;

            if (is.peek() == '^') {
                is.ignore();
                is >> p[idx];
            }
            else {
                p[idx] = 1;
            }
        }

        m = Monom(coeff, p[0], p[1], p[2]);

        if (is.fail()) is.clear();

        return is;
    }
};

#endif  