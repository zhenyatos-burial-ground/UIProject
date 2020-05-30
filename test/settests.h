#pragma once
#include "Test.h"
#include "ILogger.h"
#include "ISet.h"

const std::string SET_PREFIX = "Set     ";

class Set1 : public Test
{
private:
	void test() override;
public:
	Set1() : Test(SET_PREFIX + "Init") {}
};

class Set2 : public Test
{
private:
	void test() override;
public:
	Set2() : Test(SET_PREFIX + "Insert") {}
};

class Set3 : public Test
{
private:
	void test() override;
public:
	Set3() : Test(SET_PREFIX + "Add") {}
};