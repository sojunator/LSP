#pragma once
#include "Thomas.h"
#include "WaterObject.h"
using namespace thomas;
using namespace object;
class WaterSplashParticle : public GameObject
{
private:
	component::EmitterComponent* m_emitterComponent;
	float timer = 7.0f;
public:
	WaterSplashParticle() : GameObject("WaterSplashParticle")
	{

	}

	void Start()
	{
		m_emitterComponent = AddComponent<component::EmitterComponent>();
		
		m_emitterComponent->Init(256 * 6 + 254, true, math::Vector3(0, 1, 0), 0.1f, 1.9f, 6.1f, 10.4f, m_transform->GetPosition(), 0.605f, 0.5f, 1.0f, 0.6f, 1.2f, 0.7, "particleShader", "../res/textures/splash.png");

	}

	void Update()
	{
		timer -= Time::GetDeltaTime();
		if (timer < 0.0f)
		{
			Destroy(this);
		}
	}

private:


};