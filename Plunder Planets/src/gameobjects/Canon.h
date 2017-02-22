#pragma once
#include "Thomas.h"
#include "Projectile.h"
#include <time.h>
#include "object\component\EmitterComponent.h"

using namespace thomas;
using namespace object;

class Canon : public GameObject
{
private:


public:
	Canon() : GameObject("Canon") 
	{

	};

	void Start()
	{
		m_emitterComponent = AddComponent<component::EmitterComponent>();
		m_emitterComponent->Init(256 * 5 + 254, false, math::Vector3(0, 1, 0), 0.0f, 1.0f, 2.0f, 3.4f, m_transform->GetPosition(), 0.1f, 0.7f, 6.0f, "particleShader", "../res/textures/smoke.dds");

		roof = 0.8f;
		ReseedDelay();
	}

	void SetMaxCanonDelay(float delay)
	{
		this->roof = delay;
	}

	void ReseedDelay()
	{
		delay = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / roof));
	}

	void Update()
	{
		if (fire)
		{
			if (currentTimeCount > delay)
			{
				m_emitterComponent->Emit();
				// instanciate projectile
				Projectile* p = Instantiate<Projectile>(m_transform->GetPosition(), m_transform->GetRotation(), m_scene);
				currentTimeCount = 0.0f;
				fire = false;
			}
			else
			{
				currentTimeCount += thomas::Time::GetDeltaTime();
			}
		}
	};

	void FireCanon()
	{
		if (!fire)
		{
			fire = true;
			currentTimeCount = 0.0f;
		}
	}

	~Canon()
	{

	}

private:
	bool fire;
	float delay;
	float roof;
	float currentTimeCount;
	component::EmitterComponent* m_emitterComponent;
};