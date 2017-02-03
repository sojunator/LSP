#include "HeightMap.h"

namespace thomas
{
	namespace utils
	{

		std::vector<float> HeightMap::s_height;

		std::vector<graphics::Mesh*> HeightMap::ApplyHeightMap(int size, float detail, Plane::PlaneData& plane, graphics::Material* mat)
		{
			float width = size * detail;
			float height = width;
			double e = 0.0f;
			float d = 0;
			float n = 0;
			
			srand(time(NULL));

			noise::module::Perlin myModule;

			myModule.SetNoiseQuality(noise::NoiseQuality::QUALITY_BEST);

			myModule.SetFrequency(1.f);
			myModule.SetSeed(rand() % 1000);

			float x, y;
			for (int i = 0; i < plane.verts.size(); i++)
			{
				x = -plane.verts[i].position.z * detail;
				y = plane.verts[i].position.x * detail;

				double e = 0.0f;
				double nx = x / width - 0.5,
					ny = y / height - 0.5;


				e += myModule.GetValue(nx, ny, 0) / 2.0 + 0.5;
				e += myModule.GetValue(2 * nx, 2 * ny, 0) / 2.0 + 0.5;
				e += myModule.GetValue(4* nx, 2*  ny, 0) / 2.0 + 0.5;
				e += myModule.GetValue(8*nx, 4*ny, 0) / 2.0 + 0.5;
				e = pow(e, 1.7f);
				
				plane.verts[i].position.y = (e + 0.10) * (1 - 1.05*pow(2 * max(abs(nx), abs(ny)), 0.40)) * 4.0;
			}

			std::vector<thomas::graphics::Mesh*> mesh;
			graphics::Mesh* m = new graphics::Mesh(plane.verts, plane.indices, "Plane-1", mat);
			mesh.push_back(m);
			return mesh;
		}

		std::vector<float> HeightMap::GetHeight()
		{
			return s_height;
		}
	}
}