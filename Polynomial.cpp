#include <algorithm>
#include <initializer_list>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "Polynomial.h"

using std::endl;
using std::initializer_list;
using std::for_each;
using std::noshowpos;
using std::pair;
using std::showpos;

Polynomial::Polynomial()
{
}

Polynomial::Polynomial(Polynomial const& other)
    : m_polynomial(other.m_polynomial)
{
}

Polynomial::Polynomial(initializer_list<pair<coefficient_type, exponent_type>> il)
{
    for (auto const& p : il)
    {
        if (m_polynomial.count(p.second) == 1)
        {
            throw std::domain_error("Term exists in Polynomial");
        }
        m_polynomial[p.second] = p.first;
    }

    clear_zeroes();
}

Polynomial::~Polynomial()
{
}

Polynomial::exponent_type Polynomial::degree() const
{
    return m_polynomial.rbegin()->first;
}

Polynomial& Polynomial::operator+=(Polynomial const& other)
{
    for (auto const& ecp : other.m_polynomial)
    {
        m_polynomial[ecp.first] += ecp.second;
    }
    clear_zeroes();

    // for_each(other.m_polynomial.cbegin(), other.m_polynomial.cend(),
    //          [m_polynomial](pair<const exponent_type, coefficient_type> ecp)
    //          { m_polynomial[ecp.first] = ecp.second; });

    return *this;
}

Polynomial Polynomial::operator+(Polynomial const& other) const
{
    Polynomial ret(*this);
    ret += other;
    return ret;
}

Polynomial& Polynomial::operator+=(coefficient_type const& zero_coef)
{
    m_polynomial[exponent_type()] += zero_coef;

    return *this;
}

Polynomial Polynomial::operator+(coefficient_type const& zero_coef) const
{
    Polynomial ret(*this);

    ret += zero_coef;

    return ret;
}

Polynomial operator+(Polynomial::coefficient_type const& zero_coef, Polynomial const& p)
{
    return p + zero_coef;
}

Polynomial& Polynomial::operator*=(Polynomial const& other)
{
    m_polynomial = (*this * other).m_polynomial;

    return *this;
}

Polynomial Polynomial::operator*(Polynomial const& other) const
{
    Polynomial ret;

    for (auto const& ecp1 : m_polynomial)
    {
        for (auto const& ecp2 : other.m_polynomial)
        {
            ret.m_polynomial[ecp1.first + ecp2.first] += ecp1.second * ecp2.second;
        }
    }
    ret.clear_zeroes();

    return ret;
}

Polynomial Polynomial::operator*(Polynomial::coefficient_type const& ep) const
{
    Polynomial ret;

    for (auto const& ecp : m_polynomial)
    {
        ret.m_polynomial[ecp.first] = ecp.second * ep;
    }

    return ret;
}

Polynomial operator*(Polynomial::coefficient_type const& ep, Polynomial const& p)
{
    return p * ep;
}

Polynomial Polynomial::operator^(unsigned exp)
{
    Polynomial ret({{1, 0}});

    while (exp != 0)
    {
        ret *= *this;

        exp--;
    }

    return ret;
}

std::ostream& operator<<(std::ostream& os, Polynomial const& p)
{
    bool show_sign = false;
    for (auto const& ecp : p.m_polynomial)
    {
        if (show_sign)
        {
            os << showpos << ecp.second << noshowpos;
        }
        else
        {
            os << ecp.second;
        }
        show_sign = true;
        
        if (ecp.second != Polynomial::coefficient_type())
        {
            if (ecp.first != Polynomial::exponent_type())
            {
                os << "x^" << ecp.first;
            }
        }
    }

    return os;
}

void Polynomial::clear_zeroes()
{
    auto it = m_polynomial.begin();

    while (it != m_polynomial.end())
    {
        if (it->second == coefficient_type())
        {
            it = m_polynomial.erase(it);
        }

        it++;
    }
}
