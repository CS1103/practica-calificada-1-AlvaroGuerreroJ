#ifndef GUARD_POLYNOMIAL_H
#define GUARD_POLYNOMIAL_H

#include <initializer_list>
#include <iostream>
#include <map>
#include <ostream>
#include <stdexcept>
#include <utility>

class Polynomial
{
public:
    using exponent_type = unsigned;
    using coefficient_type = int;

private:
    std::map<exponent_type, coefficient_type> m_polynomial;

public:
    Polynomial();
    Polynomial(Polynomial const& other);
    Polynomial(std::initializer_list<std::pair<coefficient_type, exponent_type>>);
    ~Polynomial();

    exponent_type degree() const;

    Polynomial& operator+=(Polynomial const& other);
    Polynomial operator+(Polynomial const& other) const;

    Polynomial& operator+=(coefficient_type const& zero_coef);
    Polynomial operator+(coefficient_type const& zero_coef) const;
    friend Polynomial operator+(coefficient_type const& zero_coef, Polynomial const& p);

    Polynomial& operator*=(Polynomial const& other);
    Polynomial operator*(Polynomial const& other) const;
    Polynomial operator*(coefficient_type const& ep) const;
    friend Polynomial operator*(coefficient_type const& ep, Polynomial const& p);

    Polynomial operator^(unsigned exp);

    friend std::ostream& operator<<(std::ostream& os, Polynomial const& p);

private:
    void clear_zeroes();
};

#endif
