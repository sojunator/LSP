#pragma once
#include "Thomas.h"
#include "WaterObject.h"
using namespace thomas;
using namespace object;
class WaterSplashParticle : public GameObject
{
public:
	WaterSplashParticle() : GameObject("WaterSplashParticle")
	{

	}

	void Start()
	{
		//m_emitterComponent = AddComponent<component::ParticleEmitterComponent>();
		
		m_emitterSpark = AddComponent<component::ParticleEmitterComponent>();
		m_emitterSpark->SetNrOfParticles( 254);
		m_emitterSpark->SetTexture("../res/textures/spark.png");
		m_emitterSpark->SetShader("particleShader");
		m_emitterSpark->SetPosition(m_transform->GetPosition());
		m_emitterSpark->SetDirection(math::Vector3(0, 0, 1));
		m_emitterSpark->SetMaxDelay(0.0f);
		m_emitterSpark->SetMinDelay(0.0f);
		m_emitterSpark->SetMaxSpeed(20.0f);
		m_emitterSpark->SetMinSpeed(12.0f);
		m_emitterSpark->SetMaxSize(2.0f);
		m_emitterSpark->SetMinSize(1.0f);
		m_emitterSpark->SetMaxLifeTime(0.5f);
		m_emitterSpark->SetMinLifeTime(0.3f);
		m_emitterSpark->SetSpread(0.71f);
//		m_emitterComponent->Init(256 * 6 + 254, true, math::Vector3(0, 1, 0), 0.1f, 1.9f, 6.1f, 10.4f, m_transform->GetPosition(), 0.605f, 0.5f, 1.0f, 0.6f, 1.2f, 0.7, "particleShader", "../res/textures/splash.png");

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

	component::ParticleEmitterComponent* m_emitterSpark;
	float timer = 5.0f;
};