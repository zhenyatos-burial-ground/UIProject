#pragma once
#include "Integer.h"

class Rational
{
private:
	Integer p_, q_;
	void transform(); // Save invariants

public:
	Rational(Integer p, Integer q);
	Rational(int p, int q);
	Rational(Integer a);
	explicit Rational(int a);
	Rational(const Rational &other);
	Rational& operator= (const Rational& other);
	~Rational() = default;

	Rational& operator+=(const Rational& other);
	Rational& operator-=(const Rational& other);
	Rational& operator*=(const Rational& other);
	Rational& operator/=(const Rational& other);
	Rational operator-();

	bool operator==(const Rational& other) const;
	bool operator!=(const Rational& other) const;
	bool operator>(const Rational& other) const;
	bool operator>=(const Rational& other) const;
	bool operator<(const Rational& other) const;
	bool operator<=(const Rational& other) const;

	bool isNaN() const;

	friend std::ostream& operator<<(std::ostream& stream, const Rational& rational);
};

Rational operator+(Rational a, const Rational& b);
Rational operator-(Rational a, const Rational& b);
Rational operator*(Rational a, const Rational& b);
Rational operator/(Rational a, const Rational& b);

const Rational RATIONAL_NaN = { 0, 0 };