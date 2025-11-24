#pragma once

#include <iostream>
#include <exception>
#include <string>
#include "../lib_Monom/monom.h"
#include "../lib_Double_List/double_list.h"
#include <sstream>
#include <cctype>

class Polynom {
    std::string _name;
    Double_List <Monom> _polynom;
public:
    Polynom();
    Polynom(const Monom& monom);
    Polynom(std::string str);
    Polynom(Double_List<Monom> monoms);
    inline Polynom(const Polynom& other) : _polynom(other._polynom) {
        
    }

    Polynom& operator+=(const Monom& other);
    Polynom& operator-=(const Monom& other);
    Polynom& operator*=(const Monom& other);
    Polynom& operator/=(const Monom& other);

    bool operator==(const Monom& other) const;
    bool operator!=(const Monom& other) const;

    inline bool operator==(const Polynom& other) const {
        if (this->get_size() != other.get_size()) {
            return false;
        }

        auto it1 = _polynom.begin();
        auto it2 = other._polynom.begin();

        while (it1 != _polynom.end() && it2 != other._polynom.end()) {
            if (!(*it1 == *it2)) {
                return false;
            }
            ++it1;
            ++it2;
        }
        return true;
    }

    Polynom operator+(const Polynom& other) const;
    Polynom operator-(const Polynom& other) const;
    Polynom operator*(const Polynom& other) const;
    Polynom operator/(const Polynom& other) const;

    inline size_t get_size() const { return _polynom.get_size(); }

    inline typename Double_List<Monom>::Iterator begin() const { return _polynom.begin(); }
    inline typename Double_List<Monom>::Iterator end() const { return _polynom.end(); }

    friend std::ostream& operator<<(std::ostream& os, const Polynom& p);
    friend std::istream& operator>>(std::istream& is, Polynom& p);
};


inline Polynom::Polynom() {
    Monom zero;
    _polynom.push_back(zero);
}

inline Polynom::Polynom(const Monom& monom) {
    if (monom.get_coeff() != 0.0) {
        _polynom.push_back(monom);
    }
}

Polynom::Polynom(std::string str) {
    std::istringstream iss(str);
    iss >> *this;
}

Polynom::Polynom(Double_List<Monom> monoms) : _polynom(monoms) {
   
}

Polynom& Polynom::operator+=(const Monom& other) {
    
    if (other.get_coeff() == 0) {
        
        return *this;
    }

    auto it = _polynom.begin();
    while (it != _polynom.end()) {
        
        if ((*it).is_like(other)) { 
            
            *it += other;
            if ((*it).get_coeff() == 0.0) {
                
                
                it = _polynom.erase(it.get_current_node());
                
            } else {
                
                ++it;
            }
            
            return *this;
        }
        ++it;
    }
    if (other.get_coeff() != 0.0) {
        
        _polynom.push_back(other);
        
    }
    
    return *this;
}

inline Polynom& Polynom::operator-=(const Monom& other) {
    Monom negated = other;
    negated.negate(); 
    *this += negated;
    return *this;
}

inline Polynom& Polynom::operator*=(const Monom& other) {
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        *it *= other;
    }
    return *this;
}

inline Polynom& Polynom::operator/=(const Monom& other) {
    if (other.get_coeff() == 0.0) {
        throw std::invalid_argument("Division by zero coefficient");
    }
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        *it /= other;
    }
    return *this;
}

inline bool Polynom::operator==(const Monom& other) const {
    if (_polynom.get_size() != 1) return false;
    return _polynom.head() == other;
}

inline bool Polynom::operator!=(const Monom& other) const {
    return !(*this == other);
}

inline Polynom Polynom::operator+(const Polynom& other) const {
    Polynom result = *this;
    for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it) {
        result += *it;
    }
    return result;
}

inline Polynom Polynom::operator-(const Polynom& other) const {
    Polynom result = *this;
    for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it) {
        result -= *it;
    }
    return result;
}

inline Polynom Polynom::operator*(const Polynom& other) const {
    Double_List<Monom> temp_monoms;
    for (auto it1 = _polynom.begin(); it1 != _polynom.end(); ++it1) {
        for (auto it2 = other._polynom.begin(); it2 != other._polynom.end(); ++it2) {
            temp_monoms.push_back((*it1) * (*it2));
        }
    }

    Polynom result;
    for (auto it = temp_monoms.begin(); it != temp_monoms.end(); ++it) {
        result += *it; 
    }
    return result;
}

inline Polynom Polynom::operator/(const Polynom& other) const {
    
    if (other._polynom.is_empty()) {
        throw std::invalid_argument("Division by an empty polynomial");
    }

    if (other._polynom.get_size() > 1) {
        
        throw std::invalid_argument("Polynomial long division is not yet supported. Cannot divide by a polynomial with multiple terms.");
    }
    
    if (other._polynom.get_size() == 1) {
        if (other._polynom.head().get_coeff() == 0) {
            throw std::invalid_argument("Division by zero polynomial");
        }
        Polynom result = *this;
        result /= other._polynom.head(); 
        return result;
    }
    throw std::invalid_argument("Unhandled polynomial division scenario.");
}

inline std::ostream& operator<<(std::ostream& os, const Polynom& p)
{
    auto it = p._polynom.begin();
    if (it != p._polynom.end()) {
        os << *it;
        ++it;
        for (; it != p._polynom.end(); ++it) {
            if ((*it).get_coeff() < 0) {
                os << " - " << (*it).get_coeff() * (-1) << (*it).get_variables();
            }
            else {
                os << " + " << *it;
            }
        }
    }
    else {
        os << "0";
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, Polynom& p)
{
    std::string str;
    std::getline(is, str);

    p._polynom.clear(); 

    size_t pos = 0;
    bool first_term_encountered = false; 

    while (pos < str.length()) {
        while (pos < str.length() && str[pos] == ' ') {
            pos++;
        }
        if (pos == str.length()) break; 

        int sign = 1; 
       
        if (str[pos] == '-') {
            sign = -1;
            pos++;
            
            while (pos < str.length() && str[pos] == ' ') {
                pos++;
            }
        } else if (str[pos] == '+') {
            sign = 1;
            pos++;
           
            while (pos < str.length() && str[pos] == ' ') {
                pos++;
            }
        } else if (first_term_encountered) {
          
            sign = 1;
        }
        


        double coeff = 1.0;
        size_t num_start = pos;
        bool coeff_parsed = false;
        while (pos < str.length() && (isdigit(str[pos]) || str[pos] == '.')) {
            pos++;
            coeff_parsed = true;
        }
        if (pos > num_start) {
            coeff = std::stod(str.substr(num_start, pos - num_start));
        }
        else if (!coeff_parsed && pos < str.length() && (str[pos] == 'x' || str[pos] == 'y' || str[pos] == 'z')) {
            coeff = 1.0;
        }

        coeff *= sign; 

        Monom new_monom(coeff);

      
        
        while (pos < str.length() && str[pos] != '+' && str[pos] != '-' && str[pos] != ' ') {
            if (str[pos] == 'x' || str[pos] == 'y' || str[pos] == 'z') {
                char var = str[pos];
                pos++;
                int power = 1;
                if (pos < str.length() && str[pos] == '^') {
                    pos++;
                    size_t power_start = pos;
                    while (pos < str.length() && isdigit(str[pos])) {
                        pos++;
                    }
                    if (pos > power_start) {
                        power = std::stoi(str.substr(power_start, pos - power_start));
                    } else {
                        throw std::invalid_argument("Invalid monomial format: missing power after '^'");
                    }
                }
                if (var == 'x') new_monom.set_power(0, power);
                else if (var == 'y') new_monom.set_power(1, power);
                else if (var == 'z') new_monom.set_power(2, power);
            } else if (str[pos] == '*') {
                pos++;
            } else {
                throw std::invalid_argument("Invalid monomial format: unexpected character");
            }
        }

        p += new_monom;
        first_term_encountered = true; 
    }
    return is;
}

#endif
