#include "Plane.h"
#include <time.h>
#include <cmath>
#include <algorithm>
namespace thomas
{
	namespace utils
	{
		std::vector<thomas::graphics::Mesh*> Plane::CreatePlane(int size, float detail, std::string meshName,
			graphics::Material* mat)
		{
			std::vector<graphics::Vertex> verts;
			std::vector<int> indices;
			float width = (float)size * detail;
			float height = width;

			float x, y, z;
			graphics::Vertex temp_vert;
			srand(time(NULL));
			// Defualt temp values, must be calulated later
			temp_vert.normal.x = 0.0f;
			temp_vert.normal.y = 1.0f;
			temp_vert.normal.z = 0.0f;
			temp_vert.bitangent.x = 0.0f;
			temp_vert.bitangent.y = 0.0f;
			temp_vert.bitangent.z = -1.0f;
			temp_vert.tangent.x = 1.0f;
			temp_vert.tangent.y = 0.0f;
			temp_vert.tangent.z = 0.0f;

			noise::module::Perlin myModule;

			myModule.SetNoiseQuality(noise::NoiseQuality::QUALITY_BEST);

			myModule.SetFrequency(1.f);
			myModule.SetSeed(5);
	
			double e = 0.0f;
			// Create points
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					e = 0.0f;
					double nx = x / width - 0.5,
						ny = y / height - 0.5;


					e += myModule.GetValue(nx, ny, 0) / 2.0 + 0.5;
					e += myModule.GetValue(2 * nx, 2 * ny, 0) / 2.0 + 0.5;
					e += myModule.GetValue(4* nx, 2*  ny, 0) / 2.0 + 0.5;
					e += myModule.GetValue(8*nx, 4*ny, 0) / 2.0 + 0.5;
					e = pow(e, 5.3);
					
					temp_vert.position.y = (e + 0.10) * (1 - 1.05*pow(2 * max(abs(nx), abs(ny)), 0.40));
					temp_vert.position.x = (float)y / detail;
					temp_vert.position.z = -(float)x / detail;
					temp_vert.uv.x = y / ((float)size * detail);
					temp_vert.uv.y = 1.0f - (x - (height) / (height));
					verts.push_back(temp_vert);
				}
			}

			// triangulate points
			for (int i = 0; i < (size * detail) - 1; i++)
			{
				int index = size*detail * (i + 1);
				for (int j = 0; j < (size * detail) - 1; j++)
				{
					
					indices.push_back(j + i * size*detail);
					indices.push_back(index);
					indices.push_back(index + 1);

					indices.push_back(j + i * size*detail);
					indices.push_back(index + 1);
					indices.push_back((j + i * size*detail) + 1);

					index++;
				}
			}

			std::vector<thomas::graphics::Mesh*> mesh;
			graphics::Mesh* m = new graphics::Mesh(verts, indices, meshName, mat);
			mesh.push_back(m);
			return mesh;
		}
	}
}
