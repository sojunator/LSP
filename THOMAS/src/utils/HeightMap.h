#pragma once
#include "../graphics/Model.h"
#include "../Common.h"
#include "noise\noise.h"
#include "Plane.h"
#include <time.h>

namespace thomas
{
	namespace utils
	{
		class HeightMap
		{
		public:
			static void HeightMap::ApplyHeightMap(int size, float detail, Plane::PlaneData& plane, math::Vector2 offset);
			static std::vector<float> GetHeight();
		private:
			static std::vector<float> s_height;
		};
	}
}