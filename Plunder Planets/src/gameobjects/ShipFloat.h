#pragma once

#include "Thomas.h"

using namespace thomas;
using namespace object;
class ShipFloat : public GameObject
{

private:

public:
	ShipFloat() : GameObject("ShipFloat")
	{

	}

	void Start()
	{
		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("cannonball");
		m_transform->SetScale(5);

	}

	bool UpdateBoat(component::RigidBodyComponent* rb) 
	{
		math::Vector3 deltaWater = ((WaterObject*)Find("WaterObject"))->GetCollisionAt(m_transform);

		if (deltaWater.y > 0)
		{
			float density = 10;
			float volumeUnderWater = 2 - deltaWater.y;
			if (volumeUnderWater < 0)
				volumeUnderWater = 2;
			volumeUnderWater = volumeUnderWater * 2;

			float waterDensity = 2 * density;
			btVector3 force = (volumeUnderWater*waterDensity)*-Physics::s_world->getGravity();
			rb->applyImpulse(force*Time::GetDeltaTime(), *(btVector3*)&m_transform->GetPosition());
			return true;
		}
		return false;

		
	}

	void Update()
	{

	}

private:
	component::RenderComponent* m_renderer;
};