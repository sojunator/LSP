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
	}

	~TerrainObject()
	{
		delete m_islands;
		delete m_model;
		delete m_renderer;
	}

	void Start()
	{
		m_renderer = AddComponent<component::RenderComponent>();

		thomas::graphics::Material* mat = thomas::graphics::Material::CreateMaterial("terrainMat", "terrainMaterial");
		m_islands = new thomas::Islands(3, mat, 1024 / 4, 1, 1024, 100);
		m_model = thomas::graphics::Model::CreateModel("Plane-1", m_islands->GetIslands(0));

		m_renderer->SetModel("Plane-1");

		m_transform->SetPosition(math::Vector3(0, -2, 0));


	}


	void Update()
	{
	}

	float Plunder(math::Vector2 pos)
	{
		math::Vector2 center;
		float distance = 0;
		float treasure = 0;
		for (int i = 0; i < m_islands->GetNrOfIslands(); ++i)
		{
			center = m_islands->GetCenter(i);
			distance = math::Vector2::DistanceSquared(pos, center);
			if (distance <= m_islands->GetPlunderRadiusSquared(i) && m_islands->GetTreasure(i))
				treasure = m_islands->StealTreasure(i);
		}
		return treasure;
	}

	bool Collision(math::Vector2 pos)
	{
		math::Vector2 center;
		float distance = 0;
		if (!this)
			return true;
		for (int i = 0; i < m_islands->GetNrOfIslands(); i++)
		{
			center = m_islands->GetCenter(i);
			distance = math::Vector2::DistanceSquared(pos, center);
			if (distance <= m_islands->GetCollisionRadiusSquared(i))
				return true;
		}
		return false;
	}

private:
	thomas::Islands* m_islands;
	thomas::graphics::Model* m_model;

	component::RenderComponent* m_renderer;
};