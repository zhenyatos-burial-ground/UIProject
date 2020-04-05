#include "Real.h"
#include "Error.h"
#include <algorithm>

const std::string CLASS_PREFIX = "[Real] ";

class RealError : public Error
{
public:
	enum Code
	{
		OK = 0,
		EMPTY_INTERVAL = 1,
		ADD_WITH_NAN = 2,
		SUB_WITH_NAN = 3,
		MULT_WITH_NAN = 4
	};
	RealError(const Code code);

private:
	std::string getMessage(const Code code);
};

RealError::RealError(const Code code)
	: Error(code, getMessage(code))
{}

std::string RealError::getMessage(const Code code)
{
	switch (code)
	{
	case OK:
		return "";
		break;
	case EMPTY_INTERVAL:
		return CLASS_PREFIX + "[a, b] is empty if a > b, SWAP";
		break;
	case ADD_WITH_NAN:
		return CLASS_PREFIX + "(+ NaN) is undefined";
		break;
	case SUB_WITH_NAN:
		return CLASS_PREFIX + "(- NaN) is undefined";
		break;
	case MULT_WITH_NAN:
		return CLASS_PREFIX + "(* NaN) is undefined";
		break;
	}
}


Real::Real(Rational a, Rational b)
	: a_(a), b_(b)
{
	if (a.isNaN() || b.isNaN())
	{
		*this = REAL_NaN;
		return;
	}

	if (a > b)
	{
		std::cerr << RealError(RealError::EMPTY_INTERVAL) << "\n";
		std::swap(a_, b_);
	}
}

Real::Real(const Real& other)
	: a_(other.a_), b_(other.b_)
{}

Real& Real::operator=(const Real& other)
{
	a_ = other.a_;
	b_ = other.b_;
	return *this;
}

Real& Real::operator+=(const Real& other)
{
	if (isNaN() || other.isNaN())
	{
		std::cerr << RealError(RealError::ADD_WITH_NAN) << "\n";
		return *this;
	}

	a_ = a_ + other.a_;
	b_ = b_ + other.b_;

	return *this;
}

Real& Real::operator-=(const Real& other)
{
	if (isNaN() || other.isNaN())
	{
		std::cerr << RealError(RealError::SUB_WITH_NAN) << "\n";
		return *this;
	}

	a_ = a_ - other.b_;
	b_ = b_ - other.a_;

	return *this;
}

Real& Real::operator*=(const Real& other)
{
	if (isNaN() || other.isNaN())
	{
		std::cerr << RealError(RealError::MULT_WITH_NAN) << "\n";
		return *this;
	}

	Rational a = 
			std::min(a_ * other.a_,
			std::min(a_ * other.b_,
			std::min(b_ * other.a_, b_ * other.b_)));
	Rational b =
			std::max(a_ * other.a_,
			std::max(a_ * other.b_,
			std::max(b_ * other.a_, b_ * other.b_)));

	a_ = a;
	b_ = b;

	return *this;
}

Real& Real::operator/=(const Real& other)
{
	return *this;
}

bool Real::operator==(const Real& other) const
{
	return (a_ == other.a_) && (b_ == other.b_);
}

bool Real::isNaN() const
{
	return (a_.isNaN()) && (b_.isNaN());
}

Real operator+(Real a, const Real& b)
{
	a += b;
	return a;
}

Real operator-(Real a, const Real& b)
{
	a -= b;
	return a;
}

Real operator*(Real a, const Real& b)
{
	a *= b;
	return a;
}
