#pragma once
#pragma once
#include "Thomas.h"

using namespace thomas;
using namespace object;
class Projectile : public GameObject
{

private:

public:
	float forwardSpeed = 0;
	Projectile() : GameObject("Projectile")
	{

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
		m_transform->Translate(m_transform->Right()*dt*forwardSpeed/2);
		m_transform->Translate(math::Vector3::Down*m_downSpeed*dt);


		if (m_transform->GetPosition().y < 0.0)
		{
			m_splashSound->PlayOneShot(m_SFXs[rand() % 3], 0.5);
			Destroy(this);
		}
			
	}
private:
	float m_downSpeed;
	component::SoundComponent* m_splashSound;
	component::RenderComponent* m_renderer;
	std::string m_SFXs[3] = { "fSplash1", "fSplash2", "fSplash3" };
};