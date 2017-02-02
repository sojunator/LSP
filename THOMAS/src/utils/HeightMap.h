#pragma once
#include "../graphics/Model.h"
#include "../Common.h"
#include "noise\noise.h"

namespace thomas
{
	namespace utils
	{
		class HeightMap
		{
		public:
			static void GenerateHeightMap(int size, float detail);
			static std::vector<float> GetHeight();
		private:
			static std::vector<float> s_height;
		};
	}
}