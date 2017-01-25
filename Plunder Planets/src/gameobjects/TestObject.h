#pragma once
#include <Thomas.h>
#include <string>

using namespace thomas;
using namespace object;
class TestObject : public thomas::object::GameObject
{
private:
public:

	TestObject() : GameObject("TestObject") {};

	bool Start();
	void Update();
private:
	thomas::graphics::Mesh* m_mesh;
	thomas::graphics::Shader* m_shader;
};