#pragma once

#include "Thomas.h"
#include <string>
#include "../BasicEnemy.h"
#include "IslandObject.h"

class IslandManager
{

private:

public:
	IslandManager(Scene* scene)
	{
		thomas::graphics::Material* mat = thomas::graphics::Material::CreateMaterial("terrainMat", "terrainMaterial");
		m_islands = new thomas::Islands(30, mat, 512, 2048, 1 / 8.f, 4096);
		int nrOfIslands = m_islands->GetNrOfIslands();
		for (int i = 0; i < nrOfIslands; i++)
		{
			math::Vector3 pos = m_islands->GetCenter(i);
			math::Vector3 off = m_islands->GetOffSet(i);
			thomas::graphics::Model::CreateModel("Island-" + std::to_string(i), m_islands->GetIslands(i));
			m_islandObjects.push_back(thomas::object::GameObject::Instantiate<IslandObject>(m_islands->GetCenter(i), thomas::math::Quaternion::Identity, scene));
			m_islandObjects[i]->SetModel(i);
			m_islandObjects[i]->PlaceRigidBody(m_islands->GetCollisionRadius(i), m_islands->GetCenter(i));
		}
	}

	~IslandManager()
	{
		delete m_islands;
	}

	void Start()
	{
	}

	void Update()
	{
	}

	float Plunder(math::Vector3 pos)
	{
		CheckForDeadIslands();
		bool gotLoot = false;
		math::Vector3 center;
		float distance = 0;
		float treasure = 0;
		for (int i = 0; i < m_islands->GetNrOfIslands(); ++i)
		{
			if (m_islandObjects[i] != nullptr)	//If the island has been deleted
			{
				center = m_islands->GetCenter(i);
				distance = math::Vector3::DistanceSquared(pos, center);
				if (distance <= m_islands->GetPlunderRadiusSquared(i) && m_islands->GetTreasure(i))
				{
					treasure = m_islands->StealTreasure(i);
					gotLoot = true;
					if (m_islands->GetTreasureLostSinceLastEnemy(i) > 500)
					{
						/*m_islands->resetTreasureLost(i);
						float r = ((double)rand() / (RAND_MAX)) + 1;
						float rads = r * math::PI * 2;
						math::Vector2 randDir = math::Vector2(cosf(rads), sinf(rads));
						randDir.Normalize();
						math::Vector3 spawnPos = m_islands->GetCenter(i) + (m_islands->GetCollisionRadius(i) + 30)*math::Vector3(randDir.x, 0, randDir.y);
						Instantiate<BasicEnemy>(spawnPos, math::Quaternion::Identity, Scene::GetCurrentScene());*/
					}
				}
				else if (!m_islands->GetTreasure(i))
				{
					m_islandObjects[i]->SinkIsland();
					//m_islandObjects.erase(i);
				}
				m_islandObjects[i]->Looting(gotLoot);
			}
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


	math::Vector3 GetRandomPosAroundIsland(float offset)
	{

		float randIsland = (int)((((double)rand() / (RAND_MAX))) * m_islandObjects.size());
		
		while (!m_islandObjects[randIsland])
		{
			randIsland = (int)((((double)rand() / (RAND_MAX))) * m_islandObjects.size());
		}


		float r = ((double)rand() / (RAND_MAX));
		float rads = r * math::PI * 2;
		math::Vector2 randDir = math::Vector2(cosf(rads), sinf(rads));
		randDir.Normalize();
		math::Vector3 pos = m_islands->GetCenter(randIsland) + (m_islands->GetCollisionRadius(randIsland) + offset)*math::Vector3(randDir.x, 0, randDir.y);
		return pos;
	}

	void CheckForDeadIslands()
	{
		for (int i = 0; i < m_islandObjects.size(); i++)
		{
			if (m_islandObjects[i] != nullptr)
			{
				if (m_islandObjects[i]->CheckDestory())
				{
					delete m_islandObjects[i];
					m_islandObjects[i] = nullptr;
				}
			}
		}
	}

private:
	thomas::Islands* m_islands;
	std::vector<IslandObject*> m_islandObjects;
};