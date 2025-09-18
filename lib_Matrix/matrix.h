#pragma once
#include <iostream>
#include <stdexcept>
#include "../lib_MathVector/mathvector.h"

template <class T>
class Matrix : public MathVector<MathVector<T>> {
public:
    Matrix() {}
    Matrix(size_t rows, size_t cols)
        : MathVector<MathVector<T>>(rows) {}
  
    Matrix(size_t rows, size_t cols, const T& value) {}
    Matrix(const Matrix<T>& other) {}

    size_t rows() const { return 0; }
    size_t cols() const { return 0; }

    MathVector<T>& operator[](size_t index) {
    }
    const MathVector<T>& operator[](size_t index) const {
    }

    Matrix<T> transpose() const { return Matrix<T>(); }

    bool is_square() const {}
    bool is_valid() const { }

    Matrix<T> operator+(const Matrix<T>& other) const { return Matrix<T>(); }
    Matrix<T> operator-(const Matrix<T>& other) const { return Matrix<T>(); }
    Matrix<T> operator*(const Matrix<T>& other) const { return Matrix<T>(); }
    Matrix<T> operator/(const Matrix<T>& other) const { return Matrix<T>(); }

    Matrix<T> operator+(T value) const { return Matrix<T>(); }
    Matrix<T> operator-(T value) const { return Matrix<T>(); }
    Matrix<T> operator*(T value) const { return Matrix<T>(); }
    Matrix<T> operator/(T value) const { return Matrix<T>(); }

    Matrix<T>& operator+=(const Matrix<T>& other) { return *this; }
    Matrix<T>& operator-=(const Matrix<T>& other) { return *this; }
    Matrix<T>& operator*=(const Matrix<T>& other) { return *this; }
    Matrix<T>& operator/=(const Matrix<T>& other) { return *this; }

    Matrix<T>& operator+=(T value) { return *this; }
    Matrix<T>& operator-=(T value) { return *this; }
    Matrix<T>& operator*=(T value) { return *this; }
    Matrix<T>& operator/=(T value) { return *this; }

    friend Matrix<T> operator+(T value, const Matrix<T>& matrix) { return Matrix<T>(); }
    friend Matrix<T> operator*(T value, const Matrix<T>& matrix) { return Matrix<T>(); }
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) { return os; }
};