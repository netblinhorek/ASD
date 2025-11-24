#pragma once
#ifndef MONOM_H
#define MONOM_H

#include <iostream>
#include <string>
#include <cmath>

// Количество переменных, которые могут быть у монома (x, y, z)
const int VARS_COUNT = 3;

class Monom {
    double _coeff;        // Коэффициент
    int _powers[VARS_COUNT]; // Степени переменных x, y, z

public:
    // Конструктор по умолчанию
    inline Monom(double coeff = 0.0, int px = 0, int py = 0, int pz = 0) : _coeff(coeff) {
        _powers[0] = px;
        _powers[1] = py;
        _powers[2] = pz;
    }

    // Конструктор копирования
    inline Monom(const Monom& other) : _coeff(other._coeff) {
        for (int i = 0; i < VARS_COUNT; ++i) {
            _powers[i] = other._powers[i];
        }
    }

    // Конструктор из строки (если понадобится)
    inline Monom(std::string str) : _coeff(0.0) {
        // Простая реализация: разбираем строку в моном
        // Для более сложного парсинга потребуется отдельная функция
        // Сейчас просто для компиляции.
    }

    inline double get_coeff() const { return _coeff; }
    inline int get_power(int var_idx) const {
        if (var_idx >= 0 && var_idx < VARS_COUNT) {
            return _powers[var_idx];
        }
        throw std::out_of_range("Variable index out of range");
    }

    inline void set_coeff(double coeff) { _coeff = coeff; }
    inline void set_power(int var_idx, int power) {
        if (var_idx >= 0 && var_idx < VARS_COUNT) {
            _powers[var_idx] = power;
        }
        else {
            throw std::out_of_range("Variable index out of range");
        }
    }

    // Метод для получения строкового представления переменных
    inline std::string get_variables() const {
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

    inline void negate() { _coeff *= -1; }

    // Операторы присваивания
    inline Monom& operator=(const Monom& other) {
        if (this != &other) {
            _coeff = other._coeff;
            for (int i = 0; i < VARS_COUNT; ++i) {
                _powers[i] = other._powers[i];
            }
        }
        return *this;
    }

    // Операторы сравнения
    inline bool is_like(const Monom& other) const {
        for (int i = 0; i < VARS_COUNT; ++i) {
            if (_powers[i] != other._powers[i]) {
                return false;
            }
        }
        return true;
    }

    inline bool operator==(const Monom& other) const {
        return (std::abs(_coeff - other._coeff) < 1e-9 && is_like(other));
    }

    inline bool operator!=(const Monom& other) const {
        return !(*this == other);
    }

    inline bool operator>(const Monom& other) const {
        // Сравнение по степени, затем по коэффициенту
        int sum_powers_this = _powers[0] + _powers[1] + _powers[2];
        int sum_powers_other = other._powers[0] + other._powers[1] + other._powers[2];

        if (sum_powers_this > sum_powers_other) return true;
        if (sum_powers_this < sum_powers_other) return false;

        // Если степени равны, сравниваем по степеням переменных (лексикографически)
        for (int i = 0; i < VARS_COUNT; ++i) {
            if (_powers[i] > other._powers[i]) return true;
            if (_powers[i] < other._powers[i]) return false;
        }

        // Если все степени равны, сравниваем коэффициенты
        return _coeff > other._coeff;
    }

    inline bool operator<(const Monom& other) const {
        return !(*this > other || *this == other);
    }

    // Операторы арифметики
    inline Monom& operator+=(const Monom& other) {
        
        if (is_like(other)) {
            _coeff += other._coeff;
        }
        else {
            throw std::invalid_argument("Cannot add unlike monomials");
        }
        return *this;
    }

    inline Monom operator+(const Monom& other) const {
        Monom result = *this;
        result += other;
        return result;
    }

    inline Monom& operator-=(const Monom& other) {
        if (is_like(other)) {
            _coeff -= other._coeff;
        }
        else {
            throw std::invalid_argument("Cannot subtract unlike monomials");
        }
        return *this;
    }

    inline Monom operator-(const Monom& other) const {
        Monom result = *this;
        result -= other;
        return result;
    }

    inline Monom& operator*=(const Monom& other) {
        _coeff *= other._coeff;
        for (int i = 0; i < VARS_COUNT; ++i) {
            _powers[i] += other._powers[i];
        }
        return *this;
    }

    inline Monom operator*(const Monom& other) const {
        Monom result = *this;
        result *= other;
        return result;
    }

    inline Monom& operator/=(const Monom& other) {
        if (other._coeff == 0.0) {
            throw std::invalid_argument("Division by zero monomial");
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

    inline Monom operator/(const Monom& other) const {
        Monom result = *this;
        result /= other;
        return result;
    }

    // Оператор вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const Monom& m) {
        if (m._coeff == 0.0) {
            os << "0";
            return os;
        }
        if (m._coeff != 1.0 || m.get_variables().empty()) {
            os << m._coeff; // Выводим коэффициент
        }
        os << m.get_variables(); // Выводим переменные
        return os;
    }
};

#endif // MONOM_H
