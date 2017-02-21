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

	void Start()
	{
		m_renderer = AddComponent<component::RenderComponent>();
		m_shipObject = Find("Ship");

		thomas::graphics::Material* mat = thomas::graphics::Material::CreateMaterial("terrainMat", "terrainMaterial");
		m_islands = new thomas::Islands(20, mat, 1024, 1.0/16, 5000, 100);
		m_model = thomas::graphics::Model::CreateModel("Islands", m_islands->GetIslands(0));

		m_renderer->SetModel("Islands");

		m_transform->SetPosition(math::Vector3(0, -2.5, 0));


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
	math::Vector2 m_shipPos;
	object::GameObject* m_shipObject;
	thomas::Islands* m_islands;
	thomas::graphics::Model* m_model;

	component::RenderComponent* m_renderer;
};