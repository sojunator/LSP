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
		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("cannonball");
	}

	bool Start()
	{
		return true;
	}

	void Update()
	{
		float speed = 200.0;
		float dt = Time::GetDeltaTime();
		m_downSpeed += 9.82*dt;
		m_transform->Translate(m_transform->Forward()*dt*speed);
		m_transform->Translate(m_transform->Right()*dt*forwardSpeed/2);
		m_transform->Translate(math::Vector3::Down*m_downSpeed*dt);


		if (m_transform->GetPosition().y < 0.0)
			Destroy(this);
	}

private:
	float m_downSpeed;
	component::RenderComponent* m_renderer;

};