#pragma once
#include <string>
#include <list>
#include <ostream>

class Test
{
private:
	bool res;
	virtual void test() = 0;

public:
	const std::string name;
	Test(std::string name) : name(name) { }
	bool run() { res = true; test(); return res; }
	virtual ~Test() {}

	template<typename T>
	void _EQ_(T a, T b) { res &= (a == b); }

	template<typename T>
	void _INEQ_(T a, T b) { res &= (a != b); }
};

class TestDriver
{
private:
	std::list<Test*> tests;
	static bool deleteTest(Test* test) { delete test; return true; }

public:
	void runTests(std::ostream& out)
	{
		for (Test* test : tests)
		{
			if (test->run())
				out << "[PASSED] " << test->name << "\n";
			else
				out << "[FAILED] " << test->name << "\n";
		}
	}

	void addTest(Test* test)
	{
		tests.push_back(test);
	}

	~TestDriver() { tests.remove_if(deleteTest); }
};