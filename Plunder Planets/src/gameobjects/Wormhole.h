#pragma once

#include "Thomas.h"

using namespace thomas;
using namespace object;
class Wormhole : public GameObject
{

private:

public:
	Wormhole() : GameObject("PhysicsTest")
	{

	}

	void Start()
	{
		m_transform->SetPosition(0, 300, 0);
		m_emitter = AddComponent<component::ParticleEmitterComponent>();
		m_emitter->SetLooping(true);
		m_emitter->StartEmitting();
		m_emitter->SetSize(100);
		m_emitter->SetPosition(0, 300, 0);
		m_emitter->SetNrOfParticles(1);
		m_emitter->SetTexture("../res/textures/wormhole.png");
	}

	void Update()
	{
	}

private:
	component::ParticleEmitterComponent* m_emitter;
};