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
		m_emitterSmoke->Init(256 * 4 + 254, false, math::Vector3(0, 1, 0), 0.1f, 1.9f, 6.1f, 10.4f, m_transform->GetPosition(), 0.205f, 1.4f, 2.25f, 0.4f, 1.9f, 1, "particleShader", "../res/textures/smokeParticle.png");
		m_emitterSmoke2 = AddComponent<component::EmitterComponent>();
		m_emitterSmoke2->Init(256 * 10 + 254, false, math::Vector3(0, 1, 0), 0.1f, 2.7f, 6.1f, 13.4f, m_transform->GetPosition(), 0.08f, 0.5f, 0.95f, 0.4f, 0.9f, 1, "particleShader", "../res/textures/smoke.dds");

		m_emitterSpark = AddComponent<component::EmitterComponent>();
		m_emitterSpark->Init(320, false, math::Vector3(0, 0, 1), 0.0f, 0.0f, 16.0f, 28.4f, m_transform->GetPosition(), 0.1f, 0.1f, 0.4f, 0.02f, 0.12f, 1, "particleShader", "../res/textures/spark.png");

		
		roof = 0.8f;
		ReseedDelay();
	}

	void SetMaxCannonDelay(float delay)
	{
		this->roof = delay;
	}

	void ReseedDelay()
	{
		m_monteCarloDelay = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / roof));
	}

	void Update()
	{
		if (m_fire)
		{
			if (m_monteCarloDelay < 0)
			{
				math::Vector3 smokeDir = m_transform->Forward() * 6 + math::Vector3(0, 1, 0);
				smokeDir.Normalize();
				m_emitterSmoke->Update(NULL, smokeDir, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
				m_emitterSmoke->Emit();
				m_emitterSmoke2->Update(NULL, smokeDir, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
				m_emitterSmoke2->Emit();
				m_emitterSpark->Update(NULL, m_transform->Forward(), NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 1);
				m_emitterSpark->Emit();
				
				
				// instanciate projectile
				Projectile* p = Instantiate<Projectile>(m_transform->GetPosition(), m_transform->GetRotation(), m_scene);
				p->m_spawnedBy = m_transform->GetParent()->GetParent()->m_gameObject;
				
				m_fire = false;
			}
			else
			{
				m_monteCarloDelay -= thomas::Time::GetDeltaTime();
			}
		}
	};

	void SetCanonAngle(float angle)
	{
		m_transform->SetRotation(0, angle, 0);
	}

	void FireCannon()
	{
		if (!m_fire)
		{
			m_fire = true;
		}
	}

	~Cannon()
	{

	}

private:
	bool m_fire;
	float roof;
	float m_monteCarloDelay;
	component::EmitterComponent* m_emitterSmoke;
	component::EmitterComponent* m_emitterSmoke2;
	component::EmitterComponent* m_emitterSpark;
};