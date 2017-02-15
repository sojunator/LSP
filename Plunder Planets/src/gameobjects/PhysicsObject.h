#pragma once
#pragma once
#pragma once
#include "Thomas.h"

using namespace thomas;
using namespace object;
class PhysicsObject : public GameObject
{

private:

public:
	float forwardSpeed = 0;
	PhysicsObject() : GameObject("PhysicsTest")
	{

	}

	void Start()
	{
		m_transform->SetScale(10);
		m_transform->SetPosition(0, 100, 0);
		m_rigidBody = AddComponent<component::RigidBodyComponent>();
		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("cannonball");
		
	}

	void Update()
	{

	}

private:
	component::RenderComponent* m_renderer;
	component::RigidBodyComponent* m_rigidBody;
};