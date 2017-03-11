#pragma once

#include "Thomas.h"
#include "CameraObject.h"
#include "../scenes/UpgradeScene.h"
using namespace thomas;
using namespace object;
class Wormhole : public GameObject
{

private:

public:
	Wormhole() : GameObject("Wormhole")
	{

	}

	void OnEnable()
	{
		if (m_wormhole)
		{
			m_wormholeParticles->StartEmitting();
			m_wormhole->StartEmitting();
		}
			
	}

	void OnDisable()
	{
		m_wormholeParticles->StopEmitting();
		m_wormhole->StopEmitting();
	}

	void Start()
	{
		m_wormhole = AddComponent<component::ParticleEmitterComponent>();
		m_wormholeParticles = AddComponent<component::ParticleEmitterComponent>();

		m_wormhole->SetTexture("../res/textures/wormhole.png");
		m_wormhole->SetRotationSpeed(math::DegreesToRadians(180));
		m_wormhole->SetLifeTime(2);
		m_wormhole->SetLooping(true);
		m_wormhole->SetDelay(0);
		m_wormhole->SetEmissionRate(1.0f/2.0f);
		m_wormhole->SetSpeed(0);
		m_wormhole->SetEndSize(50);
	//	SetActive(false);
		m_spawned = false;
		m_spawning = true;
		m_time = 0;

		m_wormholeParticles->SetLooping(true);
		//m_wormholeParticles->SetDirection(0, 0, 1);
		m_wormholeParticles->SetSpread(180);
		m_wormholeParticles->SetSpeed(20, 50);
		m_wormholeParticles->SetEndSpeed(200);
		m_wormholeParticles->SetRotationSpeed(11);
		m_wormholeParticles->SetLifeTime(1.5, 1.5);
		m_wormholeParticles->SetDelay(0);
		m_wormholeParticles->SetSize(1, 2);
		m_wormholeParticles->SetEmissionRate(500);
		m_wormholeParticles->SetEndSize(0);
		m_wormholeParticles->SetRadius(70);
		m_wormholeParticles->SetEndColor(math::Color(0, 1, 0, 1));
		m_wormholeParticles->SpawnAtSphereEdge(true);
		//m_wormholeParticles->AddToDebugMenu();

		m_wormholeParticles->SetTexture("../res/textures/wormholeParticles.png");
		
		//m_wormhole->StartEmitting();
		m_camera = (CameraObject*)Find("CameraObject");
		m_endLevel = false;
		m_endSceneTimeLeft = 2.0f;
	}


	void StartLevel()
	{
		m_time += ThomasTime::GetDeltaTime();
		if (!m_spawned)
		{	
			m_camera->m_transform->SetPosition(m_transform->GetPosition() + math::Vector3(200, 20, 0));
			m_camera->m_transform->LookAt(m_transform->GetPosition());
		}

		if (m_spawning && m_time > 4.0f)
		{
			m_wormhole->StartEmitting();


			if (m_time > 5.5f)
			{
				m_wormhole->SetSize(50);
				m_wormhole->SetRotationSpeed(math::DegreesToRadians(20));
				m_wormhole->SetLifeTime(18);
				m_wormhole->SetEmissionRate(1.0f / 18.0f);
				m_wormholeParticles->StartEmitting();
				m_spawned = true;
				m_spawning = false;
			}
		}

		if (m_spawned && !m_ship && m_time > 7.0f)
		{
			m_ship = Instantiate<Ship>(m_transform->GetPosition(), math::Quaternion::Identity, m_scene);
			math::Vector3 shipForward = -m_ship->m_transform->Forward();
			math::Vector3 shipUp = m_ship->m_transform->Up();
			m_ship->GetComponent<component::RigidBodyComponent>()->applyCentralImpulse((*(btVector3*)&shipForward * 100 + *(btVector3*)&shipUp * 500) * m_ship->GetComponent<component::RigidBodyComponent>()->GetMass());
		}

		if (m_ship && m_ship->m_startUpSequence)
			m_camera->m_transform->LookAt(m_ship->m_transform->GetPosition());
		else if (m_ship && !m_ship->m_startUpSequence)
		{
			Destroy(this);
		}
	}


	void EndLevel()
	{
		m_time += ThomasTime::GetActualDeltaTime();
		

		if (m_time < 5.0)
		{	
			Input::Vibrate(1, 1);
			m_camera->m_transform->LookAt(m_transform->GetPosition());
		}

		if (m_spawning)
		{
			m_wormhole->StartEmitting();
			if (m_time > 2.0f)
			{
				m_wormhole->SetSize(50);
				m_wormhole->SetRotationSpeed(math::DegreesToRadians(20));
				m_wormhole->SetLifeTime(18);
				m_wormhole->SetEmissionRate(1.0f / 18.0f);
				m_wormholeParticles->StartEmitting();
				m_rigidBody = AddComponent<component::RigidBodyComponent>();
				m_rigidBody->setCollisionShape(new btBoxShape(btVector3(45.0f, 45.0f, 0.0f)));
				m_rigidBody->SetKinematic(true);
				m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
				m_spawned = true;
				m_spawning = false;
			}
		}
	}

	void Update()
	{
		if (m_endLevel)
			EndLevel();
		else
			StartLevel();


		if (m_hasEnteredWormhole)
		{
			
			if (m_endSceneTimeLeft > 1.0)
				m_endSceneTimeLeft -= ThomasTime::GetActualDeltaTime()*0.8;
			else
				m_endSceneTimeLeft -= ThomasTime::GetActualDeltaTime();
			
			float fov = 50 + (1 - m_endSceneTimeLeft/2.0) * (170 - 50);
			((CameraObject*)Find("CameraObject"))->GetComponent<component::Camera>()->SetFov(fov);

			if(m_endSceneTimeLeft <= 0)
				Scene::LoadScene<UpgradeScene>();
		}
	}

	void OnCollision(component::RigidBodyComponent::Collision collision)
	{
		if (collision.otherRigidbody->m_gameObject->GetType() == "Ship")
		{
			m_hasEnteredWormhole = true;
			ThomasTime::SetTimescale(0.0f);
		}
	}

	void SetEndLevel(bool state)
	{
		m_endLevel = state;
	}

private:
	bool m_hasEnteredWormhole;
	float m_endSceneTimeLeft;
	bool m_endLevel;
	bool m_spawned;
	bool m_spawning;
	float m_endSize;
	float m_time;
	Ship* m_ship;
	CameraObject* m_camera;
	component::ParticleEmitterComponent* m_wormhole;
	component::ParticleEmitterComponent* m_wormholeParticles;
	component::RigidBodyComponent*		 m_rigidBody;
};