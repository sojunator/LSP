#pragma once
#include "../../Common.h"

namespace thomas
{
	namespace utils
	{
		namespace AI
		{
			class THOMAS_API Pathfinding
			{
			public:
				Pathfinding();
				~Pathfinding();
				void FindPath(math::Vector3 pos, math::Vector3 forward, math::Vector3 destination);

			};
		}
	}
}