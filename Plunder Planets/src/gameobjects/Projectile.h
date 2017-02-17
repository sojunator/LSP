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
		force = 0.5 * Cd * 1.21f * radius * radius * math::PI * speed * speed;
	}

	void CalculateAccel()
	{
		accel = force / mass;
	}

	// https://ih0.redbubble.net/image.104978724.0105/raf,750x1000,075,t,ff4c00:b001c7b98d.u2.jpg
	void UpdateSpeeeeeeed()
	{
		speed += accel * Time::GetDeltaTime();
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
		angleX = MonteCarloAngle();
		angleY = MonteCarloAngle() + 10;
	}

	void Start()
	{
		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("cannonball");
		m_splashSound = AddComponent<component::SoundComponent>();
		speed = 180.0f;
		mass = 2.5f;
	}

	void Update()
	{
		CalculateForce();
		CalculateAccel();
		UpdateSpeeeeeeed();
		float dt = Time::GetDeltaTime();
		m_downSpeed += 9.82*dt;

		m_transform->Translate(m_transform->Forward()*dt*speed);
		m_transform->Translate(m_transform->Right()*dt*forwardSpeed);
		m_transform->Translate(m_transform->Up()*dt*angleY);
		m_transform->Translate(math::Vector3::Down*m_downSpeed*dt);


		if (m_transform->GetPosition().y < 0.0)
		{
			m_splashSound->PlayOneShot(m_SFXs[rand() % 3], 0.5);
			Destroy(this);
		}
			
	}

private:
	float force;
	float angleX;
	float angleY;
	float mass;
	float radius;
	float Cd = 0.35;
	float accel;
	float speed;
	float m_downSpeed;
	component::SoundComponent* m_splashSound;
	component::RenderComponent* m_renderer;
	std::string m_SFXs[3] = { "fSplash1", "fSplash2", "fSplash3" };
};