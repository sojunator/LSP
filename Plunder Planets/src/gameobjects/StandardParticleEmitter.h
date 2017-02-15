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