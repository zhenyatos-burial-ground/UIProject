#include <iostream>
#include "Integer.h"
#include "Rational.h"

using namespace std;

int main()
{
	Rational r = { 1, -2 };
	Rational s = { 1, 2 };
	Rational t = s;

	s += r;
	t -= r;
	return 0;
}
