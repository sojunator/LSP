#pragma once
#pragma once
#include <Thomas.h>
#include <string>
#include "Ship.h"

#include "CameraObject.h"

class TerrainObject : public GameObject
{

private:

public:
	TerrainObject() : GameObject("TerrainObject")
	{

	}
	~TerrainObject()
	{
		delete m_islands;
		delete m_model;
		delete m_renderer;
		delete m_shipObject;
	}

	void Start()
	{
		m_renderer = AddComponent<component::RenderComponent>();
		m_shipObject = (Ship*)Find("Ship");

		thomas::graphics::Material* mat = thomas::graphics::Material::CreateMaterial("terrainMat", "terrainMaterial");
		m_islands = new thomas::Islands(3, mat, 1024 / 16, 1, 1024/2, 100);
		m_model = thomas::graphics::Model::CreateModel("Plane-1", m_islands->GetIslands(0));
		m_shipPos = math::Vector2(m_shipObject->m_transform->GetPosition().x, m_shipObject->m_transform->GetPosition().z);

		m_renderer->SetModel("Plane-1");

		m_transform->SetPosition(math::Vector3(0, -1, 0));


	}


	void Update()
	{
		m_shipPos = math::Vector2(m_shipObject->m_transform->GetPosition().x, m_shipObject->m_transform->GetPosition().z);
		math::Vector2 center;
		float distance;
		float treasure;
		for (int i = 0; i < m_islands->GetNrOfIslands(); ++i)
		{
			center = m_islands->GetCenter(i);
			distance = math::Vector2::DistanceSquared(m_shipPos, center);
			if (distance <= m_islands->GetRadiusSquared(i) && m_islands->GetTreasure(i))
			{
				treasure = m_islands->StealTreasure(i);
				m_shipObject->UpdateTreasure(treasure);
			}
		}
	}

private:
	math::Vector2 m_shipPos;

	thomas::Islands* m_islands;
	thomas::graphics::Model* m_model;

	component::RenderComponent* m_renderer;
	Ship* m_shipObject;
};