#pragma once
#include <cstddef> 
#include <stdlib.h> 
#include <time.h> 
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "../lib_TVector/tvector.h"

template<typename T> class MathVector;

template <typename T>
std::ostream& operator<<(std::ostream& os, const MathVector<T>& vec);

template <typename T>
MathVector<T> operator+(T value, const MathVector<T>& vec);

template <typename T>
MathVector<T> operator*(T value, const MathVector<T>& vec);

template <typename T>
class MathVector : public TVector<T> {
public:
    MathVector() : TVector<T>() {}
    explicit MathVector(size_t size) : TVector<T>(size) {}
    MathVector(const T* arr, size_t size) : TVector<T>(arr, size) {}
    MathVector(const MathVector<T>& other) : TVector<T>(other) {}
    MathVector(size_t size, const T& value) : TVector<T>(size) {
        for (size_t i = 0; i < size; ++i) {
            (*this)[i] = value;
        }
    }
    T the_scalar_product(const MathVector<T>& other) const;
    T norm() const;
    MathVector<T> normalized() const;

    inline T& operator[](size_t index);
    inline const T& operator[](size_t index) const;

    MathVector<T>& operator=(const MathVector<T>& other);
    bool operator==(const MathVector<T>& other) const;
    bool operator!=(const MathVector<T>& other) const;

    size_t start_index() const;

    MathVector<T> operator+(const MathVector<T>& other) const;
    MathVector<T> operator-(const MathVector<T>& other) const;
    MathVector<T> operator*(const MathVector<T>& other) const;
    MathVector<T> operator/(const MathVector<T>& other) const;

    MathVector<T> operator+(T value) const;
    MathVector<T> operator-(T value) const;
    MathVector<T> operator*(T value) const;
    MathVector<T> operator/(T value) const;

    MathVector<T>& operator+=(const MathVector<T>& other);
    MathVector<T>& operator-=(const MathVector<T>& other);
    MathVector<T>& operator*=(const MathVector<T>& other);
    MathVector<T>& operator/=(const MathVector<T>& other);

    MathVector<T>& operator+=(T value);
    MathVector<T>& operator-=(T value);
    MathVector<T>& operator*=(T value);
    MathVector<T>& operator/=(T value);

    MathVector<T> operator-() const;
    MathVector<T> operator+() const;
    friend MathVector<T> operator+(T value, const MathVector<T>& vec) {
        MathVector<T> result(vec.size());
        for (size_t i = 0; i < vec.size(); i++) {
            result[i] = value + vec[i];
        }
        return result;
    }

    friend MathVector<T> operator*(T value, const MathVector<T>& vec) {
        MathVector<T> result(vec.size());
        for (size_t i = 0; i < vec.size(); i++) {
            result[i] = value * vec[i];
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const MathVector<T>& vec) {
        os << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            os << vec[i];
            if (i < vec.size() - 1) os << ", ";
        }
        os << "]";
        return os;
    }
};




template <typename T>
T MathVector<T>::the_scalar_product(const MathVector<T>& other) const {
    if (this->size() != other.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    T result{};
    for (size_t i = 0; i < this->size(); i++) {
        result += (*this)[i] * other[i];
    }
    return result;
}

template <typename T>
T MathVector<T>::norm() const {
    return std::sqrt(this->the_scalar_product(*this));
}

template <typename T>
MathVector<T> MathVector<T>::normalized() const {
    T length = this->norm();
    if (length == 0) {
        throw std::invalid_argument("Cannot normalize zero vector");
    }

    MathVector<T> result(this->size());
    for (size_t i = 0; i < this->size(); ++i) {
        result[i] = ((*this)[i]) / length;
    }
    return result;
}

template <typename T>
T& MathVector<T>::operator[](size_t index) {
    return TVector<T>::operator[](index);
}

template <typename T>
const T& MathVector<T>::operator[](size_t index) const {
    return TVector<T>::operator[](index);
}


template <typename T>
MathVector<T>& MathVector<T>::operator=(const MathVector<T>& other) {
    if (this != &other) {
        TVector<T>::operator=(other);
    }
    return *this;
}

template <typename T>
bool MathVector<T>::operator==(const MathVector<T>& other) const {
    if (this == &other) return true;
    if (this->size() != other.size()) return false;

    for (size_t i = 0; i < this->size(); ++i) {
        if (this->get(i) != other.get(i)) return false;
    }
    return true;
}

template <typename T>
bool MathVector<T>::operator!=(const MathVector<T>& other) const {
    return !(*this == other);
}

template <typename T>
MathVector<T> MathVector<T>::operator+(const MathVector<T>& other) const {
    if (this->size() != other.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    MathVector<T> result(this->size());
    for (size_t i = 0; i < this->size(); i++) {
        result[i] = (*this)[i] + other[i];
    }
    return result;
}

template <typename T>
MathVector<T> MathVector<T>::operator+(T value) const {
    MathVector<T> result(this->size());
    for (size_t i = 0; i < this->size(); i++) {
        result[i] = (*this)[i] + value;
    }
    return result;
}

template <typename T>
MathVector<T> MathVector<T>::operator-(const MathVector<T>& other) const {
    if (this->size() != other.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    MathVector<T> result(this->size());
    for (size_t i = 0; i < this->size(); i++) {
        result[i] = (*this)[i] - other[i];
    }
    return result;
}

template <typename T>
MathVector<T> MathVector<T>::operator-(T value) const {
    MathVector<T> result(this->size());
    for (size_t i = 0; i < this->size(); i++) {
        result[i] = (*this)[i] - value;
    }
    return result;
}


template <typename T>
MathVector<T> MathVector<T>::operator*(const MathVector<T>& other) const {
    if (this->size() != other.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    MathVector<T> result(this->size());
    for (size_t i = 0; i < this->size(); i++) {
        result[i] = (*this)[i] * other[i];
    }
    return result;
}


template <typename T>
MathVector<T> MathVector<T>::operator*(T value) const {
    MathVector<T> result(this->size());
    for (size_t i = 0; i < this->size(); i++) {
        result[i] = (*this)[i] * value;
    }
    return result;
}

template <typename T>
MathVector<T> MathVector<T>::operator/(const MathVector<T>& other) const {
    if (this->size() != other.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    MathVector<T> result(this->size());
    for (size_t i = 0; i < this->size(); i++) {
        if (other[i] == 0) {
            throw std::invalid_argument("The divisor cannot be equal to 0");
        }
        result[i] = (*this)[i] / other[i];
    }
    return result;
}

template <typename T>
MathVector<T> MathVector<T>::operator/(T value) const {
    MathVector<T> result(this->size());
    if (value == 0) {
        throw std::invalid_argument("The divisor cannot be equal to 0");
    }
    for (size_t i = 0; i < this->size(); i++) {
        result[i] = (*this)[i] / value;
    }
    return result;
}

template <typename T>
MathVector<T>& MathVector<T>::operator+=(const MathVector<T>& other) {
    if (this->size() != other.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    for (size_t i = 0; i < this->size(); i++) {
        (*this)[i] += other[i];
    }
    return *this;
}

template <typename T>
MathVector<T>& MathVector<T>::operator+=(T value) {
    for (size_t i = 0; i < this->size(); i++) {
        (*this)[i] += value;
    }
    return *this;
}

template <typename T>
MathVector<T>& MathVector<T>::operator-=(const MathVector<T>& other) {
    if (this->size() != other.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    for (size_t i = 0; i < this->size(); i++) {
        (*this)[i] -= other[i];
    }
    return *this;
}

template <typename T>
MathVector<T>& MathVector<T>::operator-=(T value) {
    for (size_t i = 0; i < this->size(); i++) {
        (*this)[i] -= value;
    }
    return *this;
}

template <typename T>
MathVector<T>& MathVector<T>::operator*=(const MathVector<T>& other) {
    if (this->size() != other.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    for (size_t i = 0; i < this->size(); i++) {
        (*this)[i] *= other[i];
    }
    return *this;
}

template <typename T>
MathVector<T>& MathVector<T>::operator*=(T value) {
    for (size_t i = 0; i < this->size(); i++) {
        (*this)[i] *= value;
    }
    return *this;
}

template <typename T>
MathVector<T>& MathVector<T>::operator/=(const MathVector<T>& other) {
    if (this->size() != other.size()) {
        throw std::invalid_argument("Vectors must have the same size for division");
    }
    for (size_t i = 0; i < this->size(); i++) {
        if (other[i] == 0) {
            throw std::invalid_argument("Division by zero in vector element at index " + std::to_string(i));
        }
        (*this)[i] /= other[i];
    }
    return *this;
}

template <typename T>
MathVector<T>& MathVector<T>::operator/=(T value) {
    if (value == 0) {
        throw std::invalid_argument("Division by zero");
    }
    for (size_t i = 0; i < this->size(); i++) {
        (*this)[i] /= value;
    }
    return *this;
}

template <typename T>
MathVector<T> MathVector<T>::operator-() const {
    MathVector<T> result(this->size());
    for (size_t i = 0; i < this->size(); ++i) {
        result[i] = -(*this)[i];
    }
    return result;
}

template <typename T>
MathVector<T> MathVector<T>::operator+() const {
    return *this;
}

template <typename T>
size_t MathVector<T>::start_index() const {
    for (size_t i = 0; i < this->size(); ++i) {
        if ((*this)[i] != T(0)) {
            return i;
        }
    }
    return this->size();
}