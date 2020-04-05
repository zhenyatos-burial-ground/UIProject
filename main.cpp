#include <iostream>
#include "Integer.h"

using namespace std;

int main()
{
	Integer a, b;
	while (true) 
	{
		std::cin >> a >> b;
		std::cout << GCD(a, b) << "\n";
	}
	return 0;
}
