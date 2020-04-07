#include "IVector.h"
#include "VectorImpl.cpp"

IVector* IVector::createVector(size_t dim, double* pData, ILogger* pLogger)
{
	if (pData == nullptr)
	{
		pLogger->log("In [createVector] pData is nullptr", RESULT_CODE::WRONG_ARGUMENT);
		return nullptr;
	}

	if (dim == 0)
	{
		pLogger->log("In [createVector] dim = 0", RESULT_CODE::WRONG_DIM);
		return nullptr;
	}

	double* data = new (std::nothrow)double[dim];
	if (data == nullptr)
	{
		pLogger->log("In [createVector] not enough memory for [double* data]", RESULT_CODE::OUT_OF_MEMORY);
		return nullptr;
	}

	for (int i = 0; i < dim; i++)
		data[i] = pData[i];

	IVector* res = new (std::nothrow)VectorImpl(dim, data);
	if (res == nullptr)
	{
		pLogger->log("In [createVector] not enough memory for [IVector* res]", RESULT_CODE::OUT_OF_MEMORY);
		return nullptr;
	}

	pLogger->createLogger(res);
	return res;
}

IVector* IVector::add(IVector const* pOperand1, IVector const* pOperand2, ILogger* pLogger)
{
	return nullptr;
}

IVector* IVector::sub(IVector const* pOperand1, IVector const* pOperand2, ILogger* pLogger)
{
	return nullptr;
}

IVector* IVector::mul(IVector const* pOperand1, double scaleParam, ILogger* pLogger)
{
	return nullptr;
}

double IVector::mul(IVector const* pOperand1, IVector const* pOperand2, ILogger* pLogger)
{
	return 0.0;
}

RESULT_CODE IVector::equals(IVector const* pOperand1, IVector const* pOperand2, NORM norm, double tolerance, bool* result, ILogger* pLogger)
{
	return RESULT_CODE();
}
