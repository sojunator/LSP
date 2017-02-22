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
		m_emitterComponent = AddComponent<component::EmitterComponent>();
		m_emitterComponent->Init(256 * 100 + 254, false, math::Vector3(0, 1, 0), 0.0f, 2.0f, 1.0f, 3.0f, m_transform->GetPosition(), 0.1f, 0.15f, 2.5f, "particleShader", "../res/textures/smokeParticleDank.png");
	}


	void Update()
	{
		if (Input::GetKeyDown(Input::Keys::NumPad1))
		{
			m_emitterComponent->Emit();
		}
		else if (Input::GetKeyDown(Input::Keys::NumPad9))
		{
			m_emitterComponent->Stop();
		}

	}

private:
	component::EmitterComponent* m_emitterComponent;
};