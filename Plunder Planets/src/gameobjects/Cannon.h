#pragma once
#include "Thomas.h"
#include "Projectile.h"
#include <time.h>

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
		m_emitterSmoke = AddComponent<component::ParticleEmitterComponent>();
		m_emitterSmoke->SetNrOfParticles(256 * 4 + 254);
		m_emitterSmoke->SetTexture("../res/textures/sumo-wrestler2.png");
		m_emitterSmoke->SetShader("particleShader");
		m_emitterSmoke->SetPosition(m_transform->GetPosition());
		m_emitterSmoke->SetDirection(math::Vector3(0, 1, 0));
		m_emitterSmoke->SetStartColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_emitterSmoke->SetEndColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_emitterSmoke->SetMaxDelay(1.75f);
		m_emitterSmoke->SetMinDelay(0.15f);
		m_emitterSmoke->SetMaxSpeed(9.0f);
		m_emitterSmoke->SetMinSpeed(6.0f);
		m_emitterSmoke->SetMaxSize(2.2f);
		m_emitterSmoke->SetMinSize(1.4f);
		m_emitterSmoke->SetEndSize(3.0f);
		m_emitterSmoke->SetMaxLifeTime(10.75f);
		m_emitterSmoke->SetMinLifeTime(0.7f);
		m_emitterSmoke->SetSpread(0.2f);
		
		m_emitterSmoke2 = AddComponent<component::ParticleEmitterComponent>();
		m_emitterSmoke2->SetNrOfParticles(256 * 10 + 254);
		m_emitterSmoke2->SetTexture("../res/textures/sumo-wrestler2.png");
		m_emitterSmoke2->SetShader("particleShader");
		m_emitterSmoke2->SetPosition(m_transform->GetPosition());
		m_emitterSmoke2->SetDirection(math::Vector3(0, 1, 0));
		m_emitterSmoke2->SetStartColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_emitterSmoke2->SetEndColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_emitterSmoke2->SetMaxDelay(2.5f);
		m_emitterSmoke2->SetMinDelay(0.15f);
		m_emitterSmoke2->SetMaxSpeed(13.0f);
		m_emitterSmoke2->SetMinSpeed(6.0f);
		m_emitterSmoke2->SetMaxSize(1.0f);
		m_emitterSmoke2->SetMinSize(0.5f);
		m_emitterSmoke2->SetEndSize(1.7);
		m_emitterSmoke2->SetMaxLifeTime(1.2f);
		m_emitterSmoke2->SetMinLifeTime(0.5f);
		m_emitterSmoke2->SetSpread(0.09f);

		m_emitterSpark = AddComponent<component::ParticleEmitterComponent>();

		m_emitterSpark->SetNrOfParticles(360);
		m_emitterSpark->SetTexture("../res/textures/spark.png");
		m_emitterSpark->SetShader("particleShader");
		m_emitterSpark->SetPosition(m_transform->GetPosition());
		m_emitterSpark->SetDirection(math::Vector3(0, 0, 1));
		m_emitterSpark->SetMaxDelay(0.0f);
		m_emitterSpark->SetMinDelay(0.0f);
		m_emitterSpark->SetMaxSpeed(27.0f);
		m_emitterSpark->SetMinSpeed(16.0f);
		m_emitterSpark->SetEndColor(math::Vector4(0.5f, 0.0f, 0.0f, 1.0f));
		m_emitterSpark->SetMaxSize(0.4f);
		m_emitterSpark->SetMinSize(0.1f);
		m_emitterSpark->SetEndSize(0.0f);
		m_emitterSpark->SetMaxLifeTime(0.12f);
		m_emitterSpark->SetMinLifeTime(0.02f);
		m_emitterSpark->SetSpread(0.11f);

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
				math::Vector3 dir = m_transform->Forward();
				dir.Normalize();
				m_emitterSmoke->SetPosition(m_transform->GetPosition());
				m_emitterSmoke->SetDirection(dir);
				m_emitterSmoke->StartEmitting();
				m_emitterSmoke2->SetPosition(m_transform->GetPosition());
				m_emitterSmoke2->SetDirection(dir);
				m_emitterSmoke2->StartEmitting();
				m_emitterSpark->SetPosition(m_transform->GetPosition());
				m_emitterSpark->SetDirection(dir);
				m_emitterSpark->StartEmitting();
				
				
				
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
	component::ParticleEmitterComponent* m_emitterSmoke;
	component::ParticleEmitterComponent* m_emitterSmoke2;
	component::ParticleEmitterComponent* m_emitterSpark;
};