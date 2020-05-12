#include "vectortests.h"

void Vector1::test()
{
	ILogger* logger = ILogger::createLogger(nullptr);

	double data1[3] = { 0, 1, -4 };
	IVector* vector1 = IVector::createVector(3, data1, logger);

	double data2[3] = { 1, 5, 2 };
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
	IVector* vector1 = IVector::createVector(2, data1, logger);

	double data2[3] = { 0, 0, 1 };
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
	IVector* vector1 = IVector::createVector(3, data1, logger);

	double data2[3] = { 2, 0, 2.5 };
	IVector* vector2 = IVector::createVector(3, data2, logger);

	_EQ_(IVector::mul(vector1, vector2, logger), -0.5);

	delete vector1;
	delete vector2;
	logger->destroyLogger(nullptr);
}