#pragma once

#include "Thomas.h"
using namespace thomas;
using namespace object;
class ShipFloat : public GameObject
{

private:

public:
	ShipFloat() : GameObject("ShipFloat")
	{

	}

	void Start()
	{
		m_radius = 0.5;
		m_transform->SetScale(m_radius);
		m_mass = 625.0;
		m_water = ((WaterObject*)Find("WaterObject"));

		m_emitterSplash = AddComponent<component::ParticleEmitterComponent>();
		m_emitterSplash->SetTexture("../res/textures/millsplash01.png");
		m_emitterSplash->SetShader("particleShader");
		m_emitterSplash->SetDirection(math::Vector3(0, 0.1, -0.9));
		m_emitterSplash->SetStartColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_emitterSplash->SetEndColor(math::Vector4(1.0f, 1.0f, 1.0f, 0.5f));
		m_emitterSplash->SetMaxDelay(1.2f);
		m_emitterSplash->SetMinDelay(0.16f);
		m_emitterSplash->SetMinSpeed(1.0f);
		m_emitterSplash->SetMaxSpeed(10.0f);
		m_emitterSplash->SetSize(4);
		m_emitterSplash->SetMaxLifeTime(1.6f);
		m_emitterSplash->SetMinLifeTime(0.3f);
		m_emitterSplash->SetRotationSpeed(0.07f);
		m_emitterSplash->SetSpread(0.6f);
		m_emitterSplash->SetEmissionRate(15);
		m_emitterSplash->SetEmissionDuration(0.1f);
		m_emitterSplash->SetRadius(4.0f);
		m_splashSound = AddComponent<component::SoundComponent>();

	}

	void SetMass(float m)
	{
		m_mass = m;
		m_radius = m / 5000.0;
		m_radius *= 5;
		m_transform->SetScale(m_radius);
	}

	float UpdateBoat(component::RigidBodyComponent* rb) 
	{

		float deltaWater = m_water->GetWaterHeightAtColliderIndex(m_collisionIndex);
		m_collisionIndex = m_water->RegisterColliderAt(m_transform->GetPosition());
		float heightBelowWater = deltaWater - m_transform->GetPosition().y;
		
		if (heightBelowWater > 0)
		{
			
			float volume = (4.0 / 3.0)*math::PI*m_radius;
			float height = m_radius*2;
			float density = m_mass/volume;
			float volumeUnderWater = height - heightBelowWater;
			if (volumeUnderWater < 0)
				volumeUnderWater = height;
			volumeUnderWater = (4.0 / 3.0)*math::PI*volumeUnderWater/2;
			
			float waterDensity = 5.0 * density;
			btVector3 force = (volumeUnderWater*waterDensity)*-rb->getGravity();
			math::Vector3 pos = math::Vector3::Transform(m_transform->m_localPosition, math::Matrix::CreateFromQuaternion(rb->m_gameObject->m_transform->GetRotation()));

			float damping;
			if (heightBelowWater < 2.0)
			{
				damping = 0.2;
			}
			else if (heightBelowWater < 5.0)
			{
				damping = 0.5;
			}
			else
			{
				damping = 1.0;
			}
			force *= damping;
			if (force.length()/rb->GetMass() > 10)
			{
				float splashForce = force.length() / rb->GetMass();
				float size = (splashForce - 10) / 3;
				m_emitterSplash->SetSize(size);
				m_emitterSplash->StartEmitting();
				m_splashSound->PlayOneShot(m_SFXs[rand() % 3], size/30);
				
			}
			rb->applyImpulse(force*ThomasTime::GetDeltaTime(), *(btVector3*)&pos);
		}
		
		return deltaWater;

		
	}

	void Update()
	{

	}

private:
	int m_collisionIndex;
	float m_radius;
	float m_mass;
	WaterObject* m_water;
	component::ParticleEmitterComponent* m_emitterSplash;
	component::SoundComponent* m_splashSound;
	std::string m_SFXs[3] = { "fSplash1", "fSplash2", "fSplash3" };
};