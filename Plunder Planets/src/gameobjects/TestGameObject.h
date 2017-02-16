#pragma once
#pragma once
#include "Thomas.h"

using namespace thomas;
using namespace object;
class TestGameObject : public GameObject
{

private:

public:

	TestGameObject() : GameObject("TestGameObject")
	{

	}

	void Start()
	{
		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("sponza");
	}

	void Update()
	{
	
	}

private:
	
	component::RenderComponent* m_renderer;
};