#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define SetDbgMemHooks()\
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_ALLOC_MEM_DF \
| _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else
#define SetDbgMemHooks() ((VOID)0)
#endif