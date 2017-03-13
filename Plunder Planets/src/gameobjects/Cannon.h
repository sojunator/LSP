#pragma once
#include "Thomas.h"
#include "Projectile.h"
#include <time.h>
#include "ShipStats.h"

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
		m_fire = false;
		m_fireTwice = false;
		m_fireTwiceTimer = 0.7f;

		m_emitterSmoke = AddComponent<component::ParticleEmitterComponent>();
		m_emitterSmoke->SetTexture("../res/textures/smokelight.png");
		m_emitterSmoke->SetShader("particleShader");
		m_emitterSmoke->SetDirection(math::Vector3(0, 1, 0));
		m_emitterSmoke->SetStartColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_emitterSmoke->SetEndColor(math::Vector4(1.0f, 1.0f, 1.0f, 0.5f));
		m_emitterSmoke->SetMaxDelay(0.25f);
		m_emitterSmoke->SetMinDelay(0.05f);
		m_emitterSmoke->SetMaxSpeed(6.0f);
		m_emitterSmoke->SetMinSpeed(3.0f);
		m_emitterSmoke->SetMaxSize(1.7f);
		m_emitterSmoke->SetMinSize(1.0f);
		m_emitterSmoke->SetEndSize(2.4f);
		m_emitterSmoke->SetMaxLifeTime(1.2f);
		m_emitterSmoke->SetMinLifeTime(0.7f);
		m_emitterSmoke->SetRotationSpeed(2.5f);
		m_emitterSmoke->SetSpread(1.44f);
		m_emitterSmoke->SetEmissionRate(250);
		m_emitterSmoke->SetEmissionDuration(0.4f);
		
		m_emitterSmoke2 = AddComponent<component::ParticleEmitterComponent>();
		m_emitterSmoke2->SetTexture("../res/textures/smokethick.png");
		m_emitterSmoke2->SetShader("particleShader");
		m_emitterSmoke2->SetDirection(math::Vector3(0, 1, 0));
		m_emitterSmoke2->SetStartColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_emitterSmoke2->SetEndColor(math::Vector4(0.0f, 0.0f, 0.0f, 0.1f));
		m_emitterSmoke2->SetMaxDelay(0.15f);
		m_emitterSmoke2->SetMinDelay(0.01f);
		m_emitterSmoke2->SetMaxSpeed(14.0f);
		m_emitterSmoke2->SetMinSpeed(8.0f);
		m_emitterSmoke2->SetMaxSize(1.0f);
		m_emitterSmoke2->SetMinSize(0.7f);
		m_emitterSmoke2->SetEndSize(0);
		m_emitterSmoke2->SetMaxLifeTime(1.0f);
		m_emitterSmoke2->SetMinLifeTime(0.5f);
		m_emitterSmoke2->SetSpread(1.0f);
		m_emitterSmoke2->SetEmissionRate(200);
		m_emitterSmoke2->SetEmissionDuration(0.4f);
		m_emitterSmoke2->SetRotationSpeed(1.0f);

		m_emitterSpark = AddComponent<component::ParticleEmitterComponent>();

		m_emitterSpark->SetTexture("../res/textures/spark.png");
		m_emitterSpark->SetShader("particleShader");
		m_emitterSpark->SetMaxDelay(0.0f);
		m_emitterSpark->SetMinDelay(0.0f);
		m_emitterSpark->SetMaxSpeed(27.0f);
		m_emitterSpark->SetMinSpeed(16.0f);
		m_emitterSpark->SetEndColor(math::Vector4(0.8f, 0.0f, 0.0f, 1.0f));
		m_emitterSpark->SetSize(0.4f, 0.7f);
		m_emitterSpark->SetEndSize(0.0f);
		m_emitterSpark->SetLifeTime(0.04f, 0.19f);
		m_emitterSpark->SetEmissionRate(255);
		m_emitterSpark->SetSpread(3.14f);
		m_emitterSpark->SetEmissionDuration(0.15f);
		
		
		math::Vector3 dir = m_transform->Forward() * 3 + m_transform->Up();
		dir.Normalize();
		m_emitterSmoke->SetDirection(dir);
		m_emitterSmoke2->SetDirection(dir);
		m_emitterSpark->SetDirection(dir);
		//m_emitterSmoke->SetLooping(true);
		//m_emitterSmoke2->SetLooping(true);

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

		if (m_fireTwice)
		{
			m_fireTwiceTimer -= ThomasTime::GetDeltaTime();
			if (m_fireTwiceTimer <= 0.0f)
			{
				m_fireTwice = false;
				m_fireTwiceTimer = 0.4f;
				m_fire = true;
			}
		}

		if (m_fire)
		{
			
			m_monteCarloDelay = 0;
			if (m_monteCarloDelay <= 0)
			{
				m_emitterSmoke2->StartEmitting();
				m_emitterSmoke->StartEmitting();
				m_emitterSpark->StartEmitting();
				
				
				
				// instanciate projectile
				Projectile* p = Instantiate<Projectile>(m_transform->GetPosition(), m_transform->GetRotation(), m_scene);
				p->m_spawnedBy = m_transform->GetParent()->GetParent()->m_gameObject;
				p->SetDamageAmount(m_projectileDamage);
				m_fire = false;
				ReseedDelay();
			}
			else
			{
				m_monteCarloDelay -= thomas::ThomasTime::GetDeltaTime();
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
			if ((int)ShipStats::s_playerStats->GetCannonCounter() == 5)
			{
				m_fireTwice = true;
			}
		}
	}

	void SetProjectileDamage(float dmg)
	{
		m_projectileDamage = dmg;
	}

	~Cannon()
	{

	}

private:
	bool m_fire;
	bool m_fireTwice;
	float m_fireTwiceTimer;

	float roof;
	float m_monteCarloDelay;
	float m_projectileDamage;
	component::ParticleEmitterComponent* m_emitterSmoke;
	component::ParticleEmitterComponent* m_emitterSmoke2;
	component::ParticleEmitterComponent* m_emitterSpark;
};