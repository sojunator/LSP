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
		
		m_emitterSplash = AddComponent<component::ParticleEmitterComponent>();
		m_emitterSplash->SetTexture("../res/textures/millsplash01.png");
		m_emitterSplash->SetShader("particleShader");
		m_emitterSplash->SetDirection(math::Vector3(0, 1, 0));
		m_emitterSplash->SetStartColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_emitterSplash->SetEndColor(math::Vector4(1.0f, 1.0f, 1.0f, 0.5f));
		m_emitterSplash->SetMaxDelay(0.25f);
		m_emitterSplash->SetMinDelay(0.05f);
		m_emitterSplash->SetMaxSpeed(6.0f);
		m_emitterSplash->SetMinSpeed(3.0f);
		m_emitterSplash->SetMaxSize(2.7f);
		m_emitterSplash->SetMinSize(2.0f);
		m_emitterSplash->SetEndSize(2.7f);
		m_emitterSplash->SetMaxLifeTime(0.5f);
		m_emitterSplash->SetMinLifeTime(0.2f);
		m_emitterSplash->SetRotationSpeed(0.9f);
		m_emitterSplash->SetSpread(3.1f);
		m_emitterSplash->SetEmissionRate(200);
		m_emitterSplash->SetRadius(0.7f);
		m_emitterSplash->SetLooping(true);
//		m_emitterComponent->Init(256 * 6 + 254, true, math::Vector3(0, 1, 0), 0.1f, 1.9f, 6.1f, 10.4f, m_transform->GetPosition(), 0.605f, 0.5f, 1.0f, 0.6f, 1.2f, 0.7, "particleShader", "../res/textures/splash.png");

	}

	void Update()
	{
		timer -= ThomasTime::GetDeltaTime();

		m_emitterSplash->StartEmitting();

		if (timer < 0.0f)
		{
			Destroy(this);
		}
	}

private:

	component::ParticleEmitterComponent* m_emitterSplash;
	float timer = 5.0f;
};