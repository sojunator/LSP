#pragma once
#include "Thomas.h"
#include "Projectile.h"
#include <time.h>

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
		roof = 0.8f;
		ReseedDelay();
	}

	void SetMaxCannonDelay(float delay)
	{
		this->roof = delay;
	}

	void ReseedDelay()
	{
		delay = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / roof));
	}

	void Update()
	{
		if (fire)
		{
			if (currentTimeCount > delay)
			{
				// instanciate projectile
				Projectile* p = Instantiate<Projectile>(m_transform->GetPosition(), m_transform->GetRotation(), m_scene);
				p->m_spawnedBy = m_transform->GetParent()->GetParent()->m_gameObject;
				currentTimeCount = 0.0f;
				fire = false;
			}
			else
			{
				currentTimeCount += thomas::Time::GetDeltaTime();
			}
		}
	};

	void FireCannon()
	{
		if (!fire)
		{
			fire = true;
			currentTimeCount = 0.0f;
		}
	}

	~Cannon()
	{

	}

private:
	bool fire;
	float delay;
	float roof;
	float currentTimeCount;

};