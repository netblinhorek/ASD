#pragma once
#include <iostream>
#include <stdexcept>
#include "../lib_Matrix/matrix.h"

enum class TriangleType { Lower, Upper };

template <typename T>
class Triangle : public Matrix<T> {
private:
    TriangleType _type;

public:
    Triangle() {}
    Triangle(size_t size, const T& value, TriangleType type = TriangleType::Lower) {}
    Triangle(const Matrix<T>& other, TriangleType type = TriangleType::Lower) {}

    T& operator()(size_t row, size_t col) {}
    const T& operator()(size_t row, size_t col) const {}

    TriangleType get_type() const noexcept { return TriangleType::Lower; }
    size_t rows() const { return 0; }
    size_t cols() const { return 0; }

    Triangle<T> operator+(const Triangle<T>& other) const { return Triangle<T>(); }
    Triangle<T> operator-(const Triangle<T>& other) const { return Triangle<T>(); }
    Triangle<T> operator*(const Triangle<T>& other) const { return Triangle<T>(); }
    Triangle<T> operator/(const Triangle<T>& other) const { return Triangle<T>(); }

    Triangle<T>& operator+=(const Triangle<T>& other) { return *this; }
    Triangle<T>& operator-=(const Triangle<T>& other) { return *this; }
    Triangle<T>& operator*=(const Triangle<T>& other) { return *this; }
    Triangle<T>& operator/=(const Triangle<T>& other) { return *this; }

    Triangle<T> operator+(T value) const { return Triangle<T>(); }
    Triangle<T> operator-(T value) const { return Triangle<T>(); }
    Triangle<T> operator*(T value) const { return Triangle<T>(); }
    Triangle<T> operator/(T value) const { return Triangle<T>(); }

    Triangle<T>& operator+=(T value) { return *this; }
    Triangle<T>& operator-=(T value) { return *this; }
    Triangle<T>& operator*=(T value) { return *this; }
    Triangle<T>& operator/=(T value) { return *this; }

    friend Triangle<T> operator+(T value, const Triangle<T>& matrix) { return Triangle<T>(); }
    friend Triangle<T> operator*(T value, const Triangle<T>& matrix) { return Triangle<T>(); }
    friend std::ostream& operator<<(std::ostream& os, const Triangle<T>& matrix) { return os; }
};