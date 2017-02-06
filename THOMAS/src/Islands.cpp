#include "Islands.h"


namespace thomas
{
	Islands::Islands(int nrOfIslands, graphics::Material* m, int size, float detail, int mapSize, int minDistance)
	{
		std::vector<utils::Plane::PlaneData> tempPlane;
		std::vector<graphics::Mesh*> mesh;
		m_mapSize = mapSize;
		m_minDistance = minDistance;
		m_nrOfIslands = nrOfIslands;

		GeneratePos();
		for (int i = 0; i < nrOfIslands; i++)
		{
			m_size.push_back(size);
			m_detail.push_back(detail);
			m_treasure.push_back(1000);
			m_islandCenter.push_back(math::Vector2(size / 2, size / 2));
			tempPlane.push_back(utils::Plane::CreatePlane(size, detail, m_worldPosOffset[i]));
			utils::HeightMap::ApplyHeightMap(size, detail, tempPlane[i], m_worldPosOffset[i]);
		}
		GenerateMesh(tempPlane, m);
	}

	void Islands::GenerateMesh(std::vector<utils::Plane::PlaneData> tempPlane, graphics::Material* m)
	{
		std::vector<thomas::graphics::Mesh*> mesh;
		for (int i = 0; i < tempPlane.size(); ++i)
		{
			mesh.push_back(new graphics::Mesh(tempPlane[i].verts, tempPlane[i].indices, "Plane-1", m));

		}
		m_mesh.push_back(mesh);
	}

	std::vector<graphics::Mesh*> Islands::GetIsland(int island)
	{
		return m_mesh[island];
	}

	void Islands::GeneratePos()
	{
		for (int i = 0; i < m_nrOfIslands; i++)
		{
			bool posNotFound = true;
			while (posNotFound)
			{
				math::Vector2 xy;
				xy.x = rand() % m_mapSize;
				xy.y = rand() % m_mapSize;
				float distPrev = 0.0f;

				if (m_worldPosOffset.size() == 0)
				{
					distPrev = 0.0f;
					m_worldPosOffset.push_back(xy);
					posNotFound = false;
				}
				else
				{
					std::vector<float> distance;
					for (int j = 0; j < m_worldPosOffset.size(); j++)
						distance.push_back((m_worldPosOffset[j].x - xy.x) * (m_worldPosOffset[j].x - xy.x) + (m_worldPosOffset[j].y - xy.y) * (m_worldPosOffset[j].y - xy.y));

					for (int k = 0; k < distance.size(); ++k)
					{
						if (distance[k] < m_minDistance)
							break;
						else
							posNotFound = false;
					}
					if (!posNotFound)
						m_worldPosOffset.push_back(xy);
				}
			}
		}
	}
}