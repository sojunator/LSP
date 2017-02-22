#pragma once
#include <Thomas.h>
#include "Broadside.h"
#include "../AI/AI.h"
#include "../../THOMAS/src/utils/DebugTools.h"

using namespace thomas;
using namespace object;

class Enemy : public GameObject
{
private:

public:
	Enemy() : GameObject("Enemy")
	{
	}

	void Start()
	{
		m_firstFrame = true;
		m_mass = 500000;
		m_searchRadius = 1000;
		m_attackRadius = 200;
		m_turnDir = 0;
		m_shootDir = 0;
		m_newForwardVec = math::Vector3::Zero;

		m_islandForward = false;
		m_islandLeft = false;
		m_islandRight = false;

		m_soundDelay = 5;
		m_soundDelayLeft = 5;

		//Front
		m_floats[0] = Instantiate<ShipFloat>(math::Vector3(1.5, 0, 8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[1] = Instantiate<ShipFloat>(math::Vector3(-1.5, 0, 8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[0]->SetMass(0.10*m_mass);
		m_floats[1]->SetMass(0.10*m_mass);
		//front middle
		m_floats[2] = Instantiate<ShipFloat>(math::Vector3(3, 0, 5), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[3] = Instantiate<ShipFloat>(math::Vector3(-3, 0, 5), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[2]->SetMass(0.12*m_mass);
		m_floats[3]->SetMass(0.12*m_mass);
		//back middle
		m_floats[4] = Instantiate<ShipFloat>(math::Vector3(3, 0, -1), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[5] = Instantiate<ShipFloat>(math::Vector3(-3, 0, -1), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[4]->SetMass(0.13*m_mass);
		m_floats[5]->SetMass(0.13*m_mass);
		//back
		m_floats[6] = Instantiate<ShipFloat>(math::Vector3(2.5, 0, -8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[7] = Instantiate<ShipFloat>(math::Vector3(-2.5, 0, -8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[6]->SetMass(0.15*m_mass);
		m_floats[7]->SetMass(0.15*m_mass);

		//stabilizers front
		m_floats[8] = Instantiate<ShipFloat>(math::Vector3(2.5, 5, 8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[9] = Instantiate<ShipFloat>(math::Vector3(-2.5, 5, 8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[8]->SetMass(0.5*m_mass);
		m_floats[9]->SetMass(0.5*m_mass);
		//stabilizers back
		m_floats[10] = Instantiate<ShipFloat>(math::Vector3(2.5, 5, -8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[11] = Instantiate<ShipFloat>(math::Vector3(-2.5, 5, -8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[10]->SetMass(0.5*m_mass);
		m_floats[11]->SetMass(0.5*m_mass);

		m_transform->SetPosition(0, 0.5, 0);

		m_renderer = AddComponent<component::RenderComponent>();
		m_sound = AddComponent<component::SoundComponent>();
		m_ai = AddComponent<AI>();
		m_rigidBody = AddComponent<component::RigidBodyComponent>();

		m_broadSideLeft = Instantiate<Broadside>(math::Vector3(-5.5, 6, -2.8), math::Quaternion::CreateFromAxisAngle(math::Vector3(0, 1, 0), math::DegreesToradians(90)), m_transform, m_scene);
		m_broadSideRight = Instantiate<Broadside>(math::Vector3(5.5, 6, -2.8), math::Quaternion::CreateFromAxisAngle(math::Vector3(0, 1, 0), math::DegreesToradians(270)), m_transform, m_scene);

		m_broadSideRight->CreateCanons();
		m_broadSideLeft->CreateCanons();


		m_renderer->SetModel("testModel0");
		m_moving = false;


		//Rigidbody init
		m_rigidBody->SetMass(m_mass);
		m_rigidBody->SetCollider(new btBoxShape(btVector3(3, 12, 8)));
		m_rigidBody->setSleepingThresholds(0.2, 0.5);

		//Sound


		//Movement
		m_speed = 600;
		utils::DebugTools::AddFloat(m_speed, "EnemySpeed");
		m_turnSpeed = 150;
		utils::DebugTools::AddFloat(m_turnSpeed, "enemyTurnSpeed");

		thomas::utils::DebugTools::AddInteger(m_shootDir, "Shoot Dir");
		//utils::DebugTools::AddBool(m_islandForward, "Island F");
		//utils::DebugTools::AddBool(m_islandRight, "Island R");
		//utils::DebugTools::AddBool(m_islandLeft, "Island L");
	}

	void Move(float dt)
	{
		math::Vector3 forward = m_transform->Forward();
		forward.y = 0;		//Remove y so no flying
		m_moving = true;
		m_shootDir = m_ai->FireCannons(m_transform->GetPosition(), -m_transform->Right());

		switch (m_ai->GetState())
		{
		case AI::Behavior::Attacking:
			FireCannons();
			m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * m_speed * dt * m_rigidBody->GetMass()));
			Rotate(dt);
			break;
		case AI::Behavior::Firing:
			FireCannons();
			m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * m_speed * dt * m_rigidBody->GetMass()));
			Rotate(dt);
			break;
		case AI::Behavior::Searching:
			m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * m_speed * dt * m_rigidBody->GetMass()));
			Rotate(dt);
			break;
		case AI::Behavior::Idle:
			m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * m_speed * dt * m_rigidBody->GetMass()));
			Rotate(dt);
			break;
		default:
			break;
		}
	}

	void Rotate(float dt)
	{
		math::Vector3 right = m_transform->Right();
		right.y = 0;		//Remove y so no flying
		m_rigidBody->activate();



		float dir = m_newForwardVec.Dot(m_transform->Right());
		if (m_transform->Forward() != m_newForwardVec)
		{
			if (m_turnDir == 1)
				m_rigidBody->applyTorque(btVector3(0, m_turnSpeed * dt * m_rigidBody->GetMass(), 0));
			else if (m_turnDir == -1)
				m_rigidBody->applyTorque(btVector3(0, -m_turnSpeed * dt * m_rigidBody->GetMass(), 0));
		}
	}

	void FireCannons()
	{
		if (m_shootDir == 1)
			m_broadSideLeft->Fire();
		else if (m_shootDir == -1)
			m_broadSideLeft->Fire();
	}

	void Update()
	{
		float const dt = Time::GetDeltaTime();

		m_moving = false;

		m_ai->Escape();
		m_ai->InsideRadius(m_searchRadius, m_transform->GetPosition(), m_newForwardVec);
		m_ai->InsideAttackRadius(m_attackRadius, m_transform->GetPosition(), m_newForwardVec);

		m_islandForward = m_ai->Collision(m_transform->GetPosition() + (-m_transform->Forward() * 60));	//Check island front
		m_islandRight = m_ai->Collision(m_transform->GetPosition() + (-m_transform->Right() * 30));	//Check island right
		m_islandLeft = m_ai->Collision(m_transform->GetPosition() - (-m_transform->Right() * 30));	//Check island left

		m_turnDir = m_ai->TurnDir(m_transform->GetPosition(), -m_transform->Forward(), -m_transform->Right(), m_islandForward, m_islandRight, m_islandLeft);

		if (!m_firstFrame)
			Move(dt);
		m_firstFrame = false;

		bool inWater = false;

		for (int i = 0; i < 12; i++)
		{
			bool wTemp = m_floats[i]->UpdateBoat(m_rigidBody, m_moving);
			if (wTemp)
				inWater = true;
		}

		if (m_moving)
			m_rigidBody->setDamping(0.5, 0.5);
		m_rigidBody->applyDamping(dt);

	}

	void Destroy()
	{
	}

private:
	//Objects
	ShipFloat* m_floats[12];
	Broadside* m_broadSideRight;
	Broadside* m_broadSideLeft;
	Broadside* m_broadSideRightCannonball;
	Broadside* m_broadSideLeftCannonball;
	Broadside* m_broadSideFront;

	//Components
	component::RenderComponent* m_renderer;
	component::SoundComponent* m_sound;
	component::RigidBodyComponent* m_rigidBody;
	AI* m_ai;

	//Ship
	bool m_moving;
	float m_mass;
	float m_speed;
	float m_turnSpeed;
	int m_turnDir;
	int m_shootDir;

	math::Vector3 m_newForwardVec;

	float m_searchRadius;
	float m_attackRadius;

	bool m_islandForward;
	bool m_islandLeft;
	bool m_islandRight;

	//Sound
	float m_soundDelay;
	float m_soundDelayLeft;


	bool m_firstFrame;
};
