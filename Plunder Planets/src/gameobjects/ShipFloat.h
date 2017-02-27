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
		m_radius = 0.5;
		m_transform->SetScale(m_radius);
		m_mass = 625.0;

	}

	void SetMass(float m)
	{
		m_mass = m;
		m_radius = m / 5000.0;
		m_radius *= 5;
		m_transform->SetScale(m_radius);
	}

	float UpdateBoat(component::RigidBodyComponent* rb, bool moving) 
	{

		float deltaWater = ((WaterObject*)Find("WaterObject"))->GetWaterHeightAtColliderIndex(m_collisionIndex);

		float heightBelowWater = deltaWater - m_transform->GetPosition().y;
		
		if (heightBelowWater > 0)
		{
			
			float volume = (4.0 / 3.0)*math::PI*m_radius;
			float height = m_radius*2;
			float density = m_mass/volume;
			float volumeUnderWater = height - heightBelowWater;
			if (volumeUnderWater < 0)
				volumeUnderWater = height;
			volumeUnderWater = (4.0 / 3.0)*math::PI*volumeUnderWater/2;
			
			float waterDensity = 3.0 * density;
			btVector3 force = (volumeUnderWater*waterDensity)*-rb->getGravity();
			math::Vector3 pos = math::Vector3::Transform(m_transform->m_localPosition, math::Matrix::CreateFromQuaternion(rb->m_gameObject->m_transform->GetRotation()));
			if (heightBelowWater < 0.3)
			{
				rb->setDamping(0.9, 0.9);
			}
			else if(heightBelowWater < 1.5)
			{
				rb->setDamping(0.7, 0.7);
			}
			else if (heightBelowWater < 2.0)
			{
				rb->setDamping(0.5, 0.5);
			}
			else
			{
				rb->setDamping(0.3, 0.3);
			}
			
			rb->applyImpulse(force*Time::GetDeltaTime(), *(btVector3*)&pos);
			if(!moving)
				rb->applyDamping(Time::GetDeltaTime());
		}
		


		return deltaWater;

		
	}

	void Update()
	{
		m_collisionIndex = ((WaterObject*)Find("WaterObject"))->RegisterColliderAt(m_transform->GetPosition());
	}

private:
	int m_collisionIndex;
	float m_radius;
	float m_mass;
};