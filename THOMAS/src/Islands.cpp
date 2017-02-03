#include "Islands.h"


namespace thomas
{
	Islands::Islands(int nrOfIslands, graphics::Material* m)
	{
		for (int i = 0; i < nrOfIslands; i++)
		{
			utils::HeightMap::ApplyHeightMap(1024, 0.125, utils::Plane::CreatePlane(1024, 0.125), m);

		}
	}
}