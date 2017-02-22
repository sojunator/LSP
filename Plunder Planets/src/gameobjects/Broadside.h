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
		m_delay = 4.5;
		m_delayLeft = 0;
		m_fireSFX = AddComponent<component::SoundComponent>();
		//m_renderer = AddComponent<component::RenderComponent>();

		//m_renderer->SetModel("cannonball");		
	}

	void CreateCanons()
	{
		float spacing = 2.3;
		for (int i = -1; i <= 3; i++)
		{
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
			m_fireSFX->PlayOneShot(m_SFXs[rand() % 2], 1); //play cannon sound
			for (auto canon : canons)
			{
				canon->FireCanon();
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
	component::RenderComponent* m_renderer;
};