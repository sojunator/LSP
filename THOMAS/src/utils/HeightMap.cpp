#include "HeightMap.h"

namespace thomas
{
	namespace utils
	{

		std::vector<float> HeightMap::s_height;

		void HeightMap::GenerateHeightMap(int size, float detail)
		{
			float width = size * detail;
			float height = width;
			double e = 0.0f;
			float d = 0;
			float n = 0;


			noise::module::Perlin myModule;

			myModule.SetNoiseQuality(noise::NoiseQuality::QUALITY_BEST);

			myModule.SetFrequency(1.f);
			myModule.SetSeed(5);

			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					e = 0.0f;
					double nx = x / width - 0.5,
						ny = y / height - 0.5;

					e += myModule.GetValue(nx, ny, 0) / 2.0 + 0.5;
					e += myModule.GetValue(2 * nx, 2 * ny, 0) / 2.0 + 0.5;
					e += myModule.GetValue(4 * nx, 2 * ny, 0) / 2.0 + 0.5;
					e += myModule.GetValue(8 * nx, 4 * ny, 0) / 2.0 + 0.5;
					e = pow(e, 5.3);

					int index = (y*size*detail) + x;
					//d = 2 * max(abs(nx), abs(ny));
					//n = (1 - 1.05*pow(d, 0.40));
					//e = (e + 0.10) * n;
					s_height.push_back((e + 0.10) * (1 - 1.05*pow(2 * max(abs(nx), abs(ny)), 0.40)));

					int i = index;
					//temp_vert.position.y = (e + 0.10) * (1 - 1.05*pow(2 * max(abs(nx), abs(ny)), 0.40));
					//temp_vert.position.x = (float)y / detail;
					//temp_vert.position.z = -(float)x / detail;
					//temp_vert.uv.x = y / ((float)size * detail);
					//temp_vert.uv.y = 1.0f - (x - (height) / (height));
					//verts.push_back(temp_vert);
				}
			}
		}

		std::vector<float> HeightMap::GetHeight()
		{
			return s_height;
		}
	}
}