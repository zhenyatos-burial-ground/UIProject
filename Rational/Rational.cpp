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
		DIVIDED_BY_ZERO = 2,
		ADD_WITH_NAN = 3,
		SUB_WITH_NAN = 4
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
		return CLASS_PREFIX + "Rational (p /= 0, q = 0) is undefined";
		break;
	case DIVIDED_BY_ZERO:
		return CLASS_PREFIX + "(/ 0) is undefined";
		break;
	case ADD_WITH_NAN:
		return CLASS_PREFIX + "(+ NaN) is undefined";
		break;
	case SUB_WITH_NAN:
		return CLASS_PREFIX + "(- Nan) is undefined";
		break;
	}
}

void Rational::transform()
{
	if (p_ == 0)
	{
		q_ = 1;
		return;
	}

	if (q_ < 0)
	{
		p_ = -p_;
		q_ = -q_;
	}

	Integer gcd = GCD(p_, q_);
	gcd = gcd < 0 ? -gcd : gcd; // If GCD is negative
	p_ /= gcd;
	q_ /= gcd;
}

Rational::Rational(Integer p, Integer q)
	: p_(p), q_(q)
{
	if (q == 0)
		if (p != 0)
		{
			std::cerr << RationalError(RationalError::ZERO_DENOMINATOR) << "\n";
			p_ = 0;
			return;
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

Rational::Rational(const Rational& other)
	: p_(other.p_), q_(other.q_)
{}

Rational& Rational::operator=(const Rational& other)
{
	p_ = other.p_;
	q_ = other.q_;
	return *this;
}

Rational& Rational::operator+=(const Rational& other)
{
	if (isNaN() || other.isNaN())
	{
		std::cerr << RationalError(RationalError::ADD_WITH_NAN) << "\n";
		return *this;
	}

	p_ = p_ * other.q_ + q_ * other.p_;
	q_ *= other.q_;
	transform();

	return *this;
}

Rational& Rational::operator-=(const Rational& other)
{
	if (isNaN() || other.isNaN())
	{
		std::cerr << RationalError(RationalError::SUB_WITH_NAN) << "\n";
		return *this;
	}

	p_ = p_ * other.q_ - q_ * other.p_;
	q_ *= other.q_;
	transform();

	return *this;
}

bool Rational::isNaN() const
{
	return (p_ == 0) && (q_ == 0);
}

Rational operator+(Rational a, const Rational& b)
{
	a += b;
	return a;
}

Rational operator-(Rational a, const Rational& b)
{
	a -= b;
	return a;
}
