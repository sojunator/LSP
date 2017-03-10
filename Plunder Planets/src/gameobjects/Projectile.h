#pragma once
#include "WaterSplashParticle.h"
using namespace thomas;
using namespace object;
class Projectile : public GameObject
{

private:
	void CalculateDrag()
	{
		//btScalar temp_vel = m_rigidbody->getLinearVelocity().length();
		//btVector3 temp = constant * temp_vel * m_rigidbody->getLinearVelocity().normalized();
		/*btVector3 temp = m_mass * Physics::s_world->getGravity() * ThomasTime::GetDeltaTime();
		m_force = temp;*/
	}

	float MonteCarloAngle()
	{
		float randNum = rand() % 999 + 1;
		randNum /= 1000.0f;
		if (randNum < 0.5f)
			return 0.75f * (sqrtf(2.0f * randNum) - 1);
		else
			return 0.75f * (1 - sqrtf(2 - 2 * randNum));
	}

public:
	float forwardSpeed = 0;
	Projectile() : GameObject("Projectile")
	{
		m_yaw = MonteCarloAngle();
		m_pitch = MonteCarloAngle();
	}

	void Start()
	{
		m_mass = 25.f;
		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("cannonball");
		m_transform->SetScale(2);
		m_splashSound = AddComponent<component::SoundComponent>();
		m_rigidbody = AddComponent<component::RigidBodyComponent>();
		constant = -0.5 * m_Cd * 1.21f * m_radius * m_radius * math::PI;
		m_rigidbody->setCollisionShape(new btSphereShape(0.35f));
		m_rigidbody->SetMass(m_mass);
		m_velocity = 130.f;
		m_water = (WaterObject*)Find("WaterObject");

		m_deathTime = 4.0f;
		m_hitSurface = false;

		m_emitterSplash = AddComponent<component::ParticleEmitterComponent>();
		m_emitterSplash->SetTexture("../res/textures/millsplash01.png");
		m_emitterSplash->SetShader("particleShader");
		m_emitterSplash->SetDirection(math::Vector3(0, 1, 0));
		m_emitterSplash->SetStartColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_emitterSplash->SetEndColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_emitterSplash->SetMaxDelay(0.25f);
		m_emitterSplash->SetMinDelay(0.05f);
		m_emitterSplash->SetMaxSpeed(7.0f);
		m_emitterSplash->SetMinSpeed(3.0f);
		m_emitterSplash->SetMaxSize(3.7f);
		m_emitterSplash->SetMinSize(3.0f);
		m_emitterSplash->SetEndSize(3.7f);
		m_emitterSplash->SetMaxLifeTime(0.8f);
		m_emitterSplash->SetMinLifeTime(0.2f);
		m_emitterSplash->SetRotationSpeed(0.9f);
		m_emitterSplash->SetSpread(3.1f);
		m_emitterSplash->SetEmissionRate(1000);
		m_emitterSplash->SetEmissionDuration(0.1f);
		m_emitterSplash->SetRadius(0.7f);
		m_emitterSplash->SetOffset(math::Vector3(0, 3, 0));

		if (!m_water)
		{
			LOG("Errorroror no wadder found");
			m_hitWater = true;
		}
		else
		{
			m_hitWater = false;
		}
		m_rigidbody->setLinearVelocity(*(btVector3*)&(m_velocity * (m_transform->Forward() * cosf(math::DegreesToRadians(m_pitch)) * cosf(math::DegreesToRadians(m_yaw)) +
			m_transform->Up() * sinf(math::DegreesToRadians(m_pitch)) +
			m_transform->Right() * cosf(math::DegreesToRadians(m_pitch)) * sinf(math::DegreesToRadians(m_yaw)))));
		/*m_rigidbody->setLinearVelocity(m_velocity * (*(btVector3*)&m_transform->Forward() * cosf(math::DegreesToRadians(m_pitch)) * cosf(math::DegreesToRadians(m_yaw))+
			*(btVector3*)&m_transform->Up() * (sinf(math::DegreesToRadians(m_pitch))) +
			*(btVector3*)&m_transform->Right() * cosf(math::DegreesToRadians(m_pitch)) * sinf(math::DegreesToRadians(m_yaw))));*/
	}

	float GetVelocity()
	{
		return m_velocity;
	}


	void Update()
	{
		CalculateDrag();

		m_rigidbody->applyCentralForce(m_force);

		if (!m_hitWater)
		{
			float deltawater = m_water->GetWaterHeightAtColliderIndex(m_oceanCollisionIndex);
			m_oceanCollisionIndex = m_water->RegisterColliderAt(m_transform->GetPosition());
			float heightBelowWater = deltawater - m_transform->GetPosition().y;
			if (heightBelowWater > 3.0)
			{
				m_deathTime -= ThomasTime::GetDeltaTime();
				//Instantiate<WaterSplashParticle>(m_transform->GetPosition(), m_transform->GetRotation(), m_scene);
				if (!m_hitSurface)
				{
					m_emitterSplash->StartEmitting();
					m_splashSound->PlayOneShot(m_SFXs[rand() % 3], 0.5);
					m_hitSurface = true;
					Destroy(this);
				}
				if (m_deathTime < 0.0f)
				{
					Destroy(this);
					m_emitterSplash->StopEmitting();
				}
			}
		}

	}

	void OnCollision(component::RigidBodyComponent::Collision collision)
	{
		if (collision.otherRigidbody->m_gameObject != m_spawnedBy && collision.otherRigidbody->m_gameObject->GetType() != "Projectile"
			&& collision.otherRigidbody->m_gameObject->GetType() != "IslandObject" && collision.otherRigidbody->m_gameObject->GetType() != "TobyEnemy")
		{
			Destroy(this);
		}


	}

	void SetDamageAmount(float amount)
	{
		m_damageAmount = amount;
	}

	float GetDamageAmount()
	{
		return m_damageAmount;
	}

public:
	GameObject* m_spawnedBy;
private:
	int m_oceanCollisionIndex;
	float m_velocity;
	btVector3 m_force;
	float m_damageAmount;
	float m_yaw;
	float m_pitch;
	float m_mass = 5.0f;
	btScalar m_radius = 0.05f;
	btScalar m_Cd = 0.47f;
	btScalar constant;

	float m_deathTime;
	bool m_hitSurface;

	component::SoundComponent* m_splashSound;
	component::RenderComponent* m_renderer;
	component::RigidBodyComponent* m_rigidbody;
	component::ParticleEmitterComponent* m_emitterSplash;
	std::string m_SFXs[3] = { "fSplash1", "fSplash2", "fSplash3" };
	WaterObject* m_water;
	bool m_hitWater;
};