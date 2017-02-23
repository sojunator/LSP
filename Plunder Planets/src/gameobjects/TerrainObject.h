
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
		m_islands = new thomas::Islands(20, mat, 1024, 1/8.f, 4096, 1024);
		m_model = thomas::graphics::Model::CreateModel("Islands", m_islands->GetIslands(0));

		m_renderer->SetModel("Islands");

		m_transform->SetPosition(math::Vector3(0, -5.5, 0));

		PlaceRigidBody();
	}

	void PlaceRigidBody()
	{
		for (int i = 0; i < m_islands->GetNrOfIslands(); ++i)
		{
			m_rigidBodyVec.push_back(AddComponent<component::RigidBodyComponent>());
			m_rigidBodyVec[i]->SetMass(0);
			m_rigidBodyVec[i]->SetCollider(new btSphereShape(m_islands->GetCollisionRadius(i)));
			m_rigidBodyVec[i]->setWorldTransform(btTransform(btQuaternion(), btVector3(m_islands->GetCenter(i).x, 0, m_islands->GetCenter(i).z)));
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

	//std::vector<Broadside*> m_broadsides;
	
	std::vector<component::RigidBodyComponent*> m_rigidBodyVec;
	component::RenderComponent* m_renderer;

};