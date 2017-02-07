#pragma once
#include "Thomas.h"
#include "Projectile.h"

using namespace thomas;
using namespace object;
class Broadside : public GameObject
{

private:

public:
	Broadside() : GameObject("BroadSide")
	{
	}

	bool Start()
	{
		return true;
	}


	void Fire(float forwardSpeed)
	{
		float spacing = 2.3;
		for (int i = -2; i <= 2; i++)
		{
			LOG("fire");
			math::Vector3 pos = m_transform->GetPosition();
			math::Quaternion rot = m_transform->GetRotation();
			rot += math::Quaternion::CreateFromAxisAngle(m_transform->Up(), -math::DegreesToradians(i));
			pos += m_transform->Right()*i*spacing;
			Projectile* p = (Projectile*)Instantiate(new Projectile(), pos, rot);
			p->forwardSpeed = forwardSpeed;
		}
		
	}

	void Update()
	{
		float dt = Time::GetDeltaTime();
	}

private:

};