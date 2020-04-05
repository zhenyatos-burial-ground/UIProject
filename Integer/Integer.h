#include "Error.h"

class Integer 
{
private:
	int i;

public:
	explicit Integer(int i = 0);
	Integer(const Integer& other);
	Integer& operator= (const Integer& other);
	Integer& operator= (int value);
	~Integer();

	Integer& operator+=(const Integer& other);
	Integer& operator-=(const Integer& other);
	Integer& operator*=(const Integer& other);
	Integer& operator/=(const Integer& other);
	Integer& operator%=(const Integer& other);

	bool operator==(const Integer& other) const;
	bool operator!=(const Integer& other) const;
	bool operator>(const Integer& other) const;
	bool operator>=(const Integer& other) const;
	bool operator<(const Integer& other) const;
	bool operator<=(const Integer& other) const;

	explicit operator int() const;
	friend std::ostream& operator<<(std::ostream& stream, const Integer& integer);
	friend std::istream& operator>>(std::istream& stream, Integer& integer);
};

Integer operator+(Integer a, const Integer& b);
Integer operator-(Integer a, const Integer& b);
Integer operator*(Integer a, const Integer& b);
Integer operator/(Integer a, const Integer& b);
Integer operator%(Integer a, const Integer& b);