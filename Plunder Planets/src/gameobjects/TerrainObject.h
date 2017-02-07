#pragma once
#pragma once
#include <Thomas.h>
#include <string>

#include "CameraObject.h"

class TerrainObject : public GameObject
{

private:

public:
	TerrainObject() : GameObject("TerrainObject")
	{
		m_renderer = AddComponent<component::RenderComponent>();
		m_shipObject = Find("Ship");
		m_insideLastCheck = false;
		m_checkedIsland = -1;
	}

	bool Start()
	{
		thomas::graphics::Material* mat = thomas::graphics::Material::CreateMaterial("terrainMat", "terrainMaterial");
		m_islands = new thomas::Islands(1, mat, 1024 / 8, 0.125, 1024 / 8, 30);
		m_model = thomas::graphics::Model::CreateModel("Plane-1", m_islands->GetIslands(0));
		m_shipPos = math::Vector2(m_shipObject->m_transform->GetPosition().x, m_shipObject->m_transform->GetPosition().z);

		m_renderer->SetModel("Plane-1");

		m_cameraObject = Find("CameraObject");

		/*m_cameraObject->m_transform->SetPosition(math::Vector3(0, 0, 50));*/
		m_transform->SetPosition(math::Vector3(0, -1, 0));


		return true;
	}


	void Update()
	{
		m_shipPos = m_shipPos = math::Vector2(m_shipObject->m_transform->GetPosition().x, m_shipObject->m_transform->GetPosition().z);
		math::Vector2 center;
		float distance;
		float treasure;
		if (!m_insideLastCheck || m_insideLastCheck && m_checkedSquaredRadius > math::Vector2::DistanceSquared(m_shipPos, m_islands->GetCenter(m_checkedIsland)))
		{
			for (int i = 0; i < m_islands->GetNrOfIslands(); ++i)
			{
				center = m_islands->GetCenter(i);
				distance = math::Vector2::DistanceSquared(m_shipPos, center);
				if (distance <= m_islands->GetRadiusSquared(i))
				{
					treasure = m_islands->StealTreasure(i);
					LOG(m_islands->GetTreasure(i));
					/*
					Can plunder
					m_ship->UpdateTreasure(treasure)
					*/
					m_insideLastCheck = true;
					m_checkedIsland = i;
					m_checkedCenter = center;
					m_checkedSquaredRadius = m_islands->GetRadiusSquared(i);
					break;
				}
				else
				{
					m_insideLastCheck = false;
				}
			}
		}
		else
		{
			treasure = m_islands->StealTreasure(m_checkedIsland);
			LOG(m_islands->GetTreasure(m_checkedIsland));
			/*
			Can plunder
			m_ship->UpdateTreasure(treasure)
			*/
		}
	}

private:
	math::Vector2 m_shipPos;
	bool m_insideLastCheck;
	int m_checkedIsland;
	float m_checkedSquaredRadius;
	math::Vector2 m_checkedCenter;

	thomas::Islands* m_islands;
	thomas::graphics::Model* m_model;

	component::RenderComponent* m_renderer;
	object::GameObject* m_cameraObject;
	object::GameObject* m_shipObject;
};