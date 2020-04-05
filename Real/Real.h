#pragma once
#include "Rational.h"

class Real
{
private:
	Rational a_, b_;
	
public:
	Real(Rational a, Rational b);
	Real(const Real& other);
	Real& operator=(const Real& other);
	~Real() = default;

	Real& operator+=(const Real& other);
	Real& operator-=(const Real& other);
	Real& operator*=(const Real& other);
	Real& operator/=(const Real& other);

	bool operator==(const Real& other) const;

	bool isNaN() const;
	bool containsZero() const;
};

Real operator+(Real a, const Real& b);
Real operator-(Real a, const Real& b);
Real operator*(Real a, const Real& b);
Real operator/(Real a, const Real& b);

const Real REAL_NaN = Real(RATIONAL_NaN, RATIONAL_NaN);