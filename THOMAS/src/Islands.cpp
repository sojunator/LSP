#include "Islands.h"


namespace thomas
{
	Islands::Islands(int nrOfIslands, graphics::Material* m, int size, float detail, int mapSize, int minDistance)
	{
		std::srand(time(NULL));
		utils::Plane::PlaneData plane = utils::Plane::CreatePlane(mapSize, detail);
		m_mapSize = mapSize;
		m_minDistance = minDistance;
		m_nrOfIslands = nrOfIslands;
		m_plunderRate = 30;

		for (int i = 0; i < nrOfIslands; i++)
		{
			m_size.push_back(size);
			m_detail.push_back(detail);
			m_treasure.push_back(1000);
			m_totalTreasure.push_back(1000);
			m_plunderRadius.push_back(size*detail*0.8);
			m_collisionRadius.push_back(size*detail*0.6);
		}

		GeneratePos();
		for (int i = 0; i < m_nrOfIslands; i++)
		{
			utils::HeightMap::ApplyHeightMap(size, detail, mapSize, plane, math::Vector2(m_worldPosOffset[i].x, m_worldPosOffset[i].y));
		}
		GenerateMesh(plane, m);

	}

	void Islands::GenerateMesh(utils::Plane::PlaneData tempPlane, graphics::Material* m)
	{
		std::vector<thomas::graphics::Mesh*> mesh;
		mesh.push_back(new graphics::Mesh(tempPlane.verts, tempPlane.indices, "Plane-1", m));
		m_mesh.push_back(mesh);
	}

	void Islands::ApplyOffSet(int island, utils::Plane::PlaneData& tempPlanes)
	{
		for (unsigned int i = 0; i < tempPlanes.verts.size(); ++i)
		{
			tempPlanes.verts[i].position.x += m_worldPosOffset[island].x;
			tempPlanes.verts[i].position.z += m_worldPosOffset[island].y;
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

	math::Vector2 Islands::GetCenter(int island)
	{
		return m_islandCenterWorldPos[island];
	}

	math::Vector2 Islands::GetOffSet(int island)
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
			return temp;
		}
		else
		{
			m_treasure[island] -= dt*m_plunderRate;
			return dt*m_plunderRate;
		}
	}

	int Islands::GetSizeOFIsland(int island)
	{
		return m_size[island] * m_detail[island];
	}

	void Islands::GeneratePos()
	{
		const int MAX_ATTEMPTS = 1200;
		int attempt = 0;
		for (int i = 0; i < m_nrOfIslands; i++)
		{
			bool posNotFound = true;
			while (posNotFound && attempt < MAX_ATTEMPTS)
			{
				math::Vector2 xy;
				xy.x = rand() % (m_mapSize  - m_size[i] - 10);
				xy.y = rand() % (m_mapSize  - m_size[i] - 10);
				xy = xy + math::Vector2(10.0);
				float distPrev = 0.0f;

				if (m_islandCenterWorldPos.size() == 0)
				{
					distPrev = 0.0f;
					m_worldPosOffset.push_back(xy);
					m_islandCenterWorldPos.push_back(math::Vector2(m_worldPosOffset[i].x + ((m_size[i] * m_detail[i]) / 2), m_worldPosOffset[i].y - ((m_size[i] * m_detail[i]) / 2)));
					posNotFound = false;
				}
				else
				{
					std::vector<float> distance;
					for (unsigned int j = 0; j < m_islandCenterWorldPos.size(); j++)
						distance.push_back((m_islandCenterWorldPos[j].x - xy.x) * (m_islandCenterWorldPos[j].x - xy.x) + (m_islandCenterWorldPos[j].y - xy.y) * (m_islandCenterWorldPos[j].y - xy.y));

					for (unsigned int k = 0; k < distance.size(); ++k)
					{
						if (distance[k] < m_minDistance*m_minDistance)
						{
							posNotFound = true;
							attempt++;
							break;
						}
						else
						{

							posNotFound = false;
						}
					}
					if (!posNotFound)
					{
						attempt = 0;
						m_worldPosOffset.push_back(xy);
						m_islandCenterWorldPos.push_back(math::Vector2(m_worldPosOffset[i].x + ((m_size[i] * m_detail[i]) / 2), m_worldPosOffset[i].y - ((m_size[i] * m_detail[i]) / 2)));
					}
				}
			}
		}
		m_nrOfIslands = m_worldPosOffset.size(); 
	}
}