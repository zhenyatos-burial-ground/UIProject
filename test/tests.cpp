#include "vectortests.h"
#include <iostream>

int main() 
{
	TestDriver driver;
	driver.addTest(new Vector1());
	driver.addTest(new Vector2());
	driver.addTest(new Vector3());
	driver.addTest(new Vector4());


	driver.runTests(std::cout);
	std::cin.get();
	return 0;
}