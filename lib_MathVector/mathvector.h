#include <cstddef> 
#include <stdlib.h> 
#include <time.h> 
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "../lib_TVector/tvector.h"


template <typename T>
class MathVector : public TVector<T> {
public:
    MathVector() : TVector<T>() {}  
    explicit MathVector(size_t size) : TVector<T>(size) {} 
    MathVector(const T* arr, size_t size) : TVector<T>(arr, size) {}  
    MathVector(const MathVector<T>& other) : TVector<T>(other) {}  

    T dot(const MathVector<T>& other) const;
    T norm() const;
    MathVector<T> normalized() const;

    MathVector<T> operator+(const MathVector<T>& other) const;
    MathVector<T> operator+(T value) const;

    MathVector<T> operator-(const MathVector<T>& other) const;
    MathVector<T> operator-(T value) const;

    MathVector<T> operator*(const MathVector<T>& other) const;
    MathVector<T> operator*(T value) const;

    MathVector<T> operator/(const MathVector<T>& other) const;
    MathVector<T> operator/(T value) const;

    MathVector<T>& operator+=(const MathVector<T>& other);
    MathVector<T>& operator+=(T value);
    MathVector<T>& operator-=(const MathVector<T>& other);
    MathVector<T>& operator-=(T value);
    MathVector<T>& operator*=(const MathVector<T>& other);
    MathVector<T>& operator*=(T value);
    MathVector<T>& operator/=(const MathVector<T>& other);
    MathVector<T>& operator/=(T value);
     
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


};


template <typename T>
T MathVector<T>::dot(const MathVector<T>& other) const {

}
    
template <typename T>
T MathVector<T>::norm() const {

}

template <typename T>
MathVector<T> MathVector<T>::normalized() const {

}

template <typename T>
MathVector<T> MathVector<T>::operator+(const MathVector<T>& other) const {
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









//template <typename T>
//MathVector<T> operator+(T value, const MathVector<T>& vec) {
//    MathVector<T> result(vec.size());
//    for (size_t i = 0; i < vec.size(); i++) {
//        result[i] = value + vec[i];
//    }
//    return result;
//}
//
//template <typename T>
//MathVector<T> operator*(T value, const MathVector<T>& vec) {
//    MathVector<T> result(vec.size());
//    for (size_t i = 0; i < vec.size(); i++) {
//        result[i] = value * vec[i];
//    }
//    return result;
//}
