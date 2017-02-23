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
		
		m_emitterComponent->Init(256 * 0 + 254, true, math::Vector3(0, 1, 0), 0.1f, 1.9f, 6.1f, 10.4f, m_transform->GetPosition(), 0.705f, 1.0f, 1.0f, 5.f, 5.f, 1, "particleShader", "../res/textures/smokeParticle.png");

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