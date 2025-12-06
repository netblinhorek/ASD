#pragma once
#include <iostream>
#include <stdexcept>
#include "../lib_Matrix/matrix.h"

enum class TriangleType { Lower, Upper };

template<typename T>
class Triangle : public Matrix<T> {
private:
    TriangleType _type;

public:
    Triangle();
    Triangle(size_t size, const T& value, TriangleType type = TriangleType::Lower);
    Triangle(const Matrix<T>& other, TriangleType type = TriangleType::Lower);

    T& operator()(size_t row, size_t col);
    const T& operator()(size_t row, size_t col) const;

    TriangleType get_type() const noexcept;
    size_t rows() const;
    size_t cols() const;

    Triangle<T> operator+(const Triangle<T>& other) const;
    Triangle<T> operator-(const Triangle<T>& other) const;
    Triangle<T> operator*(const Triangle<T>& other) const;
    Triangle<T> operator*(const T& scalar) const;

   

private:
    bool is_valid_access(size_t row, size_t col) const;
};

template<typename T>
Triangle<T>::Triangle() : Matrix<T>(), _type(TriangleType::Lower) {}

template<typename T>
Triangle<T>::Triangle(size_t size, const T& value, TriangleType type) : _type(type) {
    for (size_t i = 0; i < size; ++i) {
        size_t row_length = i + 1;

        MathVector<T> row(row_length, value);
        this->push_back(row);
    }
}

template<typename T>
Triangle<T>::Triangle(const Matrix<T>& other, TriangleType type) : _type(type) {
    if (!other.is_square()) {
        throw std::invalid_argument("Triangle matrix must be square");
    }

    size_t size = other.rows();

    for (size_t i = 0; i < size; ++i) {
        MathVector<T> row(i + 1);
        for (size_t j = 0; j <= i; ++j) {
            row[j] = other[i][j];
        }
        this->push_back(row);
    }
}

template<typename T>
bool Triangle<T>::is_valid_access(size_t row, size_t col) const {
    if (row >= this->rows() || col >= this->rows()) {
        return false;  // Выход за границы
    }
        return col <= row;  // Для нижнего треугольника
}

template<typename T>
T& Triangle<T>::operator()(size_t row, size_t col) {
    if (row >= this->size() || col >= this->size()) {
        throw std::out_of_range("Index out of range");
    }

    if (col > row) {
        throw std::invalid_argument("Cannot modify zero elements in triangular matrix");
    }
    return (*this)[row][col];
}

template<typename T>
const T& Triangle<T>::operator()(size_t row, size_t col) const {
    if (!is_valid_access(row, col)) {
        if (row >= this->rows() || col >= this->rows()) {
            throw std::out_of_range("Index out of range");
        }
        else {
            static T zero = T(0);
            return zero;
        }
    }

    return (*this)[row][col];
}

template<typename T>
TriangleType Triangle<T>::get_type() const noexcept {
    return _type;
}

template<typename T>
size_t Triangle<T>::rows() const {
    return Matrix<T>::size();
}

template<typename T>
size_t Triangle<T>::cols() const {
    return this->rows();
}

template<typename T>
Triangle<T> Triangle<T>::operator+(const Triangle<T>& other) const {
    if (this->rows() != other.rows() || _type != other._type) {
        throw std::invalid_argument("Matrix dimensions and types must match");
    }
    Triangle<T> result(this->rows(), T(0), _type);

    for (size_t i = 0; i < this->rows(); ++i) {
        for (size_t j = 0; j <= i; ++j) {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return result;
}

template<typename T>
Triangle<T> Triangle<T>::operator-(const Triangle<T>& other) const {
    if (this->rows() != other.rows() || _type != other._type) {
        throw std::invalid_argument("Matrix dimensions and types must match");
    }
    Triangle<T> result(this->rows(), T(0), _type);

    for (size_t i = 0; i < this->rows(); ++i) {
        for (size_t j = 0; j <= i; ++j) {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return result;
}

template<typename T>
Triangle<T> Triangle<T>::operator*(const Triangle<T>& other) const {
    if (this->rows() != other.rows()) {
        throw std::invalid_argument("Matrix dimensions must match for multiplication");
    }

    size_t size = this->rows();
    Triangle<T> result(size, T(0), TriangleType::Lower); 

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            T sum = T(0);
            for (size_t k = j; k <= i; ++k) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }

    return result;
}

template<typename T>
Triangle<T> Triangle<T>::operator*(const T& scalar) const {
    Triangle<T> result(this->rows(), T(0), _type);

    for (size_t i = 0; i < this->rows(); ++i) {
        for (size_t j = 0; j <= i; ++j) {
            result(i, j) = (*this)(i, j) * scalar;
        }
    }

    return result;
}

