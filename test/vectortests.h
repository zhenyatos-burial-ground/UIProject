#pragma once
#include "Test.h"
#include "ILogger.h"
#include "IVector.h"

const std::string VEC_PREFIX = "Vector  ";

class Vector0 : public Test
{
private:
	void test() override;
public:
	Vector0() : Test(VEC_PREFIX + "Init") {}
};

class Vector1 : public Test
{
private:
	void test() override;
public:
	Vector1() : Test(VEC_PREFIX + "Sum") {}
};

class Vector2 : public Test
{
private:
	void test() override;
public:
	Vector2() : Test(VEC_PREFIX + "WrongSum") {}
};

class Vector3 : public Test
{
private:
	void test() override;
public:
	Vector3() : Test(VEC_PREFIX + "Norm") {}
};

class Vector4 : public Test
{
private:
	void test() override;
public:
	Vector4() : Test(VEC_PREFIX + "DotProduct") {}
};

class Vector5 : public Test
{
private:
	void test() override;
public:
	Vector5() : Test(VEC_PREFIX + "GetterSettter") {}
};

class Vector6 : public Test
{
private:
	void test() override;
public:
	Vector6() : Test(VEC_PREFIX + "Clone") {}
};