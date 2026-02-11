#include "../lib_Polynom/polynom.h"
#include <cctype>
#include <vector>

Polynom::Polynom() {
}

Polynom::Polynom(const Monom& monom) {
    add_monom(monom);
}

Polynom::Polynom(std::string str) {
    int n = static_cast<int>(str.length());
    int i = 0;

    while (i < n) {
        while (i < n && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')) {
            i++;
        }
        if (i >= n) break;

        double sign = 1.0;
        if (str[i] == '-') {
            sign = -1.0;
            i++;
        }
        else if (str[i] == '+') {
            i++;
        }

        while (i < n && (str[i] == ' ' || str[i] == '\t')) i++;

        double coeff = 0;
        bool has_digit = false;
        while (i < n && str[i] >= '0' && str[i] <= '9') {
            coeff = coeff * 10 + (str[i] - '0');
            i++;
            has_digit = true;
        }
        if (!has_digit) coeff = 1.0;
        coeff *= sign;

        int p[3] = { 0, 0, 0 };
        while (i < n && (str[i] == 'x' || str[i] == 'y' || str[i] == 'z')) {
            char var = str[i];
            int idx = (var == 'x') ? 0 : (var == 'y') ? 1 : 2;
            i++;

            if (i < n && str[i] == '^') {
                i++;
                int power = 0;
                while (i < n && str[i] >= '0' && str[i] <= '9') {
                    power = power * 10 + (str[i] - '0');
                    i++;
                }
                p[idx] = power;
            }
            else {
                p[idx] = 1;
            }
        }

        add_monom(Monom(coeff, p[0], p[1], p[2]));
    }
}

Polynom::Polynom(List<Monom> monoms) {
    for (auto it = monoms.begin(); it != monoms.end(); ++it) {
        add_monom(*it);
    }
}

Polynom& Polynom::operator+=(const Monom& other) {
    add_monom(other);
    return *this;
}


Polynom& Polynom::operator-=(const Monom& other) {
    Monom negated = other.operator-();
    this->operator+=(negated); 
    return *this;
}

Polynom& Polynom::operator*=(const Monom& other) {
    if (other.get_coeff() == 0.0) {
        _polynom.clear();
        return *this;
    }

    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        (*it).operator*=(other);
    }

    return *this;
}


Polynom& Polynom::operator/=(const Monom& other) {
    if (other.get_coeff() == 0) {
        throw std::invalid_argument("Division by zero");
    }

    List<Monom> new_list;
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        Monom m = *it;

        if (m.get_power(0) >= other.get_power(0) &&
            m.get_power(1) >= other.get_power(1) &&
            m.get_power(2) >= other.get_power(2))
        {
            m /= other; 

            if (m.get_coeff() != 0) {
                new_list.push_back(m);
            }
        }
    }

    _polynom = new_list;
    return *this;
}



bool Polynom::operator==(const Monom& other) const {
    if (_polynom.count() != 1) return false;
    return *(_polynom.begin()) == other; 
}

inline bool Polynom::operator!=(const Monom& other) const {
    return !(*this == other);
}

bool Polynom::operator==(const Polynom& other) const
{
    if (_polynom.count() != other._polynom.count())
        return false;
    auto it1 = _polynom.begin();
    auto it2 = other._polynom.begin();

    while (it1 != _polynom.end()) {
        if (*it1 != *it2)
            return false;
        it1++;
        it2++;
    }
    return true;
}

bool Polynom::operator!=(const Polynom& other) const
{
    return !(*this == other);
}

Polynom Polynom::operator+(const Polynom& other) const {
    Polynom result = *this;
    for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it) {
        result.operator+=(*it);
    }
    return result;
}

Polynom Polynom::operator-(const Polynom& other) const{
    Polynom result = *this;
    for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it) {
        result.operator-=(*it);
    }
    return result;
}

Polynom Polynom::operator*(const Polynom& other) const {
    Polynom res;
    for (auto it1 = _polynom.begin(); it1 != _polynom.end(); ++it1) {
        for (auto it2 = other._polynom.begin(); it2 != other._polynom.end(); ++it2) {
            Monom m1 = *it1;
            Monom m2 = *it2;
            Monom tmp = m1.operator*(m2); 

            (res).operator+=(tmp);
        }
    }
    return res;
}


Polynom Polynom::operator/(const Polynom& other) const {
    if (other._polynom.is_empty())
        throw std::invalid_argument("Division by zero (empty polynomial)");

    Polynom quotient;          
    Polynom dividend = *this;  

    Monom divisor_lead = *(other._polynom.begin());

    while (!dividend._polynom.is_empty()) {
        Monom dividend_lead = *(dividend._polynom.begin());

        bool can_divide = true;
        for (int i = 0; i < 3; ++i) {
            if (dividend_lead.get_power(i) < divisor_lead.get_power(i)) {
                can_divide = false;
                break;
            }
        }

        if (!can_divide) break; 

        Monom res_monom = dividend_lead / divisor_lead;

        quotient.add_monom(res_monom);

        Polynom subtrahend = other * res_monom;
        dividend = dividend - subtrahend;
    }

    return quotient;
}
Polynom Polynom::operator*(double scalar) const {
    Polynom res = *this;
    res.operator*=(scalar);
    return res;
}

Polynom Polynom::operator/(double scalar) const {
    Polynom res = *this;
    res.operator/=(scalar); 
    return res;
}
Polynom& Polynom::operator*=(double scalar) {
    if (scalar == 0.0) {
        _polynom.clear(); 
        return *this;
    }
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        (*it).operator*=(scalar);
    }
    return *this;
}

Polynom& Polynom::operator/=(double scalar) {
    if (scalar == 0.0) {
        throw std::invalid_argument("Division by zero");
    }
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        (*it).operator/=(scalar);
    }
    return *this;
}

double Polynom::calculate_at_point(double x, double y, double z) const {
    double point = 0.0;
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        point += (*it).evaluate_at_point(x, y, z);
    }

    return point;
}

void Polynom::add_monom(const Monom& m) {
    if (m.get_coeff() == 0.0) return;

    size_t index = 0;
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        if ((*it).is_like(m)) {
            (*it).operator+=(m);

            if ((*it).get_coeff() == 0.0) {
                _polynom.erase(index);
            }
            return;
        }
        if ((*it).operator<(m)) {
            _polynom.insert(index, m);
            return;
        }
        index++;
    }

    _polynom.push_back(m);
}

List<Monom>::Iterator Polynom::begin()
{
    return _polynom.begin();
}
List<Monom>::Iterator Polynom::end()
{
    return _polynom.end();
}

std::ostream& operator<<(std::ostream& os, const Polynom& p) {
    if (p._polynom.is_empty()) return os << "0";

    auto it = p._polynom.begin();
    os << *it; 
    for (++it; it != p._polynom.end(); ++it) {
        if ((*it).get_coeff() > 0) os << " + ";
        else os << " "; 

        os << *it; 
    }
    return os;
}
std::istream& operator>>(std::istream& is, Polynom& p) {
    p._polynom.clear();
    Monom m;
    while (is >> m) {
        p += m;
    }

    is.clear(); 
    return is;
}

