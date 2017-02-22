#pragma once
#pragma once
#include "Thomas.h"
#include "WaterObject.h"
using namespace thomas;
using namespace object;
class Projectile : public GameObject
{

private:
	void CalculateDrag()
	{
		btScalar temp_vel = m_rigidbody->getLinearVelocity().length(); // ehm, borde vara length2
		btVector3 temp = constant * temp_vel * temp_vel * m_rigidbody->getLinearVelocity().normalized();
		m_force = temp;
	}

	float MonteCarloAngle()
	{
		float randNum = rand() % 999 + 1;
		randNum /= 1000.0f;
		if (randNum < 0.5f)
			return 3.0f * (sqrtf(2.0f * randNum) - 1);
		else
			return 3.0f * (1 - sqrtf(2 - 2 * randNum));
	}

public:
	float forwardSpeed = 0;
	Projectile() : GameObject("Projectile")
	{
		m_angleX = MonteCarloAngle();
		m_angleY = MonteCarloAngle();
	}

	void Start()
	{
		m_mass = 2.5f;
		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("cannonball");
		m_splashSound = AddComponent<component::SoundComponent>();
		m_rigidbody = AddComponent<component::RigidBodyComponent>();
		constant = -0.5 * m_Cd * 1.21f * m_radius * m_radius * math::PI;
		m_rigidbody->setCollisionShape(new btSphereShape(0.35f));
		m_rigidbody->SetMass(m_mass); 
		m_rigidbody->setLinearVelocity(*(btVector3*)&m_transform->Forward()*(300.0 * cosf(math::DegreesToradians(m_angleY))) + *(btVector3*)&m_transform->Up() * (100.0 * sinf(math::DegreesToradians(m_angleY))) + *(btVector3*)&m_transform->Right() * (20.0 * sinf(math::DegreesToradians(m_angleY))));

		m_water = (WaterObject*)Find("WaterObject");
		if (!m_water)
		{
			LOG("Errorroror no wadder found");
			m_hitWater = true;
		}
		else
		{
			m_hitWater = false;
		}

	}

	void Update()
	{
		CalculateDrag();
		
		m_rigidbody->applyCentralForce(m_force);
		if (!m_hitWater)
		{
			math::Vector3  temp = m_water->GetCollisionAt(m_transform);
			if (temp.y - 0.0001f < 0.0f)
			{
				constant = -0.5 * m_Cd * 1000.f * m_radius * m_radius * math::PI;
				m_hitWater = true;
			}
		}

		if (m_transform->GetPosition().y < -100.0f)
		{
			Destroy(this);
		}
	}

private:
	btVector3 m_force;

	float m_angleX;
	float m_angleY;
	float m_mass = 5.0f;
	btScalar m_radius = 0.05f;
	btScalar m_Cd = 0.47f;
	btScalar constant;
	component::SoundComponent* m_splashSound;
	component::RenderComponent* m_renderer;
	component::RigidBodyComponent* m_rigidbody;
	std::string m_SFXs[3] = { "fSplash1", "fSplash2", "fSplash3" };
	WaterObject* m_water;
	bool m_hitWater;
};