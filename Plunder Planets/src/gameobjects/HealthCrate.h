#pragma once
#pragma once
#include "Thomas.h"
#include "ShipFloat.h"

using namespace thomas;
using namespace object;

class HealthCrate : public GameObject
{

public:

public:
	HealthCrate() : GameObject("HealthCrate")
	{

	}

	void Start()
	{
		m_rigidbody = AddComponent<component::RigidBodyComponent>();
		m_renderer = AddComponent<component::RenderComponent>();
		m_renderer->SetModel("healthCrate");
		m_transform->SetScale(0.2f);
		m_rigidbody->SetCollider(new btBoxShape(btVector3(3, 2.0, 3)));
		m_rigidbody->SetMass(4000);

		m_float[0] = Instantiate<ShipFloat>(math::Vector3(3,2,3), math::Quaternion::Identity, m_transform, m_scene);
		m_float[0]->SetMass(1000);

		m_float[1] = Instantiate<ShipFloat>(math::Vector3(3,2,-3), math::Quaternion::Identity, m_transform, m_scene);
		m_float[1]->SetMass(1000);

		m_float[2] = Instantiate<ShipFloat>(math::Vector3(-3,2,3), math::Quaternion::Identity, m_transform, m_scene);
		m_float[2]->SetMass(1000);

		m_float[3] = Instantiate<ShipFloat>(math::Vector3(-3,2,-3), math::Quaternion::Identity, m_transform, m_scene);
		m_float[3]->SetMass(1000);

		t = 5.0f;
	}
	void Update()
	{
		t -= ThomasTime::GetDeltaTime();
		if (t > 0)
			return;
		float waveHeight = 0;
		math::Vector3 bois;
		
		for (int i = 0; i < 4; i++)
		{
			waveHeight += m_float[i]->UpdateBoat(m_rigidbody);
			bois += m_float[i]->m_transform->GetPosition();
		}

		m_rigidbody->setDamping(0.9, 0.9);
		m_rigidbody->applyDamping(ThomasTime::GetDeltaTime());

		waveHeight /= 4;
		bois /= 4;

		if (bois.y > waveHeight + 0.5)
		{
			btVector3& v = m_rigidbody->getWorldTransform().getOrigin();
			float oldY = v.getY();
			float newY = waveHeight + 0.5;
			newY = oldY + ThomasTime::GetDeltaTime()*4.0 * (newY - oldY);
			v.setY(newY);
		}
	}


	void OnCollide(component::RigidBodyComponent::Collision collision)
	{
		if (collision.otherRigidbody->m_gameObject->GetType() == "Ship")
		{
			ShipStats::s_playerStats->RepairHealth(2);
			Destroy(this);
		}
	}

private:
	float t;
	component::RigidBodyComponent* m_rigidbody;
	component::RenderComponent* m_renderer;
	ShipFloat* m_float[4];

};