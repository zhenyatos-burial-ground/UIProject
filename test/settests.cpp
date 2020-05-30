#include "settests.h"
#include "IVector.h"

void Set1::test()
{
	ILogger* logger = ILogger::createLogger(nullptr);

	ISet* set;

	// CHECK: initialization is correct
	set = ISet::createSet(logger);
	_INEQ_(set, (ISet*)nullptr);

	// CHECK: dimension set to 0
	_EQ_(set->getDim(), (size_t)0);

	delete set;
}

void Set2::test()
{
	ILogger* logger = ILogger::createLogger(nullptr);

	double data1[3] = { 2, 0, 0 };
	IVector* vec1 = IVector::createVector(3, data1, logger);
	double data2[3] = { 0, 1, 0 };
	IVector* vec2 = IVector::createVector(3, data2, logger);
	double data3[3] = { 0.1, 1.1, 0.1 };
	IVector* vec3 = IVector::createVector(3, data3, logger);
	double data4[4] = { 0, 0, 0, 0 };
	IVector* vec4 = IVector::createVector(4, data4, logger);

	// CHECK: vec1 inserted correctly
	ISet* set = ISet::createSet(logger);
	RESULT_CODE code = set->insert(vec1, IVector::NORM::NORM_INF, 0.2);
	_EQ_(code, RESULT_CODE::SUCCESS);
	_EQ_(set->getSize(), (size_t)1);
	_EQ_(set->getDim(), (size_t)3);

	// CHECK: vec2 inserted correctly
	code = set->insert(vec2, IVector::NORM::NORM_INF, 0.2);
	_EQ_(code, RESULT_CODE::SUCCESS);
	_EQ_(set->getSize(), (size_t)2);

	// CHECK: vec3 doesn't inserted hence it's already in the set (as vec2) with tolerance 0.2
	code = set->insert(vec3, IVector::NORM::NORM_INF, 0.2);
	_EQ_(code, RESULT_CODE::SUCCESS);
	_EQ_(set->getSize(), (size_t)2);

	// CHECK: vec4 doesn't inserted hence it has dim = 4, but set dim = 3
	code = set->insert(vec4, IVector::NORM::NORM_INF, 0.2);
	_EQ_(code, RESULT_CODE::WRONG_DIM);
	_EQ_(set->getSize(), (size_t)2);

	// CHECK: attempt to insert nullptr
	code = set->insert(nullptr, IVector::NORM::NORM_INF, 0.2);
	_EQ_(code, RESULT_CODE::WRONG_ARGUMENT);

	// CHECK: attempt to insert with negative tolerance
	code = set->insert(vec1, IVector::NORM::NORM_INF, -1);
	_EQ_(code, RESULT_CODE::WRONG_ARGUMENT);

	delete vec1;
	delete vec2;
	delete vec3;
	delete vec4;
	delete set;
}	

void Set3::test()
{
	ILogger* logger = ILogger::createLogger(nullptr);
	
	double data1[4] = { 1, 0, 0, 0 };
	IVector* vec1 = IVector::createVector(4, data1, logger);
	double data2[4] = { 0, 1, 0, 0 };
	IVector* vec2 = IVector::createVector(4, data2, logger);
	double data3[4] = { 0, 0, 1, 0 };
	IVector* vec3 = IVector::createVector(4, data3, logger);
	double data4[3] = { 0, 0, 0 };
	IVector* vec4 = IVector::createVector(3, data4, logger);

	ISet* set1 = ISet::createSet(logger);
	ISet* set2 = ISet::createSet(logger);
	ISet* set3 = ISet::createSet(logger);

	set1->insert(vec1, IVector::NORM::NORM_1, 0.1);
	set1->insert(vec2, IVector::NORM::NORM_1, 0.1);
	set2->insert(vec2, IVector::NORM::NORM_1, 0.1);
	set2->insert(vec3, IVector::NORM::NORM_1, 0.1);
	set3->insert(vec4, IVector::NORM::NORM_1, 0.1);

	// CHECK: addition is correct
	ISet* res1 = ISet::add(set1, set2, IVector::NORM::NORM_1, 0.1, logger);
	_EQ_(res1->getSize(), (size_t)3);
	_EQ_(res1->getDim(), (size_t)4);

	// CHECK: attempt to add set1 with dim = 4 and set3 with dim = 3
	ISet* res2 = ISet::add(set1, set3, IVector::NORM::NORM_1, 0.1, logger);
	_EQ_(res2, (ISet*)nullptr);

	delete vec1;
	delete vec2;
	delete vec3;
	delete set1;
	delete set2;
	delete set3; 
	delete res1;
	delete res2;
}
