
#pragma once

#include <Thomas.h>
#include <string>
#include "Broadside.h"


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

		thomas::graphics::Material* mat = thomas::graphics::Material::CreateMaterial("terrainMat", "terrainMaterial");
		m_islands = new thomas::Islands(20, mat, 1024, 1.0 / 16, 5000, 100);
		m_model = thomas::graphics::Model::CreateModel("Islands", m_islands->GetIslands(0));

		m_renderer->SetModel("Islands");

		m_transform->SetPosition(math::Vector3(0, -5.5, 0));

		//PlaceBalls();
	}

	void PlaceBalls()
	{
		for (int j = 0; j < 2; ++j)
			for (int i = 0; i < 10; i++)
			{
				m_broadsides.push_back(Instantiate<Broadside>(math::Vector3(m_islands->GetCenter(j).x, 5, m_islands->GetCenter(j).z), math::Quaternion::CreateFromAxisAngle(math::Vector3(0, 1, 0), 0), m_scene));
				m_broadsides.at(i + 10 * j)->m_transform->Rotate(math::Vector3((math::PI * 2 / 360) * 36 * i, 0, 0));
				m_broadsides.at(i + 10 * j)->m_transform->Translate(m_broadsides.at(i + 10 * j)->m_transform->Forward() * m_islands->GetCollisionRadius(j));
				m_broadsides.at(i + 10 * j)->m_transform->SetScale(5);
			}
	}

	void Update()
	{
	}

	float Plunder(math::Vector3 pos)
	{
		math::Vector3 center;
		float distance = 0;
		float treasure = 0;
		for (int i = 0; i < m_islands->GetNrOfIslands(); ++i)
		{
			center = m_islands->GetCenter(i);
			distance = math::Vector3::DistanceSquared(pos, center);
			if (distance <= m_islands->GetPlunderRadiusSquared(i) && m_islands->GetTreasure(i))
				treasure = m_islands->StealTreasure(i);
		}
		return treasure;
	}

	bool Collision(math::Vector3 pos)
	{
		math::Vector3 center;
		float distance = 0;
		if (!this)
			return true;
		for (int i = 0; i < m_islands->GetNrOfIslands(); i++)
		{
			center = m_islands->GetCenter(i);
			distance = math::Vector3::DistanceSquared(pos, center);
			if (distance <= m_islands->GetCollisionRadiusSquared(i))
				return true;
		}
		return false;
	}

private:
	thomas::Islands* m_islands;
	thomas::graphics::Model* m_model;

	std::vector<Broadside*> m_broadsides;

	component::RenderComponent* m_renderer;

};