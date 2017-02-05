#pragma once
#include "Thomas.h"

using namespace thomas;
using namespace graphics;

class TestEffect : public PostEffect
{
private:
	PostEffect* CreateInstance(std::string name, Shader* shader)
	{
		return new TestEffect(name, shader);
	}
public:
	TestEffect(std::string shader) : PostEffect(shader) {}
	TestEffect(std::string name, Shader* shader) : PostEffect(name, shader)
	{
	}
};