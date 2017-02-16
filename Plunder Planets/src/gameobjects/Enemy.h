#pragma once
#include <Thomas.h>
#include "Broadside.h"
#include "../AI/AI.h"

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

		m_renderer = AddComponent<component::RenderComponent>();
		m_sound = AddComponent<component::SoundComponent>();
		m_ai = AddComponent<AI>();

		/*
		m_broadSideLeft = Instantiate<Broadside>(math::Vector3(-3, 3, -0.8), math::Quaternion::CreateFromAxisAngle(math::Vector3(0, 1, 0), math::PI / 2), m_transform, m_scene);
		m_broadSideRight = Instantiate<Broadside>(math::Vector3(3, 3, -0.8), math::Quaternion::CreateFromAxisAngle(math::Vector3(0, 1, 0), math::PI * 2 / 3), m_transform, m_scene);
		*/

		m_renderer->SetModel("testModel0");

		m_initPosition = math::Vector3(100, -0.8f, 100);
		m_transform->SetRotation(thomas::math::PI, 0, 0);
		m_transform->SetPosition(m_initPosition);

		m_forwardSpeed = 0;
		m_acceleration = 9.5f;
		m_retardation = 6.5f;
		m_maxSpeed = 30.0f;
		m_rotation = 0.3f;
		m_turnDir = 0;

		m_searchRadius = 1000;
		m_attackRadius = 200;
		m_islandForward = false;
		m_islandLeft = false;
		m_islandRight = false;
	}

	void Move()
	{
		
		switch (m_ai->GetState())
		{
		case AI::Behavior::Attacking:
			Rotate();
			m_forwardSpeed += m_acceleration * Time::GetDeltaTime();
			break;
		case AI::Behavior::Searching:
			Rotate();
			m_forwardSpeed += m_acceleration * Time::GetDeltaTime();
			break;
		case AI::Behavior::Idle:
			m_forwardSpeed -= m_retardation * Time::GetDeltaTime();
			break;
		default:
			break;
		}

		m_forwardSpeed = std::fminf(m_forwardSpeed, m_maxSpeed);
		m_forwardSpeed = std::fmaxf(m_forwardSpeed, 0);

		m_transform->Translate(-m_transform->Forward() * m_forwardSpeed * Time::GetDeltaTime());
	}

	void Rotate()
	{
		float dir = m_newForwardVec.Dot(m_transform->Right());
		if (m_transform->Forward() != m_newForwardVec)
		{
			if (m_turnDir == 1)
				m_transform->Rotate(m_rotation * Time::GetDeltaTime(), 0, 0);
			else if (m_turnDir == -1)
				m_transform->Rotate(-m_rotation * Time::GetDeltaTime(), 0, 0);
		}
	}

	void FireCannons()
	{

	}

	void Update()
	{
		math::Vector3 pos = m_transform->GetPosition();
		m_ai->InsideRadius(m_searchRadius, m_transform->GetPosition(), m_newForwardVec);

		m_islandForward = m_ai->Collision(m_transform->GetPosition() + (m_transform->Forward() * 50));	//Check island front
		m_islandRight = m_ai->Collision(m_transform->GetPosition() + (m_transform->Right() * 40));	//Check island right
		m_islandLeft = m_ai->Collision(m_transform->GetPosition() - (m_transform->Right() * 40));	//Check island left

		pos = m_transform->GetPosition();

		m_turnDir = m_ai->TurnDir(m_transform->GetPosition(), m_transform->Forward(), m_transform->Right(), m_islandForward, m_islandRight, m_islandLeft);


		if (!m_firstFrame)
			Move();
		m_firstFrame = false;



	}

	void Destroy()
	{
	}

private:
	//Used for ship
	math::Vector3 m_initPosition;
	math::Vector3 m_newForwardVec;
	float m_forwardSpeed;
	float m_rotation;
	float m_acceleration;
	float m_retardation;
	float m_maxSpeed;
	float m_searchRadius;
	float m_attackRadius;
	float m_turnDir;

	bool m_islandForward;
	bool m_islandLeft;
	bool m_islandRight;

	//Components
	component::RenderComponent* m_renderer;
	component::SoundComponent* m_sound;
	AI* m_ai;

	//Objects
	Broadside* m_broadSideLeft;
	Broadside* m_broadSideRight;

	bool m_firstFrame;

};