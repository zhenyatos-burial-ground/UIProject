#include "ISet.h"
#include "SetImpl.cpp"

ISet* ISet::createSet(ILogger* pLogger)
{
	ISet* res = new (std::nothrow) SetImpl();
	if (res == nullptr)
	{
		if (pLogger != nullptr)
			pLogger->log("In [ISet::createSet] not enough memory for [ISet* res]", RESULT_CODE::OUT_OF_MEMORY);
	}

	return res;
}