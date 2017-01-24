#pragma once
#include <Thomas.h>
#include <string>

using namespace thomas::object;
class TestObject : public thomas::object::GameObject
{
private:
	thomas::graphics::Mesh* m_mesh;
	thomas::graphics::Shader* m_shader;
public:
	TestObject() : GameObject("TestObject") {};

	bool Start();
	void Update();
private:
};