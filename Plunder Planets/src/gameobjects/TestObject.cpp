#include "TestObject.h"

using namespace thomas::object;
bool TestObject::Start()
{
	m_transform->GetWorldMatrix();
	return true;
}

void TestObject::Update()
{
	//LOG("update");
}
