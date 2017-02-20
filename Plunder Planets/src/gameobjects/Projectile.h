#pragma once
#pragma once
#include "Thomas.h"

using namespace thomas;
using namespace object;
class Projectile : public GameObject
{

private:
	void CalculateDrag()
	{
		m_force =  -constant * 180.0f * 180.0f * *(btVector3*)&m_transform->Forward();
	}

	void CalculateAccel()
	{

	}

	// https://ih0.redbubble.net/image.104978724.0105/raf,750x1000,075,t,ff4c00:b001c7b98d.u2.jpg
	void UpdateSpeeeeeeed()
	{

	}


	float MonteCarloAngle()
	{
		float randNum = rand() % 999 + 1;
		randNum /= 1000.0f;
		if (randNum < 0.5f)
			return 15 * (sqrtf(2.0f * randNum) - 1);
		else
			return 10 * (1 - sqrtf(2 - 2 * randNum));
	}

public:
	float forwardSpeed = 0;
	Projectile() : GameObject("Projectile")
	{
		m_angleX = MonteCarloAngle();
		m_angleY = MonteCarloAngle() + 10;
	}

	void Start()
	{
		m_speed = 300.0f;
		m_mass = 2.5f;
		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("cannonball");
		m_splashSound = AddComponent<component::SoundComponent>();
		m_rigidbody = AddComponent<component::RigidBodyComponent>();
		constant = -0.5 * m_Cd * 1.21f * m_radius * m_radius * math::PI;
		m_rigidbody->setCollisionShape(new btSphereShape(0.35f));
		m_rigidbody->SetMass(m_mass); 
		m_rigidbody->setLinearVelocity(*(btVector3*)&m_transform->Forward()*(180.0 * cosf(math::DegreesToradians(m_angleY))) + *(btVector3*)&m_transform->Up() * (180.0 * sinf(math::DegreesToradians(m_angleY))));

		
	}

	void Update()
	{
		//CalculateDrag();
		
		//m_rigidbody->applyForce(m_force, btVector3(*(btVector3*)&m_transform->GetPosition()));

		if (m_transform->GetPosition().y < -10.0)
		{
			m_splashSound->PlayOneShot(m_SFXs[rand() % 3], 0.5);
			Destroy(this);
		}
			
	}

private:
	btVector3 m_force;

	float m_angleX;
	float m_angleY;
	float m_mass = 5.0f;
	float m_radius = 0.05f;
	float m_Cd = 0.47f;
	float m_accel;
	float m_speed;
	float m_downSpeed;
	float constant;
	component::SoundComponent* m_splashSound;
	component::RenderComponent* m_renderer;
	component::RigidBodyComponent* m_rigidbody;
	std::string m_SFXs[3] = { "fSplash1", "fSplash2", "fSplash3" };
};