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
		radius = 0.5;
		m_transform->SetScale(radius);
		mass = 625.0;

	}

	void SetMass(float m)
	{
		mass = m;
		radius = m / 5000.0;
		radius *= 5;
		m_transform->SetScale(radius);
	}

	bool UpdateBoat(component::RigidBodyComponent* rb, bool moving) 
	{
		math::Vector3 deltaWater = ((WaterObject*)Find("WaterObject"))->GetCollisionAt(m_transform);

		float heightBelowWater = deltaWater.y - m_transform->GetPosition().y;
		
		if (heightBelowWater > 0)
		{
			
			float volume = (4.0 / 3.0)*math::PI*radius;
			float height = radius*2;
			float density = mass/volume;
			float volumeUnderWater = height - heightBelowWater;
			if (volumeUnderWater < 0)
				volumeUnderWater = height;
			volumeUnderWater = (4.0 / 3.0)*math::PI*volumeUnderWater/2;

			float waterDensity = 1.8 * density;
			btVector3 force = (volumeUnderWater*waterDensity)*-Physics::s_world->getGravity();
			math::Vector3 pos = math::Vector3::Transform(m_transform->m_localPosition, math::Matrix::CreateFromQuaternion(rb->m_gameObject->m_transform->GetRotation()));
			if (heightBelowWater < 0.2)
			{
				rb->setDamping(0.65, 0.65);
			}
			else
			{
				rb->setDamping(0.1, 0.1);
			}
			
			rb->applyImpulse(force*Time::GetDeltaTime(), *(btVector3*)&pos);
			if(!moving)
				rb->applyDamping(Time::GetDeltaTime());
			return true;
		}


		return false;

		
	}

	void Update()
	{

	}

private:
	float radius;
	float mass;
};