#include "Islands.h"
#include "../../Plunder Planets/src/gameobjects/ShipStats.h"

namespace thomas
{
	Islands::Islands(int nrOfIslands, graphics::Material* m, int size, float detail, int mapSize)
	{
		std::srand(time(NULL));
		std::vector<thomas::utils::Plane::PlaneData> tempPlane;
		m_mapSize = mapSize;
		m_nrOfIslands = nrOfIslands;
		m_plunderRate = ShipStats::s_playerStats->GetPlunderSpeed();

		for (int i = 0; i < m_nrOfIslands; i++)
		{
			float min = std::sqrt(std::pow(size / 2, 2) + std::pow(size / 2, 2))*1.5;	//Now same, but will change when islands can be different sizes

			m_lostTreasureSinceLastEnemySpawn.push_back(0);
			m_size.push_back(size);
			m_minDistance.push_back(min);
			m_detail.push_back(detail);
			m_treasure.push_back(1000);
			m_totalTreasure.push_back(1000);
			m_plunderRadius.push_back(size*0.43);
			m_collisionRadius.push_back(size*0.33);
		}

		GeneratePos();
		for (int i = 0; i < m_nrOfIslands; i++)
		{
			tempPlane.push_back(thomas::utils::Plane::CreatePlane(size, detail));
			utils::HeightMap::ApplyHeightMap(size, detail, mapSize, tempPlane[i], math::Vector2(m_worldPosOffset[i].z, m_worldPosOffset[i].x));
			ApplyOffSet(i, tempPlane[i]);
		}
		GenerateMesh(tempPlane, m);
	}

	void Islands::GenerateMesh(std::vector<utils::Plane::PlaneData> tempPlane, graphics::Material* m)
	{
		std::vector<thomas::graphics::Mesh*> mesh;
		for (int i = 0; i < tempPlane.size(); i++)
		{
			mesh.push_back(new graphics::Mesh(tempPlane[i].verts, tempPlane[i].indices, "Islands", m));
			m_mesh.push_back(mesh);
			mesh.clear();
		}
	}

	void Islands::ApplyOffSet(int island, utils::Plane::PlaneData& tempPlanes)
	{
		for (unsigned int i = 0; i < tempPlanes.verts.size(); ++i)
		{
			tempPlanes.verts[i].position.x += m_worldPosOffset[island].x;
			tempPlanes.verts[i].position.z -= m_worldPosOffset[island].z;
		}
	}

	Islands::~Islands()
	{
		for (unsigned int i = 0; i < m_mesh.size(); ++i)
		{
			for (unsigned int j = 0; j < m_mesh[i].size(); ++j)
			{
				delete m_mesh[i][j];
			}
		}
	}

	std::vector<graphics::Mesh*> Islands::GetIslands(int island)
	{
		return m_mesh[island];
	}

	int Islands::GetPlunderRate()
	{
		return m_plunderRate;
	}

	int Islands::GetNrOfIslands()
	{
		return m_nrOfIslands;
	}

	int Islands::GetMapSize()
	{
		return m_mapSize;
	}

	int Islands::GetMinDistance(int island)
	{
		return m_minDistance[island];
	}

	math::Vector3 Islands::GetCenter(int island)
	{
		return m_islandCenterWorldPos[island];
	}

	math::Vector3 Islands::GetOffSet(int island)
	{
		return m_worldPosOffset[island];
	}

	float Islands::GetPlunderRadius(int island)
	{
		return m_plunderRadius[island];
	}

	float Islands::GetCollisionRadius(int island)
	{
		return m_collisionRadius[island];
	}

	float Islands::GetPlunderRadiusSquared(int island)
	{
		return m_plunderRadius[island] * m_plunderRadius[island];
	}

	float Islands::GetCollisionRadiusSquared(int island)
	{
		return m_collisionRadius[island] * m_collisionRadius[island];
	}

	float Islands::GetTreasure(int island)
	{
		return m_treasure[island];
	}

	float Islands::GetTreasureLostSinceLastEnemy(int island)
	{
		return m_lostTreasureSinceLastEnemySpawn[island];
	}

	void Islands::resetTreasureLost(int island)
	{
		m_lostTreasureSinceLastEnemySpawn[island] = 0;
	}


	int Islands::GetTotalTreasure(int island)
	{
		return m_totalTreasure[island];
	}



	int Islands::GetSize(int island)
	{
		return m_size[island];
	}

	int Islands::GetDetail(int island)
	{
		return m_detail[island];
	}

	float Islands::StealTreasure(int island)
	{
		float dt = ThomasTime::GetDeltaTime();
		if (m_treasure[island] < m_plunderRate*dt)
		{
			float temp = m_treasure[island];
			m_treasure[island] -= m_treasure[island];
			m_lostTreasureSinceLastEnemySpawn[island] += temp;
			return temp;
		}
		else
		{
			m_treasure[island] -= dt*m_plunderRate;
			m_lostTreasureSinceLastEnemySpawn[island] += dt*m_plunderRate;
			return dt*m_plunderRate;
		}
	}

	int Islands::GetSizeOFIsland(int island)
	{
		return m_size[island];
	}

	void Islands::ChangeHeightMapValues(std::vector<utils::Plane::PlaneData> &tempPlane)
	{
		for (int i = 0; i < m_nrOfIslands; i++)
		{
			for (int j = 0; j < tempPlane[j].verts.size(); j++)
			{
				if (tempPlane[i].verts[j].position.y < 5.0)
					tempPlane[i].verts[j].position.y = -20.0;
			}
		}
	}

	void Islands::GeneratePos()
	{
		const int MAX_ATTEMPTS = 1200;
		int attempt = 0;
		int addedIslands = 0;
		math::Vector3 tempOffset;

		tempOffset.x = rand() % m_mapSize - (m_mapSize / 2);
		tempOffset.y = 0;
		tempOffset.z = rand() % m_mapSize - (m_mapSize / 2);


		math::Vector3 tempCenter;
		tempCenter.x = tempOffset.x + m_size[0] / 2;
		tempCenter.y = 0;
		tempCenter.z = -tempOffset.z - m_size[0] / 2;

		m_worldPosOffset.push_back(tempOffset);
		m_islandCenterWorldPos.push_back(tempCenter);
		addedIslands++;

		std::vector<float> distance;
		for (int i = 0; i < m_nrOfIslands; i++)
		{
			bool foundPos = false;
			while (!foundPos && attempt != MAX_ATTEMPTS)
			{
				tempOffset.x = rand() % m_mapSize - (m_mapSize / 2);
				tempOffset.y = 0;
				tempOffset.z = rand() % m_mapSize - (m_mapSize / 2);

				tempCenter.x = tempOffset.x + m_size[0] / 2;
				tempCenter.y = 0;
				tempCenter.z = -tempOffset.z - m_size[0] / 2;

				for (int j = 0; j < m_islandCenterWorldPos.size(); ++j)
				{
					float tempDistance = (m_islandCenterWorldPos[j] - tempCenter).Length();
					distance.push_back(tempDistance);
				}

				bool tooSmall = false;

				for (int j = 0; j < distance.size(); j++)
				{
					if (distance[j] <= m_minDistance[i])
						tooSmall = true;
				}

				attempt++;

				if (!tooSmall)
				{
					attempt = 0;
					foundPos = true;
					m_worldPosOffset.push_back(tempOffset);
					m_islandCenterWorldPos.push_back(tempCenter);
					addedIslands++;
				}

				distance.clear();
			}

		}

		m_worldPosOffset.erase(m_worldPosOffset.begin());
		m_islandCenterWorldPos.erase(m_islandCenterWorldPos.begin());
		m_nrOfIslands = --addedIslands;
	}
}