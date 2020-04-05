#pragma once
#include "Integer.h"

class Rational
{
private:
	Integer p, q;
	void transform();
public:
	Rational(Integer p, Integer q);
	Rational(int p, int q);
	Rational(Integer a);
	explicit Rational(int a);
};