#include "vectortests.h"
#include "leaktest.h"
#include <iostream>

int main() 
{
	SetDbgMemHooks();
	TestDriver driver;
	driver.addTest(new Vector0());
	driver.addTest(new Vector1());
	driver.addTest(new Vector2());
	driver.addTest(new Vector3());
	driver.addTest(new Vector4());
	driver.addTest(new Vector5());
	driver.addTest(new Vector6());

	driver.runTests(std::cout);
	std::cin.get();
	return 0;
}