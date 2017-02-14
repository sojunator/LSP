#pragma once
#include <Thomas.h>
#include "Broadside.h"
#include "TerrainObject.h"
#include "Ship.h"

namespace thomas
{
	namespace object
	{
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
				m_terrainObject = (TerrainObject*)Find("TerrainObject");
				m_ship = (Ship*)Find("Ship");

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

				m_escapeTime = 100;		//Should be 10 seconds
				m_escapeTimer = 0;

				m_searchRadius = 1000;
				m_dt = 0;
			}

			void Move()
			{
				if (math::Vector3::DistanceSquared(m_playerPos, m_transform->GetPosition()) < 100)
				{
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
				
			}

			void InsideRadius()
			{
				float distanceSquared = math::Vector3::DistanceSquared(m_playerPos, m_transform->GetPosition());
				if (distanceSquared <= (m_searchRadius * m_searchRadius))
				{
					m_escapeTimer = 0;
					m_newForwardVec = m_playerPos - m_transform->GetPosition();
					m_state = Attacking;
				}
				else if (m_state == Attacking)
				{
					m_lastKnownPos = m_playerPos;
					m_escapeTimer += m_dt;
					m_state = Searching;
				}
				else
				{
					m_escapeTimer += m_dt;
				}
			}

			void Escaped()
			{
				if (m_escapeTimer >= m_escapeTime)
					m_state = Idle;
			}

			void FireCannons()
			{

			}

			void Update()
			{
				m_dt = Time::GetDeltaTime();
				m_playerPos = m_ship->m_transform->GetPosition();
				InsideRadius();

				switch (m_state)
				{
				case Searching:
				{
					break;
				}
				case Idle:
				{
					break;
				}
				case Attacking:
				{
					break;
				}
				default:
					break;
				}
				

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

			float m_escapeTimer;
			float m_escapeTime;

			math::Vector3 m_playerPos;
			math::Vector3 m_lastKnownPos;

			//Behaviors
			enum Behavior
			{
				Searching,
				Idle,
				Attacking,
			};
			
			Behavior m_state = Idle;

			float m_dt;

			//Components
			component::RenderComponent* m_renderer;
			component::SoundComponent* m_sound;
			//component::AI* m_ai;

			//Objects
			TerrainObject* m_terrainObject;
			Broadside* m_broadSideLeft;
			Broadside* m_broadSideRight;
			Ship* m_ship;

		};
	}
}