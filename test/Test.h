#pragma once
#include <string>
#include <list>
#include <ostream>

class Test
{
private:
	bool res;
	int eqNo;
	int ineqNo;
	std::string msg;
	virtual void test() = 0;

public:
	const std::string name;
	Test(std::string name) : name(name) { eqNo = 0; ineqNo = 0; }
	bool run() { res = true; test(); return res; }
	virtual ~Test() {}

	template<typename T>
	void _EQ_(T a, T b) 
	{ 
		if (!res)
			return;
		eqNo++;
		res &= (a == b); 
		if (!res)
			msg = "EQ [" + std::to_string(eqNo) + "] failed";
	}

	template<typename T>
	void _INEQ_(T a, T b) 
	{ 
		if (!res)
			return;
		ineqNo++;
		res &= (a != b); 
		if (!res)
			msg = "INEQ [" + std::to_string(ineqNo) + "] failed";
	}

	std::string getFailMsg() { return msg; }
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
				out << "[FAILED] " << test->name << " [CAUSE] " << test->getFailMsg() << "\n";
		}
	}

	void addTest(Test* test)
	{
		tests.push_back(test);
	}

	~TestDriver() { tests.remove_if(deleteTest); }
};