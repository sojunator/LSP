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
		force = 0.5 * Cd * 1.21f * radius * radius * math::PI * speed * speed * currentDirection;
	}

	void CalculateAccel()
	{
		accel = force / mass;
	}

	// https://ih0.redbubble.net/image.104978724.0105/raf,750x1000,075,t,ff4c00:b001c7b98d.u2.jpg
	void UpdateSpeeeeeeed()
	{
		speed += accel * Time::GetDeltaTime();
		speed += math::Vector3::Down * 9.82f * Time::GetDeltaTime();
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

	void BuildMovementDirection()
	{
		currentDirection = m_transform->Forward() + math::Vector3(cosf(angleX), 0.0f, sinf(angleX)) * 180.0f;
		currentDirection += m_transform->Up() * sinf(angleY);
		speed = currentDirection;
		
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

		
	}

	void Update()
	{
		BuildMovementDirection();
		CalculateForce();
		CalculateAccel();
		UpdateSpeeeeeeed();
		float dt = Time::GetDeltaTime();
		m_downSpeed += 9.82*dt;

		m_transform->Translate(speed);


		if (m_transform->GetPosition().y < 0.0)
		{
			m_splashSound->PlayOneShot(m_SFXs[rand() % 3], 0.5);
			Destroy(this);
		}
			
	}

private:
	math::Vector3 force;
	float angleX;
	float angleY;
	float mass;
	float radius;
	float Cd = 0.35f;
	math::Vector3 accel;
	math::Vector3 speed;
	float m_downSpeed;
	math::Vector3 currentDirection;
	component::SoundComponent* m_splashSound;
	component::RenderComponent* m_renderer;
	std::string m_SFXs[3] = { "fSplash1", "fSplash2", "fSplash3" };
};