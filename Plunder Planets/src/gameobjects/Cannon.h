#pragma once
#include "Thomas.h"
#include "Projectile.h"
#include <time.h>
#include "object\component\EmitterComponent.h"

using namespace thomas;
using namespace object;

class Cannon : public GameObject
{
private:


public:
	Cannon() : GameObject("Cannon") 
	{

	};

	void Start()
	{
		m_emitterSmoke = AddComponent<component::EmitterComponent>();
		m_emitterSmoke->Init(256 * 10 + 254, false, math::Vector3(0, 1, 0), 0.3f, 0.3f, 2.0f, 6.4f, m_transform->GetPosition(), 0.035f, 0.6f, 2.2f, 1.4f, 3.2f, "particleShader", "../res/textures/smoke.dds");

		m_emitterSpark = AddComponent<component::EmitterComponent>();
		m_emitterSpark->Init(126, false, math::Vector3(0, 0, 1), 0.0f, 0.0f, 26.0f, 38.4f, m_transform->GetPosition(), 0.3f, 0.2f, 0.4f, 0.06f, 0.08f, "particleShader", "../res/textures/spark.png");

		roof = 0.8f;
		ReseedDelay();
	}

	void SetMaxCannonDelay(float delay)
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
				math::Vector3 smokeDir = m_transform->Forward() * 0.5 + math::Vector3(0, 1, 0);
				smokeDir.Normalize();
				m_emitterSmoke->Update(NULL, smokeDir, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
				m_emitterSmoke->Emit();
				m_emitterSpark->Update(NULL, m_transform->Forward(), NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
				m_emitterSpark->Emit();
				// instanciate projectile
				Projectile* p = Instantiate<Projectile>(m_transform->GetPosition(), m_transform->GetRotation(), m_scene);
				p->m_spawnedBy = m_transform->GetParent()->GetParent()->m_gameObject;
				currentTimeCount = 0.0f;
				fire = false;
			}
			else
			{
				currentTimeCount += thomas::Time::GetDeltaTime();
			}
		}
	};

	void FireCannon()
	{
		if (!fire)
		{
			fire = true;
			currentTimeCount = 0.0f;
		}
	}

	~Cannon()
	{

	}

private:
	bool fire;
	float delay;
	float roof;
	float currentTimeCount;
	component::EmitterComponent* m_emitterSmoke;
	component::EmitterComponent* m_emitterSpark;
};