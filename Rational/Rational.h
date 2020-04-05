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

	bool isNaN() const; // Checks if p = 0 and q = 0
};