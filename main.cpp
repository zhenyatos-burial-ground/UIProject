#include <iostream>
#include "Integer.h"
#include "Rational.h"

using namespace std;

int main()
{
	Rational r = { 1, -2 };
	Rational t = Integer(1);
	Rational s = { 1, 0 };
	return 0;
}
