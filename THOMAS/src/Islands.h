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
		void GenerateMesh(utils::Plane::PlaneData tempPlanes, graphics::Material* m);
		void ApplyOffSet(int island, utils::Plane::PlaneData& tempPlanes);
		~Islands();

		int GetPlunderRate();									//GetplunderRate
		int GetNrOfIslands();									//Get nr of islands
		int GetMapSize();										//Get size of the whole play area
		int GetMinDistance();									//Get minimum allowed distance between islands
		float GetTreasure(int island);							//Get treasure for specific island
		int GetTotalTreasure(int island);						//Get totala amount of treasure for specific island
		int GetSize(int island);								//Get size of specific island
		int GetDetail(int island);								//Get detail level of specific island
		float GetPlunderRadius(int island);						//Get radius to plunder for specific island
		float GetCollisionRadius(int island);					//Get radius for collision for specific island
		math::Vector3 GetCenter(int island);					//Get m_islandCenterWorldPos for specific island
		math::Vector3 GetOffSet(int island);					//Get offset for specific island	
		std::vector<graphics::Mesh*> GetIslands(int island);	//Get mesh of all islands on a map

		float GetPlunderRadiusSquared(int island);				//Get radius squared for specific island
		float GetCollisionRadiusSquared(int island);
		float StealTreasure(int island);						//Get stolen treasure for specific island
		int GetSizeOFIsland(int island);						//Get size of specific island

	private:
		void GeneratePos();

	private:
		int m_plunderRate;
		int m_nrOfIslands;
		int m_mapSize;
		int m_minDistance;
		std::vector<float> m_treasure;
		std::vector<int> m_totalTreasure;
		std::vector<int> m_size;
		std::vector<float> m_detail;
		std::vector<float> m_plunderRadius;
		std::vector<float> m_collisionRadius;
		std::vector<math::Vector3> m_islandCenterWorldPos;
		std::vector<math::Vector3> m_worldPosOffset;
		std::vector<std::vector<graphics::Mesh*>> m_mesh;
	};
}