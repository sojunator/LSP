#include "Islands.h"


namespace thomas
{
	Islands::Islands(int nrOfIslands, graphics::Material* m, int size, float detail, int mapSize, int minDistance)
	{
		utils::Plane::PlaneData tempPlane;
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
			m_islandCenter.push_back(math::Vector2(size/2, size/2));
			/*Something is wrong with m_worldPosOffset*/
			tempPlane = utils::Plane::CreatePlane(size, detail, m_worldPosOffset[i]);
			m_mesh.push_back(utils::HeightMap::ApplyHeightMap(size, detail, tempPlane, m, m_worldPosOffset[i]));
		}
	}
	std::vector<graphics::Mesh*> Islands::GetIsland(int island)
	{
		return m_mesh[island];
	}

	void Islands::GeneratePos()
	{
		for (int i = 0; i < m_nrOfIslands; i++)
		{
			bool posFound = false;
			while (!posFound) {
				int x = rand() % m_mapSize;
				int y = rand() % m_mapSize;
				float distPrev = 0.0f;

				if (m_worldPosOffset.size() == 0)
				{
					distPrev = 0.0f;
					m_worldPosOffset.push_back(thomas::math::Vector2(x, y));
					posFound = true;
				}
				else
				{
					for (int j = 0; j < m_worldPosOffset.size() && !posFound; j++)
					{
						distPrev = (m_worldPosOffset[j].x - x) * (m_worldPosOffset[j].x - x) + (m_worldPosOffset[j].y - y) * (m_worldPosOffset[j].y - y);

						if (2500.0f < distPrev)
						{
							m_worldPosOffset.push_back(thomas::math::Vector2(x, y));
							posFound = true;
						}
					}
				}
			}
		}
	}
}