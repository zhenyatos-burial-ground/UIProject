#include "IVector.h"
#include "VectorImpl.cpp"

IVector* IVector::createVector(size_t dim, double* pData, ILogger* pLogger)
{
	if (pData == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector::createVector] pData is nullptr", RESULT_CODE::WRONG_ARGUMENT);
		return nullptr;
	}

	if (dim == 0)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector::createVector] dim = 0", RESULT_CODE::WRONG_DIM);
		return nullptr;
	}

	double* data = new (std::nothrow)double[dim];
	if (data == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector::createVector] not enough memory for [double* data]", RESULT_CODE::OUT_OF_MEMORY);
		return nullptr;
	}

	for (int i = 0; i < dim; i++)
		data[i] = pData[i];

	IVector* res = new (std::nothrow)VectorImpl(dim, data);
	if (res == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector::createVector] not enough memory for [IVector* res]", RESULT_CODE::OUT_OF_MEMORY);
		return nullptr;
	}

	if (pLogger != nullptr)
		pLogger->createLogger(res);
	return res;
}

IVector* IVector::add(IVector const* pOperand1, IVector const* pOperand2, ILogger* pLogger)
{
	if (pOperand1 == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector::add] pOperand1 is nullptr", RESULT_CODE::WRONG_ARGUMENT);
		return nullptr;
	}

	if (pOperand2 == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector::add] pOperand2 is nullptr", RESULT_CODE::WRONG_ARGUMENT);
		return nullptr;
	}

	if (pOperand1->getDim() != pOperand2->getDim())
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector::add] operands dimension is different", RESULT_CODE::OUT_OF_BOUNDS);
		return nullptr;
	}

	size_t dim = pOperand1->getDim();
	double* data = new (std::nothrow)double[dim];
	if (data == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector::add] not enough memory for [double* data]", RESULT_CODE::OUT_OF_MEMORY);
		return nullptr;
	}

	for (int i = 0; i < dim; i++)
		data[i] = pOperand1->getCoord(i) + pOperand2->getCoord(i);
	
	IVector* res = new (std::nothrow)VectorImpl(dim, data);
	if (res == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector::add] not enough memory for [IVector* res]", RESULT_CODE::OUT_OF_MEMORY);
		return nullptr;
	}

	if (pLogger != nullptr)
		pLogger->createLogger(res);
	return res;
}

IVector* IVector::sub(IVector const* pOperand1, IVector const* pOperand2, ILogger* pLogger)
{
	if (pOperand1 == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector::sub] pOperand1 is nullptr", RESULT_CODE::WRONG_ARGUMENT);
		return nullptr;
	}

	if (pOperand2 == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector::sub] pOperand2 is nullptr", RESULT_CODE::WRONG_ARGUMENT);
		return nullptr;
	}

	if (pOperand1->getDim() != pOperand2->getDim())
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector::sub] operands dimension is different", RESULT_CODE::OUT_OF_BOUNDS);
		return nullptr;
	}

	size_t dim = pOperand1->getDim();
	double* data = new (std::nothrow)double[dim];
	if (data == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector::sub] not enough memory for [double* data]", RESULT_CODE::OUT_OF_MEMORY);
		return nullptr;
	}

	for (int i = 0; i < dim; i++)
		data[i] = pOperand1->getCoord(i) - pOperand2->getCoord(i);

	IVector* res = new (std::nothrow)VectorImpl(dim, data);
	if (res == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector::sub] not enough memory for [IVector* res]", RESULT_CODE::OUT_OF_MEMORY);
		return nullptr;
	}

	if (pLogger != nullptr)
		pLogger->createLogger(res);
	return res;
}

IVector* IVector::mul(IVector const* pOperand1, double scaleParam, ILogger* pLogger)
{
	if (pOperand1 == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector* IVector::mul] pOperand1 is nullptr", RESULT_CODE::WRONG_ARGUMENT);
		return nullptr;
	}

	size_t dim = pOperand1->getDim();
	double* data = new (std::nothrow)double[dim];
	if (data == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector* IVector::mul] not enough memory for [double* data]", RESULT_CODE::OUT_OF_MEMORY);
		return nullptr;
	}

	for (int i = 0; i < dim; i++)
		data[i] = pOperand1->getCoord(i) * scaleParam;

	IVector* res = new (std::nothrow)VectorImpl(dim, data);
	if (res == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [IVector* IVector::mul] not enough memory for [IVector* res]", RESULT_CODE::OUT_OF_MEMORY);
		return nullptr;
	}

	if (pLogger != nullptr)
		pLogger->createLogger(res);
	return res;
}

double IVector::mul(IVector const* pOperand1, IVector const* pOperand2, ILogger* pLogger)
{
	return 0.0;
}

RESULT_CODE IVector::equals(IVector const* pOperand1, IVector const* pOperand2, NORM norm, double tolerance, bool* result, ILogger* pLogger)
{
	return RESULT_CODE();
}

IVector::~IVector()
{}