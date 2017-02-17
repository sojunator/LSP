#pragma once
#pragma once
#include "Thomas.h"

using namespace thomas;
using namespace object;
class Projectile : public GameObject
{

private:
	void CalculateForce()
	{
		m_force = -0.5 * m_Cd * 1.21f * m_radius * m_radius * math::PI * m_speed * m_speed;
	}

	void CalculateAccel()
	{
		m_accel = m_force / m_mass;
	}

	// https://ih0.redbubble.net/image.104978724.0105/raf,750x1000,075,t,ff4c00:b001c7b98d.u2.jpg
	void UpdateSpeeeeeeed()
	{
		m_speed += m_accel * Time::GetDeltaTime();
		m_downSpeed += 9.82*Time::GetDeltaTime() * m_mass;
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
		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("cannonball");
		m_splashSound = AddComponent<component::SoundComponent>();
		m_rigidbody = AddComponent<component::RigidBodyComponent>();

		m_rigidbody->SetMass(m_mass);


		m_speed = 300.0f;
		m_mass = 2.5f;
	}

	void Update()
	{
		CalculateForce();
		CalculateAccel();
		UpdateSpeeeeeeed();
		float dt = Time::GetDeltaTime();


		m_transform->Translate(m_transform->Forward()*dt*m_speed);
		m_transform->Translate(m_transform->Right()*dt*forwardSpeed);
		m_transform->Translate(m_transform->Up()*dt*m_angleY);
		m_transform->Translate(math::Vector3::Down*m_downSpeed*dt);


		if (m_transform->GetPosition().y < 0.0)
		{
			m_splashSound->PlayOneShot(m_SFXs[rand() % 3], 0.5);
			Destroy(this);
		}
			
	}

private:
	float m_force;
	float m_angleX;
	float m_angleY;
	float m_mass = 5.0f;
	float m_radius = 0.05f;
	float m_Cd = 0.47f;
	float m_accel;
	float m_speed;
	float m_downSpeed;
	component::SoundComponent* m_splashSound;
	component::RenderComponent* m_renderer;
	component::RigidBodyComponent* m_rigidbody;
	std::string m_SFXs[3] = { "fSplash1", "fSplash2", "fSplash3" };
};