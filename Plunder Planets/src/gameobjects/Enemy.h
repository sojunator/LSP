#pragma once
#include <Thomas.h>
#include "Broadside.h"
#include "TerrainObject.h"
#include "Ship.h"
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
		m_renderer = AddComponent<component::RenderComponent>();
		m_sound = AddComponent<component::SoundComponent>();
		m_ai = new AI;

		/*
		m_broadSideLeft = Instantiate<Broadside>(math::Vector3(-3, 3, -0.8), math::Quaternion::CreateFromAxisAngle(math::Vector3(0, 1, 0), math::PI / 2), m_transform, m_scene);
		m_broadSideRight = Instantiate<Broadside>(math::Vector3(3, 3, -0.8), math::Quaternion::CreateFromAxisAngle(math::Vector3(0, 1, 0), math::PI * 2 / 3), m_transform, m_scene);
		*/

		m_initPosition = math::Vector3(0, -0.8f, 0);
		m_transform->SetRotation(thomas::math::PI, 0, 0);
		m_transform->SetPosition(m_initPosition);

		m_forwardSpeed = 0;
		m_acceleration = 9.5f;
		m_retardation = 6.5f;
		m_maxSpeed = 30.0f;
		m_rotation = 0.3f;

		m_searchRadius = 1000;
	}

	void Move()
	{
		if (math::Vector3::DistanceSquared(m_playerPos, m_transform->GetPosition()) < 100)	//Close to player
		{
			m_newForwardVec = m_ship->m_transform->Forward();
			m_forwardSpeed -= m_retardation * m_dt;
			m_forwardSpeed = std::fmaxf(m_forwardSpeed, 0);
		}
		else
		{
			m_forwardSpeed += m_acceleration * m_dt;
			m_forwardSpeed = std::fminf(m_forwardSpeed, m_maxSpeed);
		}
	}

	void Rotate()
	{
		float turnDir = m_transform->Right().Dot(m_newForwardVec);
		if (turnDir > 0)	//Check with RightVec
			m_transform->Rotate(m_rotation * m_dt, 0, 0);
		else if (turnDir < 0)
			m_transform->Rotate(-m_rotation * m_dt, 0, 0);
		else
		{
			turnDir = m_transform->Forward().Dot(m_newForwardVec);
			if (turnDir < 0)
				m_transform->Rotate(m_rotation * m_dt, 0, 0);
		}
	}

	void Escaped()
	{
		//Check if the player is behind a island, then also escaped. Move to last known playerPos
		if (m_escapeTimer >= m_escapeTime)
			m_state = Idle;
	}

	void FireCannons()
	{

	}

	void Update()
	{
		m_ai->InsideRadius(m_searchRadius, m_transform->GetPosition(), m_newForwardVec);
		int turnDir = 0;
		if (m_ai->CheckInFront(m_transform->GetPosition() + (m_transform->Forward() * 50)))	//Check for island in front
		{
			turnDir = m_ai->TurnDir;
			//Turn
		}

		if (m_ai->CheckSide(m_transform->GetPosition() + (m_transform->Right() * 40)))		//Check for island to the right
		{
			//No need to turn
		}

		if (m_ai->CheckSide(m_transform->GetPosition() - (m_transform->Right() * 40)))		//Check for island to the left
		{
			//No need to turn
		}

		Escaped();




	}

	void Destroy()
	{
		delete m_ai;
	}

private:
	//Used for ship
	math::Vector3 m_initPosition;
	math::Vector3 m_newForwardVec;
	float m_forwardSpeed;
	float m_newForward;
	float m_rotation;
	float m_acceleration;
	float m_retardation;
	float m_maxSpeed;
	float m_searchRadius;

	//Components
	component::RenderComponent* m_renderer;
	component::SoundComponent* m_sound;

	AI* m_ai;

	//Objects
	Broadside* m_broadSideLeft;
	Broadside* m_broadSideRight;

};