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
		radius = 1.0;
		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("cannonball");
		m_transform->SetScale(radius);
		mass = 500.0;

	}

	bool UpdateBoat(component::RigidBodyComponent* rb) 
	{
		math::Vector3 deltaWater = ((WaterObject*)Find("WaterObject"))->GetCollisionAt(m_transform);


		if (Input::GetKey(Input::Keys::Left))
		{
			radius -= 1 * Time::GetDeltaTime();
			m_transform->SetScale(radius);
		}
		if (Input::GetKey(Input::Keys::Right))
		{
			radius += 1 * Time::GetDeltaTime();
			m_transform->SetScale(radius);
		}
		if (Input::GetKey(Input::Keys::Up))
		{
			mass += 100.0*Time::GetDeltaTime();
		}
		if (Input::GetKey(Input::Keys::Down))
		{
			mass -= 100.0*Time::GetDeltaTime();
		}
		if (deltaWater.y > 0)
		{
			
			float volume = (4.0 / 3.0)*math::PI*radius;
			float height = radius*2;
			float density = mass/volume;
			float volumeUnderWater = height - deltaWater.y;
			if (volumeUnderWater < 0)
				volumeUnderWater = height;
			volumeUnderWater = (4.0 / 3.0)*math::PI*volumeUnderWater/2;

			float waterDensity = 2*density;
			btVector3 force = (volumeUnderWater*waterDensity)*-Physics::s_world->getGravity();
			LOG(force.getY());
			math::Vector3 pos = math::Vector3::Transform(m_transform->m_localPosition, math::Matrix::CreateFromQuaternion(rb->m_gameObject->m_transform->GetRotation()));
			rb->applyImpulse(force*Time::GetDeltaTime(), *(btVector3*)&pos);
			
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
	component::RenderComponent* m_renderer;
};