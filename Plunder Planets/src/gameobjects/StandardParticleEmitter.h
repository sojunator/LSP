#pragma once
#include "Thomas.h"
#include "Input.h"
#include "object\component\EmitterComponent.h"

using namespace thomas;
using namespace object;
class StandardParticleEmitter : public GameObject
{

private:

public:
	StandardParticleEmitter() : GameObject("Emitter")
	{

	}

	void Start()
	{
		//m_emitterComponent = AddComponent<component::EmitterComponent>();
		//m_emitterComponent->Init(256 * 100 + 254, true, math::Vector3(0, 1, 0), 4.0f, 8.0f, 2.0f, 2.4f, m_transform->GetPosition(), 0.1f, 0.4f, 14.0f, "particleShader", "../res/textures/smokeParticleDank.png");

	}


	void Update()
	{
		

	}

private:
	//component::EmitterComponent* m_emitterComponent;
};