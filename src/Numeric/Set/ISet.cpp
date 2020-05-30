#include "ISet.h"
#include "SetImpl.cpp"
#include <string>

RESULT_CODE validateData(ISet const* pOperand1, ISet const* pOperand2, double tolerance, std::string fun, ILogger* logger)
{
	RESULT_CODE code = RESULT_CODE::SUCCESS;
	std::string msg;

	if (pOperand1 == nullptr)
	{
		msg = "In " + fun + " pOperand1 is nullptr";
		code = RESULT_CODE::WRONG_ARGUMENT;
	}
	else if (pOperand2 == nullptr)
	{
		msg = "In " + fun + " pOperand2 is nullptr";
		code = RESULT_CODE::WRONG_ARGUMENT;
	}
	else if (pOperand1->getDim() == 0)
	{
		msg = "In " + fun + " pOperand1 dim = 0";
		code = RESULT_CODE::WRONG_DIM;
	}
	else if (pOperand2->getDim() == 0)
	{
		msg = "In " + fun + " pOperand2 dim = 0";
		code = RESULT_CODE::WRONG_DIM;
	}
	else if (pOperand1->getDim() != pOperand2->getDim())
	{
		msg = "In " + fun + " pOperand1 dim is not equal pOperand2 dim";
		code = RESULT_CODE::WRONG_DIM;
	}

	if (logger != nullptr)
		logger->log(msg.c_str(), code);
	return code;
}

ISet* ISet::createSet(ILogger* pLogger)
{
	ISet* res = new (std::nothrow) SetImpl();
	if (res == nullptr)
		if (pLogger != nullptr)
			pLogger->log("In [ISet::createSet] not enough memory for [ISet* res]", RESULT_CODE::OUT_OF_MEMORY);

	return res;
}

ISet* ISet::add(ISet const* pOperand1, ISet const* pOperand2, IVector::NORM norm, double tolerance, ILogger* pLogger)
{
	RESULT_CODE code = validateData(pOperand1, pOperand2, tolerance, "[ISet::add]", pLogger);
	if (code != RESULT_CODE::SUCCESS)
		return nullptr;

	ISet* res = pOperand1->clone();
	if (res == nullptr)
		if (pLogger != nullptr)
			pLogger->log("In [ISet:add] not enough memory for [ISet* res]", RESULT_CODE::OUT_OF_MEMORY);

	size_t size = pOperand2->getSize();
	for (size_t indx = 0; indx < size; indx++)
	{
		IVector* vec = nullptr;
		code = pOperand2->get(vec, indx);
		if (code == RESULT_CODE::SUCCESS)
			res->insert(vec, norm, tolerance);
		delete vec;
	}

	return res;
}

ISet* ISet::intersect(ISet const* pOperand1, ISet const* pOperand2, IVector::NORM norm, double tolerance, ILogger* pLogger)
{
	RESULT_CODE code = validateData(pOperand1, pOperand2, tolerance, "[ISet::intersect]", pLogger);
	if (code != RESULT_CODE::SUCCESS)
		return nullptr;

	ISet* res = ISet::createSet(pLogger);
	if (res == nullptr)
		if (pLogger != nullptr)
			pLogger->log("In [ISet:intersect] not enough memory for [ISet* res]", RESULT_CODE::OUT_OF_MEMORY);

	size_t size = pOperand1->getSize();
	for (size_t indx = 0; indx < size; indx++)
	{
		IVector* vec1 = nullptr;
		code = pOperand1->get(vec1, indx);
		if (code == RESULT_CODE::SUCCESS)
		{
			IVector* vec2 = nullptr;
			code = pOperand2->get(vec2, vec1, norm, tolerance);
			if (code == RESULT_CODE::SUCCESS && vec2 != nullptr)
				res->insert(vec2, norm, tolerance);
			delete vec2;
		}
		delete vec1;
	}

	return res;
}

ISet* ISet::sub(ISet const* pOperand1, ISet const* pOperand2, IVector::NORM norm, double tolerance, ILogger* pLogger)
{
	RESULT_CODE code = validateData(pOperand1, pOperand2, tolerance, "[ISet::sub]", pLogger);
	if (code != RESULT_CODE::SUCCESS)
		return nullptr;
		

	ISet* res = pOperand1->clone();
	if (res == nullptr)
		if (pLogger != nullptr)
			pLogger->log("In [ISet:sub] not enough memory for [ISet* res]", RESULT_CODE::OUT_OF_MEMORY);

	size_t size = pOperand2->getSize();
	for (size_t indx = 0; indx < size; indx++)
	{
		IVector* vec = nullptr;
		code = pOperand2->get(vec, indx);
		if (code == RESULT_CODE::SUCCESS)
			res->erase(vec, norm, tolerance);
		delete vec;
	}

	return res;
}

ISet* ISet::symSub(ISet const* pOperand1, ISet const* pOperand2, IVector::NORM norm, double tolerance, ILogger* pLogger)
{
	RESULT_CODE code = validateData(pOperand1, pOperand2, tolerance, "[ISet::symSub]", pLogger);
	if (code != RESULT_CODE::SUCCESS)
		return nullptr;

	ISet* add = ISet::add(pOperand1, pOperand2, norm, tolerance, pLogger);
	if (add == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [ISet::symSub] not enough memory for [ISet* add]", RESULT_CODE::OUT_OF_MEMORY);
		return nullptr;
	}

	ISet* intersect = ISet::intersect(pOperand1, pOperand2, norm, tolerance, pLogger);
	if (intersect == nullptr)
	{
		delete add;
		if (pLogger != nullptr)
			pLogger->log("In [ISet::symSub] not enough memory for [ISet* add]", RESULT_CODE::OUT_OF_MEMORY);
		return nullptr;
	}

	ISet* res = ISet::sub(add, intersect, norm, tolerance, pLogger);
	if (res == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [ISet::symSub] not enough memory for [ISet* res]", RESULT_CODE::OUT_OF_MEMORY);
	}

	delete add;
	delete intersect;

	return res;
}

ISet::~ISet()
{}
