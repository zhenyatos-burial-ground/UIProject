#pragma once
#include "Test.h"
#include "ILogger.h"
#include "IVector.h"

class Vector0 : public Test
{
private:
	void test() override;
public:
	Vector0() : Test("Vector : Init") {}
};

class Vector1 : public Test
{
private:
	void test() override;
public:
	Vector1() : Test("Vector : Sum") {}
};

class Vector2 : public Test
{
private:
	void test() override;
public:
	Vector2() : Test("Vector : WrongSum") {}
};

class Vector3 : public Test
{
private:
	void test() override;
public:
	Vector3() : Test("Vector : Norm") {}
};

class Vector4 : public Test
{
private:
	void test() override;
public:
	Vector4() : Test("Vector : DotProduct") {}
};

class Vector5 : public Test
{
private:
	void test() override;
public:
	Vector5() : Test("Vector : GetSet") {}
};

class Vector6 : public Test
{
private:
	void test() override;
public:
	Vector6() : Test("Vector : Clone") {}
};