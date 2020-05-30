#include "ISet.h"
#include "SetImpl.cpp"
#include <string>

RESULT_CODE validateData(ISet const* pOperand1, ISet const* pOperand2, double tolerance, std::string fun, std::string& msg)
{
	if (pOperand1 == nullptr)
	{
		msg = "In " + fun + " pOperand1 is nullptr";
		return RESULT_CODE::WRONG_ARGUMENT;
	}

	if (pOperand2 == nullptr)
	{
		msg = "In " + fun + " pOperand2 is nullptr";
		return RESULT_CODE::WRONG_ARGUMENT;
	}

	if (pOperand1->getDim() == 0)
	{
		msg = "In " + fun + " pOperand1 dim = 0";
		return RESULT_CODE::WRONG_DIM;
	}

	if (pOperand2->getDim() == 0)
	{
		msg = "In " + fun + " pOperand2 dim = 0";
		return RESULT_CODE::WRONG_DIM;
	}

	if (pOperand1->getDim() != pOperand2->getDim())
	{
		msg = "In " + fun + " pOperand1 dim is not equal pOperand2 dim";
		return RESULT_CODE::WRONG_DIM;
	}

	return RESULT_CODE::SUCCESS;
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
	std::string msg;
	RESULT_CODE code = validateData(pOperand1, pOperand2, tolerance, "[ISet::add]", msg);
	if (code != RESULT_CODE::SUCCESS)
		if (pLogger != nullptr)
		{
			pLogger->log(msg.c_str(), code);
			return nullptr;
		}

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
	std::string msg;
	RESULT_CODE code = validateData(pOperand1, pOperand2, tolerance, "[ISet::add]", msg);
	if (code != RESULT_CODE::SUCCESS)
		if (pLogger != nullptr)
		{
			pLogger->log(msg.c_str(), code);
			return nullptr;
		}

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

ISet::~ISet()
{}
