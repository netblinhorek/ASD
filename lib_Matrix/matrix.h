#pragma once
#include <cstddef>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include "../lib_MathVector/mathvector.h"

template <typename T>
class Matrix : public MathVector<MathVector<T>> {
public:
    Matrix();
    Matrix(size_t rows, size_t cols);
    Matrix(size_t rows, size_t cols, const T& value);
    Matrix(const Matrix<T>& other) = default;
    Matrix(Matrix<T>&& other) = default;
    Matrix(const MathVector<MathVector<T>>& other) : MathVector<MathVector<T>>(other) {}
    Matrix<T>& operator=(const Matrix<T>& other) = default;
    Matrix<T>& operator=(Matrix<T>&& other) = default;

    size_t rows() const;
    size_t cols() const;
    void erase_row(size_t index);
    void erase_col(size_t index);

    Matrix<T> transpose() const;

    bool is_square() const;
    bool is_valid() const;

    Matrix<T> operator+(const Matrix<T>& other) const;
    Matrix<T> operator-(const Matrix<T>& other) const;
    Matrix<T> operator*(const Matrix<T>& other) const;
    Matrix<T> operator*(const T& other) const;        
    Matrix<T> operator/(const T& other) const;        

    Matrix<T>& operator+=(const Matrix<T>& other);
    Matrix<T>& operator-=(const Matrix<T>& other);
    Matrix<T>& operator*=(const Matrix<T>& other);
    Matrix<T>& operator*=(const T& other);
    Matrix<T>& operator/=(const T& other);

    friend Matrix<T> operator*(T value, const Matrix<T>& matrix) {
        return matrix * value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
        os << "[\n";
        for (size_t i = 0; i < matrix.rows(); ++i) {
            os << "  " << matrix[i];
            if (i < matrix.rows() - 1) os << ",\n";
        }
        os << "\n]";
        return os;
    }

    inline MathVector<T>& operator[](size_t index) {
        return MathVector<MathVector<T>>::operator[](index);
    }

    inline const MathVector<T>& operator[](size_t index) const {
        return MathVector<MathVector<T>>::operator[](index);
    }

};

template <typename T>
Matrix<T>::Matrix() : MathVector<MathVector<T>>() {}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : MathVector<MathVector<T>>() {
    if (rows > 0) {
        this->reserve(rows);
        for (size_t i = 0; i < rows; ++i) {
            this->push_back(MathVector<T>(cols));
        }
    }
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T& value) : MathVector<MathVector<T>>() {
    if (rows > 0) {
        this->reserve(rows);
        for (size_t i = 0; i < rows; ++i) {
            this->push_back(MathVector<T>(cols, value));
        }
    }
}
template <typename T>
void Matrix<T>::erase_row(size_t index) {
    if (index >= rows()) {
        throw std::out_of_range("Row index out of range");
    }
    this->erase(index);
}

template <typename T>
void Matrix<T>::erase_col(size_t index) {
    if (this->is_empty()) return;
    if (index >= cols()) {
        throw std::out_of_range("Column index out of range");
    }

    for (size_t i = 0; i < rows(); ++i) {
        (*this)[i].erase(index);
    }
}
template <typename T>
size_t Matrix<T>::rows() const {
    return this->size();
}

template <typename T>
size_t Matrix<T>::cols() const {
    if (this->is_empty()) return 0;
    return (*this)[0].size();
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    return this->MathVector<MathVector<T>>::operator+(other);
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
    return this->MathVector<MathVector<T>>::operator-(other);
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
      if (cols() != other.rows()) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication!");
    }
    Matrix<T> result(rows(), other.cols());
    Matrix<T> otherT = other.transpose();
    for (size_t i = 0; i < rows(); i++) {
        for (size_t j = 0; j < other.cols(); j++) {
            
            result[i][j] = (*this)[i].the_scalar_product(otherT[j]);
        }
    }

    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const T& other) const {
    if (!is_valid()) {
        throw std::invalid_argument("Matrix is not valid");
    }
    Matrix<T> result(rows(), cols());
    for (size_t i = 0; i < rows(); i++) {
        result[i] = (*this)[i] * other;
    }

    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator/(const T& other) const {
    if (other == T()) {
        throw std::invalid_argument("Division by zero!");
    }

    if (!is_valid()) {
        throw std::invalid_argument("Matrix is not valid");
    }

    Matrix<T> result(rows(), cols());

    for (size_t i = 0; i < rows(); i++) {
        result[i] = (*this)[i] / other;
    }

    return result;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
    *this = *this + other;
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
    *this = *this - other; 
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) {
    *this = *this * other;
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const T& other) {
    *this = *this * other;
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(const T& other) {
    *this = *this / other;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    if (!is_valid()) {
        throw std::invalid_argument("Matrix is not valid");
    }

    if (rows() == 0 && cols() == 0) return Matrix<T>();

    Matrix<T> result(cols(), rows());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            result[j][i] = (*this)[i][j];
        }
    }
    return result;
}

template <typename T>
bool Matrix<T>::is_square() const {
    return is_valid() && (rows() == cols());
}

template <typename T>
bool Matrix<T>::is_valid() const {
    if (this->is_empty()) return false;
    size_t expected_cols = (*this)[0].size();
    for (size_t i = 1; i < this->size(); ++i) {
        if ((*this)[i].size() != expected_cols) {
            return false;
        }
    }
    return true;
}