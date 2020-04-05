#include <iostream>
#include "Integer.h"
#include "Rational.h"

using namespace std;

int main()
{
	Rational r = { 1, -2 };
	Rational s = { 1, 2 };
	Rational t = s;

	t *= r;
	r /= s;
	r /= {0, 1};
	return 0;
}
