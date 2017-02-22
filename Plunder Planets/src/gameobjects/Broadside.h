#pragma once
#include "Thomas.h"
#include "Cannon.h"

using namespace thomas;
using namespace object;
class Broadside : public GameObject
{

private:

public:
	Broadside() : GameObject("BroadSide")
	{

	}

	void Start()
	{
		m_delay = 1.5;
		m_delayLeft = 0;
		m_fireSFX = AddComponent<component::SoundComponent>();
		m_pitch = 0.0f;
		m_yaw = 0.0f;

		m_box = AddComponent<component::RenderComponent>();
		m_box->SetModel("box1");
	}

	void CreateCannons()
	{
		float spacing = 2.3;
		for (int i = -1; i <= 3; i++)
		{
			m_fireSFX->PlayOneShot(m_SFXs[rand() % 2], 1);
			math::Vector3 pos = math::Vector3(0.0f);
			pos += m_transform->Forward()*i*spacing - m_transform->Up() * 3.5;

			Cannon* c = Instantiate<Cannon>(pos, math::Quaternion::Identity, m_transform, m_scene);
			m_cannons.push_back(c);
		}
	}

	void Fire()
	{
		if (m_delayLeft <= 0)
		{
			for (auto cannon : m_cannons)
			{
				cannon->FireCannon();
			}
			m_delayLeft = m_delay;
		}
	}

	void Update()
	{
		float dt = Time::GetDeltaTime();
		m_delayLeft -= dt;
	}
	bool IncreasePitch(unsigned float pitch)
	{
		if (m_pitch < 5.f)
		{
			m_pitch += (float)pitch;
			return true;
		}
		return false;
	}
	bool IncreaseYaw(unsigned float yaw)
	{
		if (m_yaw < 10.f)
		{
			m_yaw += (float)yaw;
			return true;
		}
		return false;
	}
	bool DecreasePitch(unsigned float pitch)
	{
		if (m_pitch > -5.f)
		{
			m_pitch -= (float)pitch;
			return true;
		}
		return false;
	}
	bool DecreaseYaw(unsigned float yaw)
	{
		if (m_yaw > -10.f)
		{
			m_yaw -= (float)yaw;
			return true;
		}
		return false;
	}

private:
	float m_delay;
	float m_delayLeft;
	float m_pitch, m_yaw;

	std::vector<Cannon*> m_cannons; 
	component::SoundComponent* m_fireSFX;
	component::RenderComponent* m_box;
	std::string m_SFXs[2] = { "fCannon1", "fCannon2" };
};