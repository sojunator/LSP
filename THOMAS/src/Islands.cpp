#include "Islands.h"
#include "../../Plunder Planets/src/gameobjects/ShipStats.h"

namespace thomas
{
	Islands::Islands(int nrOfIslands, graphics::Material* m, int minSize, int maxSize, float detail, int mapSize)
	{
		std::srand(time(NULL));
		std::vector<thomas::utils::Plane::PlaneData> tempPlane;
		m_mapSize = mapSize;
		m_nrOfIslands = nrOfIslands;
		m_plunderRate = ShipStats::s_playerStats->GetPlunderSpeed();

		for (int i = 0; i < m_nrOfIslands; i++)
		{
			int randNumber = rand() % (maxSize - minSize) + minSize;
			float islandSize = std::round(randNumber * detail) / detail;	//Generates a size that is divisible by "detail". This ensures that the islands don't have holes in them.
			float powIsland = std::pow(islandSize / 2, 2);
			float min = std::sqrt(powIsland + powIsland) + 512;		//Depends on size of island

			float treasure = rand() % 800 + islandSize;

			m_lostTreasureSinceLastEnemySpawn.push_back(0);
			m_size.push_back(islandSize);
			m_minDistance.push_back(min);
			m_detail.push_back(detail);
			m_treasure.push_back(islandSize * 0.35);
			m_totalTreasure.push_back(treasure);
			m_collisionRadius.push_back(islandSize * 0.33);
			m_plunderRadius.push_back(m_collisionRadius[i] + 100);
		}

		GeneratePos();
		for (int i = 0; i < m_nrOfIslands; i++)
		{
			tempPlane.push_back(thomas::utils::Plane::CreatePlane(m_size[i], detail));
			utils::HeightMap::ApplyHeightMap(m_size[i], detail, mapSize, tempPlane[i], math::Vector2(m_worldPosOffset[i].x, m_worldPosOffset[i].z));
			MoveCenterFromCornerToCenter(i, tempPlane[i]);
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

	void Islands::MoveCenterFromCornerToCenter(int island, utils::Plane::PlaneData& tempPlanes)
	{
		for (unsigned int i = 0; i < tempPlanes.verts.size(); ++i)
		{
			tempPlanes.verts[i].position.x -= m_size[island] / 2;
			tempPlanes.verts[i].position.z += m_size[island] / 2;
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

	void Islands::GeneratePos()
	{
		const int MAX_ATTEMPTS = 1200;
		int attempt = 0;
		int addedIslands = 0;
		math::Vector3 tempOffset;

		tempOffset.x = m_mapSize / 2;			//Should be +mapSize / 2. So that we can't spawn in an island
		tempOffset.y = 0;
		tempOffset.z = -m_mapSize / 2;			//Should be -mapSize / 2. So that we can't spawn in an island


		math::Vector3 tempCenter;
		tempCenter.x = 0;
		tempCenter.y = 0;
		tempCenter.z = 0;

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

				tempCenter.x = tempOffset.x + m_size[i] / 2;
				tempCenter.y = 0;
				tempCenter.z = tempOffset.z - m_size[i] / 2;

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