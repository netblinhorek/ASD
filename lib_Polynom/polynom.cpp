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

        while (i < n && (str[i] == ' ' || str[i] == '\t')) {
            i++;
        }

        double coeff = 0;
        int digit_count = 0;
        while (i < n && str[i] >= '0' && str[i] <= '9') {
            coeff = coeff * 10 + (str[i] - '0');
            i++;
            digit_count++;
        }
        if (digit_count == 0) {
            coeff = 1.0;
        }
        coeff = coeff * sign;

        int powers[3] = { 0, 0, 0 };

        while (i < n && (str[i] == 'x' || str[i] == 'y' || str[i] == 'z')) {
            int var_index;
            if (str[i] == 'x') var_index = 0;
            else if (str[i] == 'y') var_index = 1;
            else var_index = 2;
            i++;

            if (i < n && str[i] == '^') {
                i++;
                int power = 0;
                while (i < n && str[i] >= '0' && str[i] <= '9') {
                    power = power * 10 + (str[i] - '0');
                    i++;
                }
                powers[var_index] = power;
            }
            else {
                powers[var_index] = 1;
            }
        }

        Monom m(coeff, powers[0], powers[1], powers[2]);
        add_monom(m);
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
    if (other.get_coeff() == 0.0) {
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

bool Polynom::operator!=(const Monom& other) const {
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
    if (other._polynom.is_empty()) {
        throw std::invalid_argument("Division by zero (empty polynomial)");
    }

    Polynom quotient;           
    Polynom remainder = *this;  

    Monom divisor_first = *(other._polynom.begin());

    while (!remainder._polynom.is_empty()) {
        Monom remainder_first = *(remainder._polynom.begin());

        bool can_divide = true;
        for (int i = 0; i < 3; i++) {
            if (remainder_first.get_power(i) < divisor_first.get_power(i)) {
                can_divide = false;
                break;
            }
        }

        if (!can_divide) {
            break;
        }

        Monom quotient_term = remainder_first / divisor_first;

        quotient.add_monom(quotient_term);

        Polynom to_subtract = other * quotient_term;
        remainder = remainder - to_subtract;
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

bool Polynom::operator<(const Polynom& other) const
{
    auto it1 = _polynom.begin();
    auto it2 = other._polynom.begin();

    while (it1 != _polynom.end() && it2 != other._polynom.end()) {
        if (*it1 < *it2) return true;
        if (*it2 < *it1) return false;
        ++it1;
        ++it2;
    }

    return false; 
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

    std::stringstream ss;
    auto it = p._polynom.begin();
    ss << *it;

    for (++it; it != p._polynom.end(); ++it) {
        if ((*it).get_coeff() > 0) ss << " + ";
        else ss << " ";

        ss << *it; 
    }

    return os << ss.str(); 
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

