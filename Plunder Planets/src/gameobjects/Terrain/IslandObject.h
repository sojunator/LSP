#pragma once
#include "Thomas.h"

class IslandObject : public thomas::object::GameObject
{
public:
	IslandObject() : thomas::object::GameObject("IslandObject")
	{
		m_renderer = thomas::object::GameObject::AddComponent<thomas::object::component::RenderComponent>();
	}
	~IslandObject();

	void Start();
	void Update();
	void Destroy();
	void SetModel(int island);
	void SinkIsland();
	void PlaceRigidBody(float radius, thomas::math::Vector3 center);

private:
	thomas::object::component::RenderComponent* m_renderer;
	thomas::object::component::RigidBodyComponent* m_rigidBody;
	bool m_falling;
};