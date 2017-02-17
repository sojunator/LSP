#pragma once
#include "Thomas.h"
#include "Canon.h"

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
		for (int i = -2; i <= 2; i++)
		{

		}
	}


	void Fire(float forwardSpeed)
	{
		if (m_delayLeft <= 0)
		{
			float spacing = 2.3;
			for (int i = -2; i <= 2; i++)
			{
				m_fireSFX->PlayOneShot(m_SFXs[rand()%2],1);
				math::Vector3 pos = m_transform->GetPosition();
				math::Quaternion rot = m_transform->GetRotation();
				pos += m_transform->Right()*i*spacing;
				Canon* c = Instantiate<Canon>(pos, rot, m_scene);
				c->FireCanon();

			}
			
			m_delayLeft = m_delay;
		}

		
		
	}

	void Update()
	{
		float dt = Time::GetDeltaTime();
		m_delayLeft -= dt;
	}

private:
	float m_delay;
	float m_delayLeft;
	std::vector<Canon*> canons; 
	component::SoundComponent* m_fireSFX;
	std::string m_SFXs[2] = { "fCannon1", "fCannon2" };
};