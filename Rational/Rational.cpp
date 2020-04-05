#include "Rational.h"
#include "Error.h"

const std::string CLASS_PREFIX = "[Rational] ";

class RationalError : public Error
{
public:
	enum Code
	{
		OK = 0,
		ZERO_DENOMINATOR = 1,
		DIVIDED_BY_ZERO = 2
	};
	RationalError(const Code code);

private:
	std::string getMessage(const Code code);
};

RationalError::RationalError(const Code code)
	: Error(code, getMessage(code))
{}

std::string RationalError::getMessage(const Code code)
{
	switch (code)
	{
	case OK:
		return "";
		break;
	case ZERO_DENOMINATOR:
		return CLASS_PREFIX + "can't build Rational with p /= 0, q = 0";
		break;
	}
}

void Rational::transform()
{
	if (p == 0)
	{
		q = 1;
		return;
	}

	if (q < 0)
	{
		p = -p;
		q = -q;
	}

	Integer gcd = GCD(p, q);
	gcd = gcd < 0 ? -gcd : gcd; // If GCD is negative
	p /= gcd;
	q /= gcd;
}

Rational::Rational(Integer p, Integer q)
	: p(p), q(q)
{
	if (q == 0)
		if (p != 0)
		{
			std::cerr << RationalError(RationalError::ZERO_DENOMINATOR) << "\n";
			p = 0;
		}
		else
			return;
	
	transform();
}

Rational::Rational(int p, int q)
	: Rational(Integer(p), Integer(q))
{}

Rational::Rational(Integer a)
	: Rational(a, Integer(1))
{}

Rational::Rational(int a)
	: Rational(a, 1)
{}
