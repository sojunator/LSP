#pragma once
#include <Thomas.h>

using namespace thomas::object;
class TestObject : public thomas::object::GameObject
{
private:
public:
	TestObject() : GameObject("TestObject") {};

	bool Start();
	void Update();
private:
};