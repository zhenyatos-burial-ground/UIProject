#include "vectortests.h"


void Vector0::test()
{
	ILogger* logger = ILogger::createLogger(nullptr);

	double data[3] = { 0, 0, 0 };
	IVector* vector;

	// CHECK: wrong dimension
	vector = IVector::createVector(-2, data, logger);
	_EQ_(vector, (IVector*)nullptr);
	if (vector != nullptr)
		delete vector;

	// CHECK: null data
	vector = IVector::createVector(3, nullptr, logger);
	_EQ_(vector, (IVector*)nullptr);
	if (vector != nullptr)
		delete vector;

	// CHECK: initialized, dim set correctly
	vector = IVector::createVector(3, data, logger);
	_INEQ_(vector, (IVector*)nullptr);
	_EQ_(vector->getDim(), (size_t)3);
	

	delete vector;
	logger->destroyLogger(nullptr);
}


void Vector1::test()
{
	ILogger* logger = ILogger::createLogger(nullptr);
	double data1[3] = { 0, 1, -4 };
	double data2[3] = { 1, 5, 2 };

	// CHECK: correct addition
	IVector* vector1 = IVector::createVector(3, data1, logger);
	IVector* vector2 = IVector::createVector(3, data2, logger);
	IVector* result = IVector::add(vector1, vector2, logger);
	_EQ_(result->getCoord(0), 1.0);
	_EQ_(result->getCoord(1), 6.0);
	_EQ_(result->getCoord(2), -2.0);

	delete vector1;
	delete vector2;
	delete result;
	logger->destroyLogger(nullptr);
}

void Vector2::test()
{
	ILogger* logger = ILogger::createLogger(nullptr);
	double data1[2] = { 0, 1 };
	double data2[3] = { 0, 0, 1 };

	// CHECK: error in addition (dim 2 + dim 3)
	IVector* vector1 = IVector::createVector(2, data1, logger);
	IVector* vector2 = IVector::createVector(3, data2, logger);
	IVector* result = IVector::add(vector1, vector2, logger);
	_EQ_(result, (IVector*)nullptr);

	delete vector1;
	delete vector2;
	logger->destroyLogger(nullptr);
}

void Vector3::test()
{
	ILogger* logger = ILogger::createLogger(nullptr);
	double data[3] = { 1, 1, -1 };

	// CHECK: norm calculation
	IVector* vector = IVector::createVector(3, data, logger);
	_EQ_(vector->norm(IVector::NORM::NORM_1), 3.0);
	_EQ_(vector->norm(IVector::NORM::NORM_2), sqrt(3));
	_EQ_(vector->norm(IVector::NORM::NORM_INF), 1.0);

	delete vector;
	logger->destroyLogger(nullptr);
}

void Vector4::test()
{
	ILogger* logger = ILogger::createLogger(nullptr);
	double data1[3] = { 1, 1, -1 };
	double data2[3] = { 2, 0, 2.5 };

	// CHECK: dot product calculation
	IVector* vector1 = IVector::createVector(3, data1, logger);
	IVector* vector2 = IVector::createVector(3, data2, logger);
	_EQ_(IVector::mul(vector1, vector2, logger), -0.5);

	delete vector1;
	delete vector2;
	logger->destroyLogger(nullptr);
}

void Vector5::test()
{
	ILogger* logger = ILogger::createLogger(nullptr);
	double data[3] = { 0, 1, 20 };

	// CHECK: correct get
	IVector* vector = IVector::createVector(3, data, logger);
	_EQ_(vector->getCoord(0), 0.0);
	_EQ_(vector->getCoord(1), 1.0);
	_EQ_(vector->getCoord(2), 20.0);

	// CHECK: correct set
	_EQ_(vector->setCoord(0, 10.0), RESULT_CODE::SUCCESS);
	_EQ_(vector->getCoord(0), 10.0);							

	delete vector;
	logger->destroyLogger(nullptr);
}

void Vector6::test()
{
	ILogger* logger = ILogger::createLogger(nullptr);
	double data[4] = { 0, 3.5, -100, 8.1 };
	IVector* vector = IVector::createVector(4, data, logger);

	// CHECK: correct clone
	IVector* cloned = vector->clone();
	_EQ_(cloned->getDim(), (size_t)4);
	
	_EQ_(cloned->getCoord(0), vector->getCoord(0));
	_EQ_(cloned->getCoord(1), vector->getCoord(1));
	_EQ_(cloned->getCoord(2), vector->getCoord(2));
	_EQ_(cloned->getCoord(3), vector->getCoord(3));

	delete vector;
	delete cloned;
	logger->destroyLogger(nullptr);
}
