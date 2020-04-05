#include <iostream>
#include "Integer.h"
#include "Rational.h"
#include "Real.h"

using namespace std;

int main()
{
	Rational a1 = { 1, 3 };
	Rational a2 = { 1, 2 };
	
	Rational b1 = { -1, 2 };
	Rational b2 = { -1, 3 };

	Real a = { a1, a2 };
	Real b = { b1, b2 };

	Real test1 = a * b;
	Real test2 = a + b;

	return 0;
}
