#include "Integer.h"
#include "Error.h"
#include <string>

const std::string CLASS_PREFIX = "[Integer] ";
const int MIN_VALUE = std::numeric_limits<int>::min();
const int MAX_VALUE = std::numeric_limits<int>::max();

class IntegerError : public Error
{
public:
	enum Code 
	{ 
		OK = 0, 
		ADD_OVERFLOW = 1, 
		MULT_OVERFLOW = 2, 
		SUB_OVERFLOW = 3, 
		DIVIDED_BY_ZERO = 4 
	};
	IntegerError(const Code code);

private:
	std::string getMessage(const Code code);
};

std::string IntegerError::getMessage(const Code code)
{
	switch (code) 
	{
	case OK:
		return "";
		break;
	case ADD_OVERFLOW:
		return CLASS_PREFIX + "(+) overflow detected";
		break;
	case MULT_OVERFLOW:
		return CLASS_PREFIX + "(*) overflow detected";
		break;
	case SUB_OVERFLOW:
		return CLASS_PREFIX + "(-) overflow detected";
		break;
	case DIVIDED_BY_ZERO:
		return CLASS_PREFIX + "(/ 0, % 0) is undefined";
		break;
	}
}

IntegerError::IntegerError(const Code code)
	: Error(code, getMessage(code))
{ }

Integer::Integer(int i)
	: i(i)
{}

Integer::Integer(const Integer& other)
	: i(other.i)
{}

Integer& Integer::operator=(const Integer& other)
{
	i = other.i;
	return *this;
}

Integer& Integer::operator=(int value)
{
	i = value;
	return *this;
}

Integer& Integer::operator+=(const Integer& other)
{
	if ((i >= 0) && (other.i >= 0) && (i > MAX_VALUE - other.i)) // Two non negative, can reach MAX
		std::cerr << IntegerError(IntegerError::ADD_OVERFLOW) << "\n";
	else if ((i < 0) && (other.i < 0) && (i < MIN_VALUE - other.i)) // Two negative, can reach MIN
		std::cerr << IntegerError(IntegerError::ADD_OVERFLOW) << "\n";
	else
		i += other.i; // No problemo, can't reach MIN or MAX

	return *this;
}

Integer& Integer::operator-=(const Integer & other)
{
	if ((i < 0) && (other.i >= 0) && (i < MIN_VALUE + other.i)) // Equivalent of two negative addition
		std::cerr << IntegerError(IntegerError::SUB_OVERFLOW) << "\n";
	else if ((i >= 0) && (other.i < 0) && (i > MAX_VALUE + other.i)) // Equivalent of two non-negative addition
		std::cerr << IntegerError(IntegerError::SUB_OVERFLOW) << "\n";
	else
		i -= other.i;

	return *this;
}

Integer& Integer::operator*=(const Integer& other)
{
	if (!i || !other.i) // At least one of the operands is zero
	{
		i = 0;
		return *this;
	}

	bool neg = (i < 0) && (other.i > 0) || (i > 0) && (other.i < 0); // Sign of *

	int a = i < 0 ? -i : i; // Absolute values
	int b = other.i < 0 ? -other.i : other.i; 

	if (MAX_VALUE / a < b)
		std::cerr << IntegerError(IntegerError::MULT_OVERFLOW) << "\n";
	else
		i = i * other.i;

	return *this;
}

Integer& Integer::operator/=(const Integer& other)
{
	if (other.i == 0)
		std::cerr << IntegerError(IntegerError::DIVIDED_BY_ZERO) << "\n";
	else
		i /= other.i;

	return *this;
}

Integer& Integer::operator%=(const Integer& other)
{
	if (other.i == 0)
		std::cerr << IntegerError(IntegerError::DIVIDED_BY_ZERO) << "\n";
	else
		i %= other.i;

	return *this;
}

Integer Integer::operator-()
{
	return Integer(-i);
}

bool Integer::operator==(const Integer& other) const
{
	return i == other.i;
}

bool Integer::operator!=(const Integer& other) const
{
	return i != other.i;
}

bool Integer::operator>(const Integer& other) const
{
	return i > other.i;
}

bool Integer::operator>=(const Integer& other) const
{
	return i >= other.i;
}

bool Integer::operator<(const Integer& other) const
{
	return i < other.i;
}

bool Integer::operator<=(const Integer& other) const
{
	return i <= other.i;
}

bool Integer::operator==(int value) const
{
	return i == value;
}

bool Integer::operator!=(int value) const
{
	return i != value;
}

bool Integer::operator>(int value) const
{
	return i > value;
}

bool Integer::operator>=(int value) const
{
	return i >= value;
}

bool Integer::operator<(int value) const
{
	return i < value;
}

bool Integer::operator<=(int value) const
{
	return i <= value;
}

Integer::operator int() const
{
	return i;
}

std::ostream& operator<<(std::ostream& stream, const Integer& integer)
{
	stream << integer.i;
	return stream;
}

std::istream& operator>>(std::istream& stream, Integer& integer)
{
	int x;
	stream >> x;
	integer.i = x;
	return stream;
}

Integer operator+(Integer a, const Integer & b)
{
	a += b;
	return a;
}

Integer operator-(Integer a, const Integer & b)
{
	a -= b;
	return a;
}

Integer operator*(Integer a, const Integer & b)
{
	a *= b;
	return a;
}

Integer operator/(Integer a, const Integer& b)
{
	a /= b;
	return a;
}

Integer operator%(Integer a, const Integer& b)
{
	a %= b;
	return a;
}


Integer GCD(Integer a, Integer b)
{
	if (a == 0 && b != 0)
		return b;

	if (b == 0 && a != 0)
		return a;

	if (a < b)
		std::swap(a, b);

	Integer res;

	Integer r = a % b;
	while (r != 0) {
		a = b;
		b = r;
		r = a % b;
	}
	res = b;

	return res;
}