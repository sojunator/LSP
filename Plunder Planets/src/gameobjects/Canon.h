#pragma once
#include "Thomas.h"
#include "Projectile.h"
#include <time.h>

using namespace thomas;
using namespace object;

class Canon : public GameObject
{
private:


public:
	Canon() : GameObject("Canon") 
	{

	};

	void Start()
	{
		delay = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.2f));

		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("box");
	}

	void SetCanonDelay()
	{

	}

	void Update()
	{
		if (fire)
		{
			if (currentTimeCount > delay)
			{
				// instanciate projectile
				Projectile* p = Instantiate<Projectile>(m_transform->GetPosition(), m_transform->GetRotation(), m_scene);
				currentTimeCount = 0.0f;
				fire = false;
			}
			else
			{
				currentTimeCount += thomas::Time::GetDeltaTime();
			}
		}
	};

	void FireCanon()
	{
		if (!fire)
		{
			fire = true;
			currentTimeCount = 0.0f;
		}
	}

	~Canon()
	{

	}

private:
	bool fire;
	float delay;
	float currentTimeCount;
	component::RenderComponent* m_renderer;
};