#pragma once

#include "Thomas.h"

using namespace thomas;
using namespace object;
class Wormhole : public GameObject
{

private:

public:
	Wormhole() : GameObject("Wormhole")
	{

	}

	void OnEnable()
	{
		if (m_wormhole)
		{
			m_wormholeParticles->StartEmitting();
			m_wormhole->StartEmitting();
		}
			
	}

	void OnDisable()
	{
		m_wormholeParticles->StopEmitting();
		m_wormhole->StopEmitting();
	}

	void Start()
	{
		m_transform->SetPosition(0, 300, 0);
		m_wormhole = AddComponent<component::ParticleEmitterComponent>();
		m_wormholeParticles = AddComponent<component::ParticleEmitterComponent>();
		
		m_wormhole->SetSize(50);
		m_wormhole->SetTexture("../res/textures/wormhole.png");
		m_wormhole->SetRotationSpeed(math::DegreesToradians(20));
		m_wormhole->SetLifeTime(18);
		m_wormhole->SetLooping(true);
		m_wormhole->SetDelay(0);
		m_wormhole->SetEmissionRate(1.0f/18.0f);
		m_wormhole->SetSpeed(0);
		m_wormhole->StartEmitting();
	//	SetActive(false);


		m_wormholeParticles->SetLooping(true);
		//m_wormholeParticles->SetDirection(0, 0, 1);
		m_wormholeParticles->SetSpread(180);
		m_wormholeParticles->SetSpeed(20, 50);
		m_wormholeParticles->SetEndSpeed(100);
		m_wormholeParticles->SetRotationSpeed(11);
		m_wormholeParticles->SetLifeTime(1, 2);
		m_wormholeParticles->SetDelay(0);
		m_wormholeParticles->SetSize(1, 2.5);
		m_wormholeParticles->SetEmissionRate(500);
		m_wormholeParticles->SetEndSize(0);
		m_wormholeParticles->SetRadius(50);
		m_wormholeParticles->SetEndColor(math::Color(0, 1, 0, 0));
		m_wormholeParticles->SpawnAtSphereEdge(true);
		//m_wormholeParticles->AddToDebugMenu();

		m_wormholeParticles->SetTexture("../res/textures/wormholeParticles.png");
		m_wormholeParticles->StartEmitting();
		//m_wormhole->StartEmitting();
	}

	void Update()
	{

	}

private:
	component::ParticleEmitterComponent* m_wormhole;
	component::ParticleEmitterComponent* m_wormholeParticles;
};