#pragma once
#include "Thomas.h"

class IslandObject : public thomas::object::GameObject
{
public:
	IslandObject() : thomas::object::GameObject("IslandObject")
	{
	}

	~IslandObject();

private:
	thomas::object::component::RenderComponent* m_renderer;
	thomas::object::component::SoundComponent* m_sound;
	thomas::object::component::RigidBodyComponent* m_rigidbody;
};