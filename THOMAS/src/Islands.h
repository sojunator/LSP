#pragma once

#include "Common.h"
#include "utils\HeightMap.h"
#include <vector>

namespace thomas
{
	class Islands
	{
	public:
		Islands(int nrOfIslands, graphics::Material* m, int size, float detail, int mapSize, int minDistance);
		//~Islands();
		//std::vector<std::vector<graphics::Mesh*>> GetIslands();
		std::vector<graphics::Mesh*> GetIsland(int island);
		/*std::vector<int> GetTreasure();
		int GetTreasureForIsland(int island);
		std::vector<int> GetSize();
		int GetSizeForIsland(int island);
		std::vector<math::Vector2> GetCenter();
		math::Vector2 GetCenterForIsland(int island);
		std::vector<math::Vector2> GetWorldCenter();
		math::Vector2 GetWorldCenterForIsland(int island);*/
	private:
		void GeneratePos();

	private:
		int m_nrOfIslands;
		int m_mapSize;
		int m_minDistance;
		std::vector<int> m_treasure;
		std::vector<int> m_size;
		std::vector<float> m_detail;
		std::vector<math::Vector2> m_islandCenter;
		std::vector<math::Vector2> m_worldPosOffset;
		std::vector<std::vector<graphics::Mesh*>> m_mesh;
	};
}