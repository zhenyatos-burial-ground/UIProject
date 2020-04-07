#include "IVector.h"

IVector* IVector::createVector(size_t dim, double* pData, ILogger* pLogger)
{
	return nullptr;
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
