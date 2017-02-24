#pragma once
#include "Thomas.h"
#include "WaterObject.h"
#include "WaterSplashParticle.h"
using namespace thomas;
using namespace object;
class Projectile : public GameObject
{

private:
	void CalculateDrag()
	{
		btScalar temp_vel = m_rigidbody->getLinearVelocity().length(); // ehm, borde vara length2
		btVector3 temp = constant * temp_vel * temp_vel * m_rigidbody->getLinearVelocity().normalized();
		m_force = temp;
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
		m_mass = 2.5f;
		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("cannonball");
		m_transform->SetScale(2);
		m_splashSound = AddComponent<component::SoundComponent>();
		m_rigidbody = AddComponent<component::RigidBodyComponent>();
		constant = -0.5 * m_Cd * 1.21f * m_radius * m_radius * math::PI;
		m_rigidbody->setCollisionShape(new btSphereShape(0.35f));
		m_rigidbody->SetMass(m_mass); 
		m_velocity = 200;
		m_water = (WaterObject*)Find("WaterObject");
		

		if (!m_water)
		{
			LOG("Errorroror no wadder found");
			m_hitWater = true;
		}
		else
		{
			m_hitWater = false;
		}
		m_rigidbody->setLinearVelocity(m_velocity * (*(btVector3*)&m_transform->Forward() * cosf(math::DegreesToradians(m_pitch)) * cosf(math::DegreesToradians(m_yaw))+ 
			*(btVector3*)&m_transform->Up() * (sinf(math::DegreesToradians(m_pitch))) + 
			*(btVector3*)&m_transform->Right() * cosf(math::DegreesToradians(m_pitch)) * sinf(math::DegreesToradians(m_yaw))));
		m_damageAmount = 5;
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
			math::Vector3 deltaWater = m_water->GetCollisionAt(m_transform);
			float heightBelowWater = deltaWater.y - m_transform->GetPosition().y;
			if (heightBelowWater > 3.0)
			{
				//Instantiate<WaterSplashParticle>(m_transform->GetPosition(), m_transform->GetRotation(), m_scene);
				m_splashSound->PlayOneShot(m_SFXs[rand() % 3], 0.5);
				Destroy(this);
			}
		}
			
	}

	void OnCollision(component::RigidBodyComponent* other)
	{
		if(other->m_gameObject != m_spawnedBy && other->m_gameObject->GetType() != "Projectile")
			Destroy(this);

	}

	float GetDamageAmount()
	{
		return m_damageAmount;
	}

public:
	GameObject* m_spawnedBy;
private:
	float m_velocity;
	btVector3 m_force;
	float m_damageAmount;
	float m_yaw;
	float m_pitch;
	float m_mass = 5.0f;
	btScalar m_radius = 0.05f;
	btScalar m_Cd = 0.47f;
	btScalar constant;
	
	component::ParticleEmitterComponent* m_emitterComponent;
	component::SoundComponent* m_splashSound;
	component::RenderComponent* m_renderer;
	component::RigidBodyComponent* m_rigidbody;
	std::string m_SFXs[3] = { "fSplash1", "fSplash2", "fSplash3" };
	WaterObject* m_water;
	bool m_hitWater;
};