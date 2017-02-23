#pragma once
#include "Thomas.h"
#include "WaterObject.h"
using namespace thomas;
using namespace object;
class WaterSplashParticle : public GameObject
{
private:
	component::EmitterComponent* m_emitterComponent;

public:
	WaterSplashParticle() : GameObject("WaterSplashParticle")
	{

	}

	void Start()
	{
		m_emitterComponent = AddComponent<component::EmitterComponent>();
		m_emitterComponent->Init(256 * 10 + 254, true, math::Vector3(0, 1, 0), 0.0f, 0.0f, 2.0f, 6.4f, m_transform->GetPosition(), 0.035f, 0.6f, 2.2f, 1.4f, 3.2f, "particleShader", "../res/textures/smoke.dds");

	}

	void Update()
	{
		m_emitterComponent->Update(NULL, math::Vector3::Up, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		m_emitterComponent->Emit();
	}

private:


};