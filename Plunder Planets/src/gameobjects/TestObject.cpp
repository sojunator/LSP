#include "TestObject.h"

using namespace thomas::object;
bool TestObject::Start()
{
	return true;
}

void TestObject::Update()
{
	LOG("update");
}
