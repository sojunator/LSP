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
	

		m_box = AddComponent<component::RenderComponent>();
		m_box->SetModel("box1");
	}

	void CreateCanons()
	{
		float spacing = 2.3;
		for (int i = -1; i <= 3; i++)
		{
			m_fireSFX->PlayOneShot(m_SFXs[rand() % 2], 1);
			math::Vector3 pos = math::Vector3(0.0f);
			pos += m_transform->Forward()*i*spacing - m_transform->Up() * 3.5;

			Canon* c = Instantiate<Canon>(pos, math::Quaternion::Identity, m_transform, m_scene);
			canons.push_back(c);
		}
	}

	void Fire()
	{
		if (m_delayLeft <= 0)
		{
			for (auto canon : canons)
			{
				canon->FireCanon();
			}
			m_delayLeft = m_delay;
		}
	}

	void Update()
	{
		forward = m_transform->Forward();
		right = m_transform->Right();
		float dt = Time::GetDeltaTime();
		m_delayLeft -= dt;
	}

private:
	float m_delay;
	float m_delayLeft;
	math::Vector3 forward, right;

	std::vector<Canon*> canons; 
	component::SoundComponent* m_fireSFX;
	component::RenderComponent* m_box;
	std::string m_SFXs[2] = { "fCannon1", "fCannon2" };
};