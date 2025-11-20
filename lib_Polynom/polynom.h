#include <iostream>
#include <exception>
#include "../lib_Monom/monom.h"
//#include "../lib_List/list.h"

class Polynom {
	std::string _name;
	List <Monom> _polynom;
public:
	Polynom();
	Polynom(const Monom& monom) {
		_polynom.push_back(monom);
	}
	Polynom(std::string str) {
		//парсить переданную строку в моном
	}

	Polynom& operator+=(const Monom& other);
	Polynom& operator-=(const Monom& other);
	Polynom& operator*=(const Monom& other);
	Polynom& operator/=(const Monom& other);

	bool operator==(const Monom& other) const;
	bool operator!=(const Monom& other) const;

	Polynom operator+(const Polynom& other) const;
	Polynom operator-(const Polynom& other) const;
	Polynom operator*(const Polynom& other) const;
	Polynom operator/(const Polynom& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Polynom& p);
	friend std::istream& operator>>(std::istream& is, Polynom& p);
};
//+, -, *, /, ==, !=, *=, +=, /=, -=,  >>, <<
// Polynom +,*, -, / Monom


Polynom::Polynom() {
	Monom zero;
	_polynom.push_back(zero);
}


Polynom Polynom::operator*(const Polynom& other) const{
	Polynom res;
	for (auto it1 = _polynom.begin(); ;) {
		for (auto it2 = _polynom.begin(); ;) {
		res += (*it1) * (*it2);
}
	}
}

inline Polynom Polynom::operator/(const Polynom& other) const
{
	return Polynom();
}

Polynom& Polynom::operator+=(const Monom& other){
Polynom res(*this);
	auto it = res.begin();
	prev_it = nullptr;
	for (; *it > other; it++) {
		&& it != end()
	}
	push_front();
}
Polynom& Polynom::operator-=(const Monom& other)
{
	return;

}
Polynom& Polynom::operator*=(const Monom& other)
{
	return;

}
Polynom& Polynom::operator/=(const Monom& other)
{
	return;
}

inline bool Polynom::operator==(const Monom& other) const
{
	return false;
}

inline bool Polynom::operator!=(const Monom& other) const
{
	return false;
}

inline Polynom Polynom::operator+(const Polynom& other) const
{
	return Polynom();
}

inline Polynom Polynom::operator-(const Polynom& other) const
{
	return Polynom();
}










//1 проверить на подобие, ели подобны, то вызвать Monom + Monom
//3  вклинить other после prev_it
// 2 if(prev_it == nullptr)
