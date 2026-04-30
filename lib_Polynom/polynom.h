#pragma once
#ifndef POLYNOM_H
#define POLYNOM_H
#include <iostream>
#include <exception>
#include <string>
#include "../lib_Monom/monom.h"
#include "../lib_List/list.h"
#include <sstream>
#include <cctype>

class Polynom {
    std::string _name;
    List <Monom> _polynom;
public:
    Polynom(); //++
    Polynom(const Monom& monom); //+
    Polynom(std::string str); //+
    Polynom(List<Monom> monoms); // +
    Polynom(const Polynom& other) : _polynom(other._polynom) {  //+
    }
    
    Polynom operator+(const Polynom& other) const; //+++++
    Polynom operator-(const Polynom& other) const; //+++++
    Polynom operator*(const Polynom& other) const; //+++++
    Polynom operator/(const Polynom& other) const; //++++

    Polynom& operator+=(const Monom& other); //+
    Polynom& operator-=(const Monom& other);//+
    Polynom& operator*=(const Monom& other);//+
    Polynom& operator*=(double scalar);//+
    Polynom& operator/=(const Monom& other); //+
    Polynom& operator/=(double scalar); //+

    Polynom Polynom::operator*(double scalar) const; //+
    Polynom Polynom::operator/(double scalar) const; //+

    void add_monom(const Monom& m);
    bool operator>(const Polynom& other) const;
    bool operator<(const Polynom& other) const;
    bool operator==(const Monom& other) const;
    bool operator!=(const Monom& other) const;

    bool operator==(const Polynom& other) const;
    bool operator!=(const Polynom& other) const;

    inline size_t get_size() const { return _polynom.count(); }
    double calculate_at_point(double x, double y, double z) const;
    List<Monom>::Iterator begin();
    List<Monom>::Iterator end();

    friend std::ostream& operator<<(std::ostream& os, const Polynom& p);
    friend std::istream& operator>>(std::istream& is, Polynom& p);
};


#endif