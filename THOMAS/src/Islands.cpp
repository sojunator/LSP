#include "Islands.h"


namespace thomas
{
	Islands::Islands(int nrOfIslands, graphics::Material* m, int size, float detail, int mapSize, int minDistance)
	{
		std::srand(time(NULL));

		m_mapSize = mapSize;
		m_minDistance = minDistance;
		m_mapSize = mapSize;
		m_minDistance = minDistance;
		m_plunderRate = 30;
		m_nrOfIslands = nrOfIslands;

		for (int i = 0; i < m_nrOfIslands; i++)
		{
			m_lostTreasureSinceLastEnemySpawn.push_back(0);
			m_size.push_back(size);
			m_detail.push_back(detail);
			m_treasure.push_back(1000);
			m_totalTreasure.push_back(1000);
			m_plunderRadius.push_back(size*0.43);
			m_collisionRadius.push_back(size*0.3);
		}

		GeneratePos(); // find suitable pos
		std::vector<utils::Plane::PlaneData> planes;

		for (int i = 0; i < m_nrOfIslands; i++)
		{
			planes.push_back(utils::Plane::CreatePlane(size, detail));
		}

		for (int i = 0; i < m_nrOfIslands; i++)
		{
			utils::HeightMap::ApplyHeightMap(size, detail, planes[i]);
			//m_islandCenterWorldPos[i].x -= mapSize / 2;
			//m_islandCenterWorldPos[i].z += mapSize / 2;
		}

		for (unsigned int i = 0; i < m_nrOfIslands; i++)
		{
			ApplyOffSet(i, planes[i]);
		}
		//ChangeHeightMapValues(planes);
		GenerateMesh(planes, m);

	}
	
	void Islands::GenerateMesh(utils::Plane::PlaneData tempPlane, graphics::Material* m)
	{
		std::vector<thomas::graphics::Mesh*> mesh;
		mesh.push_back(new graphics::Mesh(tempPlane.verts, tempPlane.indices, "Islands", m));
		m_mesh.push_back(mesh);
	}

	void Islands::GenerateMesh(std::vector<utils::Plane::PlaneData> tempPlanes, graphics::Material* m)
	{
		std::vector<thomas::graphics::Mesh*> mesh;
		for (auto plane : tempPlanes)
		{
			int index = 0;
			mesh.push_back(new graphics::Mesh(plane.verts, plane.indices, "Island" + std::to_string(index++), m));
			m_mesh.push_back(mesh);
		}
	}

	void Islands::ApplyOffSet(int island, utils::Plane::PlaneData& tempPlanes)
	{
		for (unsigned int i = 0; i < tempPlanes.verts.size(); ++i)
		{
			tempPlanes.verts[i].position.x += m_worldPosOffset[island].x;
			tempPlanes.verts[i].position.z += m_worldPosOffset[island].z;
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

	int Islands::GetMinDistance()
	{
		return m_minDistance;
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
		float dt = Time::GetDeltaTime();
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
		return m_size[island]/* * m_detail[island]*/;
	}

	void Islands::ChangeHeightMapValues(thomas::utils::Plane::PlaneData& plane)
	{
		for (int i = 0; i < plane.verts.size(); i++)
		{
			if (plane.verts[i].position.y < 5.0)
				plane.verts[i].position.y = -20.0;
		}
	}

	void Islands::GeneratePos()
	{
		const int MAX_ATTEMPTS = 1200;
		int attempt = 0;
		int addedIslands = 0;
		math::Vector3 tempOffset;


		tempOffset.x = 0;
		tempOffset.y = 0;
		tempOffset.z = 0;


		tempOffset.x += 10;
		tempOffset.z += 10;

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
			while (!foundPos && MAX_ATTEMPTS != attempt)
			{
				tempOffset.x = rand() % 1024;
				tempOffset.y = 0;
				tempOffset.z = rand() % 1024;
				tempOffset.x += 10;
				tempOffset.z += 10;
				
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
					if (distance[j] <= m_minDistance)
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