#include <iostream>
#include <exception>

#define VARS_COUNT
class Monom {
	double _coeff;
	int _powers[VARS_COUNT];  // нужен конструктор копирования
public:
	Monom(double coeff = 0.0) : _coeff(coeff)
	{
		for (int i = 0; i < VARS_COUNT; i++) {
			_powers[i] = 0;
		}
	}
	Monom(Monom& other);
	
	// ==, !=, +, -, *, /, >, <, =
	bool operator !=(const Monom& other);
	bool operator ==(const Monom& other);
	

	bool operator>(const Monom& other);
	bool operator<(const Monom& other);
	
	Monom operator+(const Monom& other);
	Monom operator-(const Monom& other);
	Monom operator*(const Monom& other);
	Monom operator/(const Monom& other);

	bool operator =(const Monom& other);
		
};

Monom::Monom(Monom& other)
{
}

bool Monom::operator != (const Monom& other) {
	return !(*this == other);
}

bool Monom::operator>(const Monom& other) {
	for (int i = 0; i < VARS_COUNT; i++) {
		if (_powers[i] < other._powers[i]) {
			return false;
		}
		if (_powers[VARS_COUNT - 1] <= other._powers[VARS_COUNT - 1]) {
			return false;
		}
	}
	return true;
}
bool Monom::operator<(const Monom& other) {  // исправить 
	for (int i = 0; i < VARS_COUNT; i++) {
		if (_powers[i] < other._powers[i]) {
			return false;
		}
		if (_powers[VARS_COUNT - 1] <= other._powers[v_c - 1]) {
			return false;
		}
	}
	return true;
}
Monom Monom::operator+(const Monom& other) {
	if (*this != other) {
		throw std::invalid_argument("Невозможно выполнить сложение");
	}
	Monom res(*this);
	res._coeff += other._coeff;
	return res;
}