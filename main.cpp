#include <iostream>
#include "IVector.h"

using namespace std;

ostream& operator<<(ostream& stream, const IVector* vector)
{
	if (vector == nullptr)
		return stream;

	size_t dim = vector->getDim();
	stream << "[";
	for (int i = 0; i < dim - 1; i++)
		stream << vector->getCoord(i) << " ";
	stream << vector->getCoord(dim - 1);
	stream << "]";

	return stream;
}

int main()
{
	ILogger* logger = ILogger::createLogger(nullptr);

	double data1[3] = { 0, 1, -1 };
	IVector* vector1 = IVector::createVector(3, data1, logger);

	double data2[3] = { 1, 0, 2 };
	IVector* vector2 = IVector::createVector(3, data2, logger);

	IVector* testAdd = IVector::add(vector1, vector2, logger);
	std::cout << testAdd << "\n";

	double testMul = IVector::mul(vector1, vector2, logger);
	std::cout << testMul << "\n";

	IVector* testSub = IVector::sub(vector1, vector2, logger);
	std::cout << testSub << "\n";

	IVector* testScale = IVector::mul(vector1, 2.5, logger);
	std::cout << testScale << "\n";

	IVector* testLog = IVector::add(nullptr, vector2, logger);

	int x;
	std::cin >> x;

	delete vector1;
	delete vector2;
	delete testAdd;
	delete testSub;
	delete testScale;
	return 0;
}
