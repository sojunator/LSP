#pragma once
#pragma once
#include "Thomas.h"

using namespace thomas;
using namespace object;
class Projectile : public GameObject
{

private:
	float angleX;
	float angleY;
public:
	float forwardSpeed = 0;
	Projectile() : GameObject("Projectile")
	{
		angleX = monteCarloAngle();
		angleY = monteCarloAngle() + 10;
	}

	void Start()
	{
		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("cannonball");

		m_splashSound = AddComponent<component::SoundComponent>();
	}

	void Update()
	{
		float speed = 180.0;
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
	float monteCarloAngle()
	{
		float randNum = rand() % 999 + 1;
		randNum /= 1000.0f;
		if (randNum < 0.5f)
			return 15 * (sqrtf(2.0f * randNum) - 1);
		else
			return 10 * (1 - sqrtf(2 - 2 * randNum));
	}

	float m_downSpeed;
	component::SoundComponent* m_splashSound;
	component::RenderComponent* m_renderer;
	std::string m_SFXs[3] = { "fSplash1", "fSplash2", "fSplash3" };
};