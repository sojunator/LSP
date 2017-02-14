#pragma once
#include <Thomas.h>
#include "Broadside.h"
#include "TerrainObject.h"

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

				m_dt = 0;
			}

			void Move()
			{

			}

			void Rotate()
			{

			}

			void Update()
			{
				m_dt = Time::GetDeltaTime();

				

			}

		private:

		public:
			//Used for ship
			math::Vector3 m_initPosition;
			math::Vector3 m_forwardVec;
			math::Vector3 m_newForwardVec;
			float m_forwardSpeed;
			float m_newForward;
			float m_rotation;
			float m_acceleration;
			float m_retardation;
			float m_maxSpeed;

			//Behaviors

			float m_dt;

			//Components
			component::RenderComponent* m_renderer;
			component::SoundComponent* m_sound;
			//component::AI* m_ai;

			//Objects
			TerrainObject* m_terrainObject;
			Broadside* m_broadSideLeft;
			Broadside* m_broadSideRight;

		};
	}
}