#include <iostream>
#include "Integer.h"
#include "Rational.h"

using namespace std;

int main()
{
	Rational r = { 2, 5 };
	Rational s = { 1, 2 };
	
	std::cout << (r < s);
	int x;
	std::cin >> x;
	return 0;
}
