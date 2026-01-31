#pragma once
#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <cmath>
#include "../lib_Matrix/matrix.h"

enum class TriangleType { Lower, Upper };

template<typename T>
class Triangle : public Matrix<T> {
private:
    TriangleType _type;
    int _n;

public:
    Triangle();
    Triangle(const int size);
    Triangle(const MathVector<MathVector<T>>& other);
    Triangle(const Triangle<T>& other_matrix);

    Triangle<T> add(const Triangle<T>&) const;
    Triangle<T> sub(const Triangle<T>&) const;
    Triangle<T> mult(const Triangle<T>&) const;
    Triangle<T> mult_by_number(const T&) const;
    Triangle<T> div_by_number(const T&) const;

    Triangle<T>& operator+=(const Triangle<T>& second);
    MathVector<T> operator*(const MathVector<T>& vector) const;
    Triangle<T>& operator-=(const Triangle<T>& second);

    Triangle<T>& operator*=(const T& value);
    Triangle<T>& operator/=(const T& value);
    Triangle<T>& operator=(const Triangle<T>& other_matrix);

    bool operator!=(const Triangle<T>& other_matrix);
    bool operator==(const Triangle<T>& other_matrix);

    Triangle<T> operator+(const Triangle<T>& other) const;
    Triangle<T> operator-(const Triangle<T>& other) const;
    Triangle<T> operator*(const Triangle<T>& other) const;
    Triangle<T> operator*(const T& scalar) const;
    Triangle<T> operator/(const T& scalar) const;
};

template <class T>
Triangle<T>::Triangle() : Matrix<T>(), _n(0) {}

template <class T>
Triangle<T>::Triangle(const int size) : Matrix<T>(size, size), _n(size) {
    this->_type = TriangleType::Lower;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j > i) {
                (*this)[i][j] = T(0);
            }
        }
    }
}

template <class T>
Triangle<T>::Triangle(const MathVector<MathVector<T>>& other) : Matrix<T>(other) {
    this->_n = other.size();
    this->_type = TriangleType::Lower;
}

template <class T>
Triangle<T>::Triangle(const Triangle<T>& other_matrix) : Matrix<T>(other_matrix), 
_n(other_matrix._n), _type(other_matrix._type) {}

template<class T>
Triangle<T> Triangle<T>::add(const Triangle<T>& other) const {
    if (this->_n != other._n)
        throw std::logic_error("Matrixes have different sizes for addition");

    Triangle<T> result(*this);
    result.Matrix<T>::operator+=(other);
    return result;
}

template<class T>
Triangle<T> Triangle<T>::sub(const Triangle<T>& other) const {
    if (this->_n != other._n)
        throw std::logic_error("Matrixes have different sizes for subtraction");

    Triangle<T> result(*this);
    result.Matrix<T>::operator-=(other);
    return result;
}

template<class T>
Triangle<T> Triangle<T>::mult(const Triangle<T>& other) const {
    if (this->cols() != other.rows()) {
        throw std::logic_error("Triangle matrices dimensions do not match for multiplication!");
    }

    if (this->_type != other._type) {
        throw std::logic_error("Triangle matrices must have the same type for multiplication!");
    }

    const Matrix<T>& this_matrix = *this; 
    const Matrix<T>& other_matrix = other;
    Matrix<T> result_matrix = this_matrix * other_matrix;

    return Triangle<T>(result_matrix);
}

template<class T>
Triangle<T> Triangle<T>::mult_by_number(const T& value) const {
    const Matrix<T>& this_matrix = *this;

    Matrix<T> result_matrix = this_matrix * value;

    return Triangle<T>(result_matrix);
}

template<class T>
Triangle<T> Triangle<T>::div_by_number(const T& value) const {
    const Matrix<T>& this_matrix = *this;

    Matrix<T> result_matrix = this_matrix / value;

    return Triangle<T>(result_matrix);
}

template <class T>
Triangle<T> Triangle<T>::operator +(const Triangle<T>& second) const {
    return this->Triangle<T>::add(second);
}

template <class T>
Triangle<T>& Triangle<T>::operator+=(const Triangle<T>& second) {
    *this = *this + second;
    return *this;
}

template <class T>
Triangle<T> Triangle<T>::operator-(const Triangle<T>& second) const {
    return this->Triangle<T>::sub(second);
}

template <class T>
Triangle<T>& Triangle<T>::operator-=(const Triangle<T>& second) {
    *this = *this - second;
    return *this;
}

template <class T>
Triangle<T> Triangle<T>::operator *(const Triangle<T>& second) const {
    return this->Triangle<T>::mult(second);
}


template <class T>
Triangle<T> Triangle<T>::operator*(const T& value) const {
    return this->Triangle<T>::mult_by_number(value);
}

template <class T>
Triangle<T>& Triangle<T>::operator *=(const T& value) {
    *this = *this * value;
    return *this;
}

template <class T>
Triangle<T> Triangle<T>::operator/(const T& scalar) const {
    return this->Triangle<T>::div_by_number(scalar);
}

template <class T>
Triangle<T>& Triangle<T>::operator/=(const T& value) {
    *this = *this / value;
    return *this;
}

template <class T>
MathVector<T> Triangle<T>::operator*(const MathVector<T>& vector) const {
    if (vector.size() != _n)
        throw std::logic_error("Wrong sizes");

    MathVector<T> result(_n);
    for (int i = 0; i < _n; i++) {
        T sum = T(0);
        for (int j = 0; j <= i; j++) {
            sum += (*this)[i][j] * vector[j];
        }
        result[i] = sum;
    }
    return result;
}

template <class T>
Triangle<T>& Triangle<T>::operator=(const Triangle<T>& other_matrix) {
    if (&other_matrix == this)
        return *this;

    this->_n = other_matrix._n;
    this->_type = other_matrix._type;

    (*this).MathVector<MathVector<T>>::operator=(other_matrix);

    return *this;
}

template <class T>
bool Triangle<T>::operator==(const Triangle<T>& other_matrix) {
    if (&other_matrix == this)
        return true;
    if (this->_n != other_matrix._n)
        return false;

    return (*this).MathVector<MathVector<T>>::operator==(other_matrix);
}

template <class T>
bool Triangle<T>::operator!=(const Triangle<T>& other_matrix) {
    return !((*this) == other_matrix);
}