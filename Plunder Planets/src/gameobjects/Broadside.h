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
		m_delay = 0;
		m_delayLeft = 0;
		m_fireSFX = AddComponent<component::SoundComponent>();
		m_pitch = 0.f;
		m_yaw = 0.f;


	}

	void CreateCannons()
	{
		float spacing = 2.3;
		for (int i = -1; i <= 3; i++)
		{
			math::Vector3 pos = math::Vector3(0.0f);
			pos += math::Vector3(1,0,0)*i*spacing - math::Vector3(0, 1, 0) * 5;

			Cannon* c = Instantiate<Cannon>(pos, math::Quaternion::Identity, m_transform, m_scene);
			m_cannons.push_back(c);
		}
	}

	void Fire()
	{
		if (m_delayLeft <= 0)
		{
			m_fireSFX->PlayOneShot(m_SFXs[rand() % 2], 1); //play cannon sound
			for (auto cannon : m_cannons)
			{
				cannon->FireCannon();
			}
			m_delayLeft = m_delay;
		}
	}

	bool CanFire()
	{
		return m_delayLeft <= 0;
	}

	void SetCanonLookAt(math::Vector3 pos)
	{
		for (auto cannon : m_cannons)
		{
			cannon->m_transform->LookAt(pos);
		}
	}

	void SetCanonAngle(float angle)
	{
		for (auto cannon : m_cannons)
		{
			cannon->SetCanonAngle(angle);
		}
	}

	float CalculateCanonAngle(math::Vector3 target)
	{
		math::Vector3 broadsidePos = m_transform->GetPosition();
		float y = m_cannons[0]->m_transform->GetPosition().y - target.y;

		float xx = target.x - broadsidePos.x;
		float xz = target.z - broadsidePos.z;
		float x = sqrtf(xx*xx + xz*xz);

		float v = 200;

		float g = Physics::s_world->getGravity().getY();

		float square = (v*v*v*v) - (g*(g*(x*x) + 2 * y*(v*v)));

		if (square < 0.0)
		{
			return -1000.0;
		}
		square = sqrtf(square);
		if (x < 5000)
			return atanf(((v*v) - square) / (g*x));
		else
			return atanf(((v*v) + square) / (g*x));

	}

	void Update()
	{
		float dt = ThomasTime::GetDeltaTime();
		m_delayLeft -= dt;

	}
	bool IncreasePitch(float pitch)
	{
		if (m_pitch < 10.f)
		{
			m_pitch += (float)pitch;
			return true;
		}
		return false;
	}
	bool IncreaseYaw(float yaw)
	{
		if (m_yaw < 10.f)
		{
			m_yaw += (float)yaw;
			return true;
		}
		return false;
	}
	bool DecreasePitch(float pitch)
	{
		if (m_pitch > -10.f)
		{
			m_pitch -= (float)pitch;
			return true;
		}
		return false;
	}
	bool DecreaseYaw(float yaw)
	{
		if (m_yaw > -10.f)
		{
			m_yaw -= (float)yaw;
			return true;
		}
		return false;
	}
	float GetPitch()
	{
		return m_pitch;
	}
	float GetYaw()
	{
		return m_yaw;
	}
	GameObject* GetCannon()
	{
		return m_cannons[0];
	}
private:
	float m_delay;
	float m_delayLeft;
	float m_pitch, m_yaw;

	std::vector<Cannon*> m_cannons; 
	component::SoundComponent* m_fireSFX;
	std::string m_SFXs[2] = { "fCannon1", "fCannon2" };
};